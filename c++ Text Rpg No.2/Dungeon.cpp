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
// ���� ������
Dungeon::Dungeon(unsigned int seed) : seed(seed), eventManager(seed) {}

void Dungeon::traverse(Node* node, int depth) {
    if (!node) return;

    // ������ EventManager ��ü�� ����Ͽ� �̺�Ʈ�� Ʈ����
    eventManager.triggerEvent(node->E_Type, depth);

    // ������ ��θ� �����ϰ� ��������� Ž��
    if (node->left && node->right) {
        std::cout << "Choose your path: [1] Left or [2] Right" << std::endl;
        int choice;
        std::cin >> choice;

        if (choice == 1)
            traverse(node->left, depth + 1);  // ���̸� ������Ű�鼭 �������� Ž��
        else
            traverse(node->right, depth + 1); // ���̸� ������Ű�鼭 ���������� Ž��
    }
    else {
        std::cout << "No more paths. End of dungeon." << std::endl;
    }
}