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
	EventType E_Type; // 노드의 이벤트 타입
	Node* left;            // 왼쪽 경로
	Node* right;           // 오른쪽 경로

	Node(EventType type) : E_Type(type),left(nullptr),right(nullptr) {}// 생성자
	//Node();
	~Node();                // 소멸자
};
// 던전 클래스 정의
class Dungeon {
public:
	Node* start; // 던전 시작점

	Dungeon();                        // 생성자
	~Dungeon();                       // 소멸자
	void traverse(Node* node);        // 던전 탐험 함수
	Node* generateDungeon(int depth = 5); // 던전 생성 함수, 옆의 int 5는 따로 지정값이 없으면 적용
};
#endif // DUNGEON_H
// Dungeon 클래스 변수 생성하고 생성자로 탐험 맵 생성, 그 후 Main 진행 함수를 이걸로 진행,
// 던전 생성자를 지금 상태로 가자, 나중에 추가로 던전 생성을 할 수도 있으니