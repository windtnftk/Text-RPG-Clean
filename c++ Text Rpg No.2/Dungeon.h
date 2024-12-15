#pragma once
#ifndef DUNGEON_H
#define DUNGEON_H








// �̺�Ʈ�� ��� �Ͼ���� �⺻ ���
// Node�� ����Ʈ�� ���·� ���� 
// ������ ���� ����� class
// ���� �� traverse���� ��� �Լ��� ���� �� �����̴�
// ������ �� 1���� ��� ����
#include "EventManager.h"
// NowCoding : ���� ���� Ŭ���� �� �ٸ� Ŭ����, �Լ� ����-���� �ʿ� �� �� �̺�Ʈ �Լ� ���� ��û
class Node {
public:
    std::unique_ptr<IEvent> event;
    Node* left;
    Node* right;

    Node(std::unique_ptr<IEvent> event)
        : event(std::move(event)), left(nullptr), right(nullptr) {
    }

    ~Node() {
        delete left;
        delete right;
    }
};

class Dungeon {
public:
    Dungeon(unsigned int seed);
    Dungeon();
    ~Dungeon();

    void generateDungeon(int depth = 0);
    void traverseDungeon();

private:
    unsigned int seed;
    EventManager eventManager;  // EventManager ��ü
    Node* root;

    Node* generateNode(int depth);
    void traverse(Node* node, int depth);
};
#endif // DUNGEON_H
// Dungeon Ŭ���� ���� �����ϰ� �����ڷ� Ž�� �� ����, �� �� Main ���� �Լ��� �̰ɷ� ����,
// ���� �����ڸ� ���� ���·� ����, ���߿� �߰��� ���� ������ �� ���� ������