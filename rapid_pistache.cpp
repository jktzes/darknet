#include <string>
#include <sstream>
#include <iterator>
#include <vector>
#include <iostream>
#include <pistache/endpoint.h>
#include "./src/yolo_v2_class.hpp"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

using namespace Pistache; 

std:string write_json(std::vector<bbox_t> const result_vec, std::vector<std::string> const obj_names) {
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
			    if (obj_names.size() > i.obj_id) { obj_names[i.obj_id] = " - ";}
                	    writer.Key("width");
                	    writer.Uint(x.h);
                	    writer.Key("height");
                	    writer.Uint(x.h);
			    writer.Key("left");
                	    writer.Uint(x.x);
                	    writer.Key("top");
                	    writer.Uint(x.y);
                	    writer.Key("label");
                	    writer.String(obj_name[x.obj_id]);
                        writer.EndObject();
		    };
                writer.EndArray();
        writer.EndObject();
    writer.EndObject();

    s.GetString()
}

class HelloHandler : public Http::Handler {
public:

    HTTP_PROTOTYPE(HelloHandler)

    void onRequest(const Http::Request& request, Http::ResponseWriter response) {
        UNUSED(request);
        response.send(Pistache::Http::Code::Ok, generate_json());
    }
};

std::vector<std::string> objects_names_from_file(std::string const filename) { std::ifstream file(filename);
	std::vector<std::string> file_lines;
	if (!file.is_open()) return file_lines;
	for(std::string line; getline(file, line);) file_lines.push_back(line);
	std::cout << "object names loaded \n";
	return file_lines;
}

int main() {
    Pistache::Address addr(Pistache::Ipv4::any(), Pistache::Port(3205));
    auto opts = Pistache::Http::Endpoint::options()
        .threads(1);

    Http::Endpoint server(addr);
    server.init(opts);
    server.setHandler(Http::make_handler<HelloHandler>());
    server.serve();

    server.shutdown();
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
