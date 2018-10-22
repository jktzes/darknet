#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <iostream>
using namespace rapidjson;
using namespace std;

int main() {
    StringBuffer s;
    Writer<StringBuffer> writer(s);

    writer.StartObject();

        writer.Key("url");
        writer.String("some.jpg");

        writer.Key("response");
        writer.StartObject();

                writer.Key("annotations");
                writer.StartArray();

                        writer.StartObject();

                                writer.Key("width");
                                writer.Uint(325);

                        writer.EndObject();

                writer.EndArray();

        writer.EndObject();

    writer.EndObject();
    cout << s.GetString() << endl;
    
    return 0;
}

//json = { "url": "some.jpg", "response":{ "annotations": [{ "width":325 }]}}
