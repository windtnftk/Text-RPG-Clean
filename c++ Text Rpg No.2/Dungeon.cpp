#include "pch.h"
#include "Dungeon.h"

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
Dungeon::Dungeon() {
    srand(time(0)); // 랜덤 시드 초기화
    start = generateDungeon();
}

// 던전 소멸자
Dungeon::~Dungeon() {
    delete start;
}

// 던전 탐험 함수
void Dungeon::traverse(Node* node) {
    if (!node) return;
    //NowCoding : 2024.11.28
    // 이벤트 타입에 따라 메시지 출력,  
    switch (node->E_Type) {
    case EventType::Enemy:
        std::cout << "You encounter an enemy!" << std::endl;
        break;
    case EventType::Treasure:
        std::cout << "You find a treasure chest!" << std::endl;
        break;
    case EventType::Shop:
        std::cout << "You enter a shop!" << std::endl;
        break;
    case EventType::Event:
        std::cout << "A mysterious event occurs..." << std::endl;
        break;
    }

    if (node->left && node->right) {
        std::cout << "Choose your path: [1] Left or [2] Right" << std::endl;
        int choice;
        std::cin >> choice;

        if (choice == 1)
            traverse(node->left);
        else
            traverse(node->right);
    }
    else {
        std::cout << "No more paths. End of dungeon." << std::endl;
    }
}

// 던전 생성 함수
Node* Dungeon::generateDungeon(int depth) {
    if (depth == 0) return nullptr;

    // 랜덤 이벤트 선택
    EventType events[] = { EventType::Enemy, EventType::Treasure, EventType::Shop, EventType::Event };
    EventType eventType = events[rand() % 4];

    Node* currentNode = new Node(eventType);
    currentNode->left = generateDungeon(depth - 1);
    currentNode->right = generateDungeon(depth - 1);

    return currentNode;
}