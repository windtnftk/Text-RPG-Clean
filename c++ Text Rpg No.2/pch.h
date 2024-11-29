#pragma once
#ifndef PCH_H
#define PCH_H
#define SINGLE(type) public:\
						 static type* GetInst()\
						{\
						static type mgr; \
						return &mgr;\
						}\
						protected:\
						type();\
						~type();
extern bool GameOff;
#include <random>
#include <vector>
using std::vector;
#include <string>
using std::string;
using std::wstring;
#include <stdio.h>
#include <iostream>
#include <map>
#include <memory>
using std::map;
#include <fstream>
#include "Default.h"
#include <sstream>
#include <unordered_map>
#include <functional>
#include "Enemy.h"
#include "Item.h"
#include "Ccore.h"
#include "Dungeon.h"
#include "Attribute.h"



#endif // PCH_H
