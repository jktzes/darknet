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

std::string generate_json(std::vector<bbox_t> const result_vec, std::vector<std::string> const obj_names) {
    using namespace rapidjson;
	Document json_response;
	Value response;
	Value annotations;
	Value annotation_array;
	Document::AllocatorType& allocator = json_response.GetAllocator();

	json_response.SetObject();
	response.SetObject();
	annotations.SetObject();
	annotation_array.SetArray();

	for (auto &i : result_vec) {
	    if (obj_names.size() > i.obj_id) { obj_names[i.obj_id] = " - ";}
	    Value single_annotation;
	    single_annotation.
	    annotation_array.AddMember("width", x.w, allocator)

	    somearray.PushBack("woah", allocator); 

	StringBuffer buffer;
	Writer<StringBuffer> writer(buffer);
	document.Accept(writer);
	return buffer.GetString();
};

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

void show_console_result(std::vector<bbox_t> const result_vec, std::vector<std::string> const obj_names) {
    for (auto &i : result_vec) {
        if (obj_names.size() > i.obj_id) 
	    std::cout << obj_names[i.obj_id] << " - ";
        std::cout << "obj_id = " << i.obj_id << ",  x = " << i.x << ", y = " << i.y 
            << ", w = " << i.w << ", h = " << i.h
            << std::setprecision(3) << ", prob = " << i.prob << std::endl;
    }
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
