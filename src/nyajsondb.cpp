#include "nyajsondb.h"
using namespace std;

Napi::Object NyaJSONDB::Init(Napi::Env env, Napi::Object exports)
{
    Napi::Function func = DefineClass(env, "NyaJSONDB", {
                                                         InstanceMethod("set", &NyaJSONDB::Set),
                                                         InstanceMethod("clear", &NyaJSONDB::Clear),
                                                         InstanceMethod("get", &NyaJSONDB::Get),
                                                         InstanceMethod("save", &NyaJSONDB::Save)
                                                     });
    Napi::FunctionReference *constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("NyaJSONDB", func);
    return exports;
};

NyaJSONDB::NyaJSONDB(const Napi::CallbackInfo &info) : Napi::ObjectWrap<NyaJSONDB>(info)
{
    Napi::Env env = info.Env();

    int length = info.Length();

    if (length == 0 || !info[0].IsString())
    {
        Napi::TypeError::New(env, "Expected a path variable!").ThrowAsJavaScriptException();
        return;
    }

    if (info[1].IsObject()) {
        const auto options = info[1].As<Napi::Object>();
        if (options.Has("autoSave") && options.Get("autoSave").IsBoolean()) {
            this->autoSave = options.Get("autoSave").As<Napi::Boolean>().ToBoolean();
        }
    }

    string path = info[0].As<Napi::String>().ToString().Utf8Value();

    this->_path = path;

    this->Load();
};

void NyaJSONDB::Set(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();

    if (info.Length() != 2 || !info[0].IsString() || !info[1].IsObject())
    {
        Napi::TypeError::New(env, "Expected a key, value as string!").ThrowAsJavaScriptException();
        return;
    };

    string key = info[0].As<Napi::String>().ToString().Utf8Value();

    Napi::Object json_object = info[1].As<Napi::Object>();

    Napi::Object json = env.Global().Get("JSON").As<Napi::Object>();
    Napi::Function stringify = json.Get("stringify").As<Napi::Function>();
    string stringified = stringify.Call(json, {json_object})
                             .As<Napi::String>()
                             .ToString()
                             .Utf8Value();
    this->_map.insert_or_assign(key, stringified);
    if(this->autoSave) this->Save();
}

Napi::Value NyaJSONDB::Get(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();

    if (info.Length() != 1 || !info[0].IsString())
    {
        Napi::Error::New(env, "Expected a key as string!").ThrowAsJavaScriptException();
        return env.Undefined();
    };

    const string key = info[0].As<Napi::String>().ToString().Utf8Value();

    string item;
    auto it = this->_map.find(key);

    if (it != this->_map.end())
    {
        item = this->_map[it->first];
    }
    else
    {
        return env.Undefined();
    }

    const Napi::String json_string = Napi::String::String::New(env, item);
    const Napi::Object json = env.Global().Get("JSON").As<Napi::Object>();
    const Napi::Function parse = json.Get("parse").As<Napi::Function>();

    return parse.Call(json, {json_string}).As<Napi::Value>();
};

void NyaJSONDB::Save(const Napi::CallbackInfo&) {
    this->Save();
};

void NyaJSONDB::Clear(const Napi::CallbackInfo &)
{
    this->Clear();
};

void NyaJSONDB::Load()
{
    try
    {
        ifstream istream(this->_path);
        cereal::JSONInputArchive iarchive(istream);
        iarchive(this->_map);
    }
    catch (cereal::Exception &)
    {
    };
};

void NyaJSONDB::Save()
{
    try
    {
        ofstream ostream(this->_path);
        cereal::JSONOutputArchive oarchive(ostream);
        oarchive(this->_map);
    }
    catch (cereal::Exception &)
    {
    };
};

void NyaJSONDB::Clear()
{
    this->_map.clear();
    remove(this->_path.c_str());
};