#pragma once
#include "Item.h"

class Consumable : public MainItem
{
public:
	//SINGLE(Consumable);
	
	static Consumable* GetInst() {
		static Consumable instance;
		return &instance;
	}
	void ItemInit() override { std::cout << "hi" << std::endl; }

public:
	Consumable();
	~Consumable();
};

