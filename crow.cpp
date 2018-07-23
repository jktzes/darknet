#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include <vector>
#include "crow.h"
#include "./src/yolo_v2_class.hpp"

crow::json::wvalue return_result(std::vector<bbox_t> const result_vec, std::vector<std::string> const obj_names) {
	crow::json::wvalue detection_json;
	for (auto &i : result_vec) {
		detection_json[i].obj = i.obj_id;
		detection_json["x"] = i.x;
		detection_json["y"] = i.y;
		detection_json["w"] = i.w;
		detection_json["h"] = i.h;
		detection_json["prob"] = i.prob;
	}
	return detection_json;
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

	app.port(18080).multithreaded().run();
}
