{
    "targets": [{
        "target_name": "nyajsondb",
        "cflags!": [ "-fno-exceptions", "-std=c++17" ],
        "cflags_cc!": [ "-fno-exceptions", "-std=c++17" ],
        "sources": [
            "cpp/main.cpp",
            "cpp/nyajsondb.cpp"
        ],
        'include_dirs': [
            "<!@(node -p \"require('node-addon-api').include\")"
        ],
        'libraries': [],
        'dependencies': [
            "<!(node -p \"require('node-addon-api').gyp\")"
        ],
        'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ]
    }]
}