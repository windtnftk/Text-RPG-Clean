#include "pch.h"
#include "EventManager.h"
//#include "Dungeon.h"
//#include "Ccore.h"

//Node::Node()
//	: E_Type(EventType::Treasure),
//	left(nullptr),
//	right(nullptr)
//{
//	
//}
Node::~Node()
{
	delete left;
	delete right;
}
// 던전 생성자
Dungeon::Dungeon(unsigned int seed) : seed(seed), eventManager(seed) {}

void Dungeon::traverse(Node* node, int depth) {
    if (!node) return;

    // 동일한 EventManager 객체를 사용하여 이벤트를 트리거
    eventManager.triggerEvent(node->E_Type, depth);

    // 던전의 경로를 선택하고 재귀적으로 탐험
    if (node->left && node->right) {
        std::cout << "Choose your path: [1] Left or [2] Right" << std::endl;
        int choice;
        std::cin >> choice;

        if (choice == 1)
            traverse(node->left, depth + 1);  // 깊이를 증가시키면서 왼쪽으로 탐험
        else
            traverse(node->right, depth + 1); // 깊이를 증가시키면서 오른쪽으로 탐험
    }
    else {
        std::cout << "No more paths. End of dungeon." << std::endl;
    }
}