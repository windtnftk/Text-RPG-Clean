#pragma once
#ifndef DUNGEON_H
#define DUNGEON_H
#include "EventManager.h"
struct E_Check;
class EventManager;
// 이벤트가 어떤게 일어날지의 기본 노드
class Node {
public:
    
    EventType E_Type; // 이벤트 종류 저장
    Node* left;
    Node* right;
    Node(EventType type) : E_Type(type), left(nullptr), right(nullptr) {} // 생성자 추가
    ~Node();
};

class Dungeon {
public:
    Dungeon(unsigned int seed);
    void traverse(Node* node, int depth);

private:
    unsigned int seed; // 던전의 랜덤 시드값
    EventManager eventManager; // EventManager 인스턴스, 사실상 맵
};
#endif // DUNGEON_H
// Dungeon 클래스 변수 생성하고 생성자로 탐험 맵 생성, 그 후 Main 진행 함수를 이걸로 진행,
// 던전 생성자를 지금 상태로 가자, 나중에 추가로 던전 생성을 할 수도 있으니