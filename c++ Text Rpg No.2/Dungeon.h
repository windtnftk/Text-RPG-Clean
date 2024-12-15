#pragma once
#ifndef DUNGEON_H
#define DUNGEON_H








// 이벤트가 어떤게 일어날지의 기본 노드
// Node가 이진트리 형태로 연결 
// 던전을 돌때 사용할 class
// 생성 후 traverse에서 모든 함수가 진행 될 예정이다
// 던전은 단 1개만 사용 예정
#include "EventManager.h"
// NowCoding : 현재 던전 클래스 및 다른 클래스, 함수 정의-정리 필요 그 후 이벤트 함수 진행 요청
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
    EventManager eventManager;  // EventManager 객체
    Node* root;

    Node* generateNode(int depth);
    void traverse(Node* node, int depth);
};
#endif // DUNGEON_H
// Dungeon 클래스 변수 생성하고 생성자로 탐험 맵 생성, 그 후 Main 진행 함수를 이걸로 진행,
// 던전 생성자를 지금 상태로 가자, 나중에 추가로 던전 생성을 할 수도 있으니