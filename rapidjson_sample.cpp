#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <iostream>

using namespace rapidjson;

int main() {
	Document document;
	document.SetObject();
	Document::AllocatorType& allocator = document.GetAllocator();
	Value something;
	something.SetObject();
	Value somearray;
	somearray.SetArray();
	somearray.PushBack("woah", allocator); 
	document.AddMember("array", somearray, allocator);
	document.AddMember("something", something, allocator);
	document.AddMember("it", "works", allocator);

	StringBuffer buffer;
	Writer<StringBuffer> writer(buffer);
	document.Accept(writer);

	std::cout << buffer.GetString() << std::endl;
	return 0;
}
