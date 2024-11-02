#include <iterator>
#include <iostream>


#include "pch.h"
#include "Ccore.h"
#include "Item.h"
bool GameOff = true;

int main()
{

	std::locale::global(std::locale(""));
	std::wcout.imbue(std::locale());
	Ccore::GetInst()->GameStartSet();
	Ccore::GetInst()->Init();
	while (GameOff)
	{

		Ccore::GetInst()->Progress();


	}


}
