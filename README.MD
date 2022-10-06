# Nya JSON DB
(Not yet another) json database is a super simple implementation of a persistent database which uses c++ in the backend.
## Features
 - Automatically saves the database on disk after a set operation.
 - Simple database corruption check.

## Usage

    const NyaJSONDB = require("nya-json-db");
    
    let nyaJSONDB = new NyaJSONDB(<path to db>);
    // Set object
    nyaJSONDB.set(<key>, <object>);
    // Get Object
    const result = nyaJSONDB.get(<key>);
    // Clear Database
    nyaJSONDB.clear();
