
# Nya JSON DB

(Not yet another) json database is a super simple implementation of a persistent database which uses c++ in the backend.
Requires Python >= 3.7 and MSVC Build Tools 2017.

## Usage

    const NyaJSONDB = require("nya-json-db");
    
    let nyaJSONDB = new NyaJSONDB(<path to db>, (<options>));
    
    // Set object
    nyaJSONDB.set(<key>, <object>);
    
    // Get Object
    const result = nyaJSONDB.get(<key>);
    
    // Clear Database
    nyaJSONDB.clear();

  

## Options

    options = {
	    autoSave: boolean; // Automatically saves database to disk. Defaultvalue: true.
    }

