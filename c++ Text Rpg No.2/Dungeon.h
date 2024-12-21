#pragma once
#ifndef DUNGEON_H
#define DUNGEON_H


// �̺�Ʈ�� ��� �Ͼ���� �⺻ ���
// Node�� ����Ʈ�� ���·� ���� 
// ������ ���� ����� class
// ���� �� traverse���� ��� �Լ��� ���� �� �����̴�
// ������ �� 1���� ��� ����
#include "EventManager.h"


// ���� ���, generateNode �Լ��� ����Ʈ�� ���� ���� 5
class Node {
public:
    // �� ������ IEvent �κ�Ŭ���� ��ӹ��� �̺�Ʈ Ŭ���� ����
    // Ŭ������ �����Ͽ� ��ü ���������� ���� -> Ŭ���� Ʈ���� �ߵ��� �˾Ƽ� �������� �߻�
    IEvent* event;;
    Node* left;
    Node* right;
    // ������, ȣ��� getRandomEvent�� �μ� �޾ƿ�
    Node(IEvent* event) : event(event), left(nullptr), right(nullptr) {}
    // ����, ������ �ּҷ� �̵��Ͽ� ������� ������ ����
    ~Node() {
        delete left;
        delete right;
    }
};
// ���� Ž��� �� �Լ��� traverseDungeon ȣ���Ͽ� ���� ����
// Ž�� �� �̺�Ʈ ó�� �� Ȯ�� ���� ����
class Dungeon {
public:
    // �̾��ϱ� �� ������ �ִ� Seed �� �ҷ��ͼ� ���� ����
    Dungeon(unsigned int seed);
    // ���� ���۽� seed �� ���� ����
    Dungeon();
    // ����� ��� ����
    ~Dungeon();
    // root ������� ���� �� generateNode ȣ��
    void generateDungeon(int depth = 0);
    // root ������� �̻� �߻��̶� �Ǵ��Ͽ� ����, �ƴҰ�� traverse ȣ��
    void traverseDungeon();

private:
    // ���ӿ��� ����� seed ��
    unsigned int seed;
    EventManager eventManager;  // EventManager ��ü
    Node* root;
    // Root ����, ���� 5���� ����Ʈ���� ���� �̺�Ʈ�� ����
    Node* generateNode(int depth);
    // �ش� �̺�Ʈ Ʈ���� �� ����, ������ �����Ͽ� ����
    // ���� 5���� ���޽� ����
    void traverse(Node* node, int depth);
};
#endif // DUNGEON_H
// Dungeon Ŭ���� ���� �����ϰ� �����ڷ� Ž�� �� ����, �� �� Main ���� �Լ��� �̰ɷ� ����,
// ���� �����ڸ� ���� ���·� ����, ���߿� �߰��� ���� ������ �� ���� ������