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
// ���� ������
Dungeon::Dungeon() {
    srand(time(0)); // ���� �õ� �ʱ�ȭ
    start = generateDungeon();
}

// ���� �Ҹ���
Dungeon::~Dungeon() {
    delete start;
}

// ���� Ž�� �Լ�
void Dungeon::traverse(Node* node) {
    if (!node) return;
    //NowCoding : 2024.11.28
    // �̺�Ʈ Ÿ�Կ� ���� �޽��� ���,  
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

// ���� ���� �Լ�
Node* Dungeon::generateDungeon(int depth) {
    if (depth == 0) return nullptr;

    // ���� �̺�Ʈ ����
    EventType events[] = { EventType::Enemy, EventType::Treasure, EventType::Shop, EventType::Event };
    EventType eventType = events[rand() % 4];

    Node* currentNode = new Node(eventType);
    currentNode->left = generateDungeon(depth - 1);
    currentNode->right = generateDungeon(depth - 1);

    return currentNode;
}