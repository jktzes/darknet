#!/bin/bash
clang++ -std=c++11 -lboost_system -pthread -o crow crow.cpp darknet.so 
