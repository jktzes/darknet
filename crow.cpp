#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include <vector>
#include "crow.h"
#include "./src/yolo_v2_class.hpp"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

std::string return_result(std::vector<bbox_t> const result_vec, std::vector<std::string> const obj_names) {
    using namespace rapidjson;
    using namespace std;
    StringBuffer s;
    Writer<StringBuffer> writer(s);

    writer.StartObject();
        writer.Key("url");
        writer.String("some.jpg");
        writer.Key("response");
        writer.StartObject();
                writer.Key("annotations");
                writer.StartArray();
		    for (auto &i : result_vec) {
                        writer.StartObject();
			    //if (obj_names.size() > i.obj_id) { obj_names[i.obj_id] = " - ";}
			    std::string std_string_label = obj_names[i.obj_id];
			    const char* label = std_string_label.c_str();
                	    writer.Key("width");
                	    writer.Uint(i.h);
                	    writer.Key("height");
                	    writer.Uint(i.h);
			    writer.Key("left");
                	    writer.Uint(i.x);
                	    writer.Key("top");
                	    writer.Uint(i.y);
                	    writer.Key("label");
                	    writer.String(label);
                        writer.EndObject();
		    };
                writer.EndArray();
        writer.EndObject();
    writer.EndObject();

    return s.GetString();
}

std::vector<std::string> objects_names_from_file(std::string const filename) {
	std::ifstream file(filename);
	std::vector<std::string> file_lines;
	if (!file.is_open()) return file_lines;
	for(std::string line; getline(file, line);) file_lines.push_back(line);
	std::cout << "object names loaded \n";
	return file_lines;
}

int main(int argc, char* argv[])
{
	crow::SimpleApp app;
	//initiate a variable of Detector type called detector
	Detector detector("./cfg/slyz.cfg" , "./slyz_3300.weights"); 
	auto obj_names = objects_names_from_file("data/slyz.names");

	CROW_ROUTE(app, "/detect/<str>")([&detector, &obj_names](std::string filename){
		//initiate a vector variable called detection that will only contain bbox_t type data 
		std::string path = "./data/test/slyz" + filename + ".jpg";		
		std::vector<bbox_t> detection = detector.detect(path, 0.5, 0);
		auto json = return_result(detection, obj_names);
		return json;
			});

	app.port(3205).multithreaded().run();
}
