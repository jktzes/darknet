#include <pistache/endpoint.h>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <iostream>

using namespace Pistache;

std::string generate_json() {
    using namespace rapidjson;
	Document document;
	Value something;
	Value somearray;
	Document::AllocatorType& allocator = document.GetAllocator();

	document.SetObject();
	something.SetObject();
	somearray.SetArray();

	somearray.PushBack("woah", allocator); 
	document.AddMember("array", somearray, allocator);
	document.AddMember("something", something, allocator);
	document.AddMember("it", "works", allocator);

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
