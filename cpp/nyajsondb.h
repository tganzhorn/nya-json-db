#ifndef NYATDB_H
#define NYATDB_H

#include <string>
#include <map>
#include <napi.h>
#include <cstdio>
#include <fstream>
#include <vector>

class NyaJSONDB : public Napi::ObjectWrap<NyaJSONDB> {
    public:
        static Napi::Object Init(Napi::Env env, Napi::Object exports);
        NyaJSONDB(const Napi::CallbackInfo& info);
    private:
        Napi::Value Get(const Napi::CallbackInfo& info);
        void Set(const Napi::CallbackInfo& info);
        void Clear(const Napi::CallbackInfo& info);
        
        std::map<std::string, std::string> _map = {};
        std::string _path;
        void Clear();
        void Save();
};

#endif