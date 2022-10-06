#include "nyajsondb.h"
using namespace std;

Napi::Object NyaJSONDB::Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "NyatDB", {
        InstanceMethod("set", &NyaJSONDB::Set),
        InstanceMethod("clear", &NyaJSONDB::Clear),
        InstanceMethod("get", &NyaJSONDB::Get),
    });
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);
    exports.Set("NyaJSONDB", func);
    return exports;
};

NyaJSONDB::NyaJSONDB(const Napi::CallbackInfo& info): Napi::ObjectWrap<NyaJSONDB>(info) {
    Napi::Env env = info.Env();

    int length = info.Length();

    if (length <= 0 || !info[0].IsString()) {
        Napi::TypeError::New(env, "Expected a path variable!").ThrowAsJavaScriptException();
        return;
    }

    string path = info[0].As<Napi::String>().ToString().Utf8Value();

    this->_path = path;

    vector<pair<string, string>> temp({});
    ifstream saveFile(this->_path);
    string line;
    bool invalidSaveFile = false;
    int size = 0;
    if (saveFile) {
        getline(saveFile, line);
        size = stoi(line);
        while (getline(saveFile, line)) {
            const string key = line;
            if (!getline(saveFile, line)) {
                invalidSaveFile = true;
            }
            temp.push_back(pair(key, line));
        }
    };
    if (!invalidSaveFile) {
        for (auto const& value : temp) {
            this->_map.insert(value);
        };
    }
};

void NyaJSONDB::Set(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() != 2 || !info[0].IsString() || !info[1].IsObject()) {
        Napi::TypeError::New(env, "Expected a key, value as string!").ThrowAsJavaScriptException();
        return;
    };

    string key = info[0].As<Napi::String>().ToString().Utf8Value();

    Napi::Object json_object = info[1].As<Napi::Object>();

    Napi::Object json = env.Global().Get("JSON").As<Napi::Object>();
    Napi::Function stringify = json.Get("stringify").As<Napi::Function>();
    string stringified = stringify.Call(json, { json_object })
        .As<Napi::String>().ToString().Utf8Value();
    this->_map.insert_or_assign(key, stringified);
    this->Save();
}

Napi::Value NyaJSONDB::Get(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() != 1 || !info[0].IsString()) {
        Napi::Error::New(env, "Expected a key as string!").ThrowAsJavaScriptException();
        return env.Undefined();
    };

    const string key = info[0].As<Napi::String>().ToString().Utf8Value();

    string item;
    auto it = this->_map.find(key);

    if (it != this->_map.end()) {
        item = this->_map[it->first];
    } else {
        return env.Undefined();
    }

    const Napi::String json_string = Napi::String::String::New(env, item);
    const Napi::Object json = env.Global().Get("JSON").As<Napi::Object>();
    const Napi::Function parse = json.Get("parse").As<Napi::Function>();

    return parse.Call(json, { json_string }).As<Napi::Value>();
};

void NyaJSONDB::Clear(const Napi::CallbackInfo&) {
    this->Clear();
};

void NyaJSONDB::Save() {
    ofstream saveFile;
    saveFile.open(this->_path);
    saveFile << this->_map.size() << endl;
    for (auto const& [key, value] : this->_map) {
        saveFile << key << endl << value << endl;
    }
};

void NyaJSONDB::Clear() {
    this->_map.clear();
    remove(this->_path.c_str());
};