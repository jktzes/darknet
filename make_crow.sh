#!/bin/bash
if [ `uname` = "Darwin" ]; then
	clang++ -std=c++11 -lboost_system -pthread -o crow crow.cpp darknet.so 
elif [ `uname` = "Linux" ]; then
	g++ -std=c++11 -lboost_system -pthread -o crow crow.cpp darknet.so 
fi
