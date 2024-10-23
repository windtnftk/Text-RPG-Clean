#pragma once
#include <random>
#include <vector>
using std::vector;
#include <string>
using std::string;
using std::wstring;
#include <stdio.h>
#include <iostream>
#include <map>
using std::map;
#include <fstream>
#include "Default.h"
#include <sstream>

extern bool GameOff;


#define SINGLE(type) public:\
						 static type* GetInst()\
						{\
						static type mgr; \
						return &mgr;\
						}\
						private:\
						type();\
						~type();