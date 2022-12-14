#ifndef NYAJSONDB_H
#define NYAJSONDB_H

#include <string>
#include <map>
#include <napi.h>
#include <cstdio>
#include <fstream>
#include <vector>
#include "cereal/archives/json.hpp"
#include "cereal/types/map.hpp"
#include "cereal/types/string.hpp"

class NyaJSONDB : public Napi::ObjectWrap<NyaJSONDB> {
    public:
        static Napi::Object Init(Napi::Env env, Napi::Object exports);
        NyaJSONDB(const Napi::CallbackInfo& info);
    private:
        Napi::Value Get(const Napi::CallbackInfo& info);
        void Set(const Napi::CallbackInfo& info);
        void Clear(const Napi::CallbackInfo& info);
        void Save(const Napi::CallbackInfo& info);
        
        std::map<std::string, std::string> _map = {};
        std::string _path;
        void Clear();
        void Save();
        void Load();
        bool autoSave = true;
};

#endif