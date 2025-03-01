
# What is it?

Quote from json.org (https://www.json.org/json-en.html)
- “JSON (JavaScript Object Notation) is a lightweight data-interchange format. It is easy for humans to read and write. It is easy for machines to parse and generate.”

#### JSON Format

- Sample json string:
```json
{  
    "SceneName": "Scene1",  
    "GameObjects": [{  
        "ID": 1,  
        "Name": "Player",  
        "Size": 1  
    }, {  
        "ID": 7,  
        "Name": "Floor"  
        "Size": 5  
    }, {  
        "ID": 8,  
        "Name": "Box"  
        "Size": 2  
    }]  
}
```

#### C++ Libraries

There are huge number of C/C++ libraries available that can read and wrote json files, you can find a partial list here:

https://www.json.org/json-en.html

#### Nlohmann JSON Library

- GitHub
	- https://github.com/nlohmann/json
	- we only need one file: single_include/nlohmann/json.hpp

Everything is in the nlohmann namespace, so either pull individual elements out of the namespace or use the entire thing, though you likely only need the "json" object.
```
	using json = nlohmann::json;
	using namespace nlohmann;
```

Load the file and turn it into a data structure:
```c++
	std::ifstream f( "example.json" );
	json data = json::parse(f);
```

Read data from the JSON structure:
```c++
	std::string sceneName = data["SceneName"]; // Get the value "Scene1"
	int firstID = data["GameObjects"][1]["ID"]; // Get the number 7
```

Working on the whole array:
```c++
	json arrayOfGameObjects = data["GameObjects"];
	
	int numObjects = arrayOfGameObjects.size();
```
