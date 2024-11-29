#pragma once
#ifndef DUNGEON_H
#define DUNGEON_H
#include "EventManager.h"
struct E_Check;
class EventManager;
// �̺�Ʈ�� ��� �Ͼ���� �⺻ ���
class Node {
public:
    
    EventType E_Type; // �̺�Ʈ ���� ����
    Node* left;
    Node* right;
    Node(EventType type) : E_Type(type), left(nullptr), right(nullptr) {} // ������ �߰�
    ~Node();
};

class Dungeon {
public:
    Dungeon(unsigned int seed);
    void traverse(Node* node, int depth);

private:
    unsigned int seed; // ������ ���� �õ尪
    EventManager eventManager; // EventManager �ν��Ͻ�, ��ǻ� ��
};
#endif // DUNGEON_H
// Dungeon Ŭ���� ���� �����ϰ� �����ڷ� Ž�� �� ����, �� �� Main ���� �Լ��� �̰ɷ� ����,
// ���� �����ڸ� ���� ���·� ����, ���߿� �߰��� ���� ������ �� ���� ������