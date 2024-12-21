#pragma once
#ifndef DUNGEON_H
#define DUNGEON_H


// 이벤트가 어떤게 일어날지의 기본 노드
// Node가 이진트리 형태로 연결 
// 던전을 돌때 사용할 class
// 생성 후 traverse에서 모든 함수가 진행 될 예정이다
// 던전은 단 1개만 사용 예정
#include "EventManager.h"


// 던전 노드, generateNode 함수로 이진트리 생성 깊이 5
class Node {
public:
    // 이 변수로 IEvent 부보클래스 상속받은 이벤트 클래스 연결
    // 클래스를 연결하여 객체 지향적으로 관리 -> 클래스 트리거 발동시 알아서 랜덤으로 발생
    IEvent* event;;
    Node* left;
    Node* right;
    // 생성자, 호출시 getRandomEvent로 인수 받아옴
    Node(IEvent* event) : event(event), left(nullptr), right(nullptr) {}
    // 왼쪽, 오른쪽 주소로 이동하여 차레대로 데이터 삭제
    ~Node() {
        delete left;
        delete right;
    }
};
// 던전 탐험시 이 함수의 traverseDungeon 호출하여 진행 예정
// 탐험 중 이벤트 처리 및 확인 진행 예정
class Dungeon {
public:
    // 이어하기 시 가지고 있는 Seed 값 불러와서 진행 예정
    Dungeon(unsigned int seed);
    // 새로 시작시 seed 값 랜덤 지정
    Dungeon();
    // 사용한 노드 삭제
    ~Dungeon();
    // root 있을경우 삭제 후 generateNode 호출
    void generateDungeon(int depth = 0);
    // root 없을경우 이상 발생이라 판단하여 리턴, 아닐경우 traverse 호출
    void traverseDungeon();

private:
    // 게임에서 사용할 seed 값
    unsigned int seed;
    EventManager eventManager;  // EventManager 객체
    Node* root;
    // Root 생성, 깊이 5까지 이진트리로 랜덤 이벤트로 생성
    Node* generateNode(int depth);
    // 해당 이벤트 트리거 후 왼쪽, 오른쪽 선택하여 진행
    // 깊이 5까지 도달시 종료
    void traverse(Node* node, int depth);
};
#endif // DUNGEON_H
// Dungeon 클래스 변수 생성하고 생성자로 탐험 맵 생성, 그 후 Main 진행 함수를 이걸로 진행,
// 던전 생성자를 지금 상태로 가자, 나중에 추가로 던전 생성을 할 수도 있으니