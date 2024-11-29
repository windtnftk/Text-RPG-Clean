#include <iterator>
#include <iostream>


#include "pch.h"
//#include "Ccore.h"
//#include "Item.h"
bool GameOff = true;

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	std::locale::global(std::locale(""));
	std::wcout.imbue(std::locale());
	Ccore::GetInst()->GameStartSet();
	Ccore::GetInst()->Init();
	while (GameOff)
	{

		Ccore::GetInst()->Progress();


	}
	//Ccore::GetInst()->CurDataSave();

}
