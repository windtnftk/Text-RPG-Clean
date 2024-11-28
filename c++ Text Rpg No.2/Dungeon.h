#pragma once
#ifndef DUNGEON_H
#define DUNGEON_H
enum class EventType
{
	Enemy,
	Treasure,
	Shop,
	Event
};
class Node
{
public:
	EventType E_Type; // ����� �̺�Ʈ Ÿ��
	Node* left;            // ���� ���
	Node* right;           // ������ ���

	Node(EventType type) : E_Type(type),left(nullptr),right(nullptr) {}// ������
	//Node();
	~Node();                // �Ҹ���
};
// ���� Ŭ���� ����
class Dungeon {
public:
	Node* start; // ���� ������

	Dungeon();                        // ������
	~Dungeon();                       // �Ҹ���
	void traverse(Node* node);        // ���� Ž�� �Լ�
	Node* generateDungeon(int depth = 5); // ���� ���� �Լ�, ���� int 5�� ���� �������� ������ ����
};
#endif // DUNGEON_H
// Dungeon Ŭ���� ���� �����ϰ� �����ڷ� Ž�� �� ����, �� �� Main ���� �Լ��� �̰ɷ� ����,
// ���� �����ڸ� ���� ���·� ����, ���߿� �߰��� ���� ������ �� ���� ������