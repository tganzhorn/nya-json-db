#include <napi.h>
#include "nyajsondb.h"

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
    return NyaJSONDB::Init(env, exports);
}

NODE_API_MODULE(nyajsondb, InitAll)