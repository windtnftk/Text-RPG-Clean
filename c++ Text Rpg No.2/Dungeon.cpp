#pragma once
#include "pch.h"
#include "EventManager.h"
#include "IEvent.h"
#include "Dungeon.h"
#include <chrono>
#pragma message("IEvent.h included successfully")
Dungeon::Dungeon(unsigned int seed)
    : seed(seed), eventManager(seed), root(nullptr) {
    eventManager.addEvent(std::make_unique<EnemyEvent>(eventManager.gen));
    eventManager.addEvent(std::make_unique<MysteriousEvent>(eventManager.gen));
    generateDungeon();  // 던전 트리 생성
}

Dungeon::Dungeon()
    : seed(static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count())),
    eventManager(seed), root(nullptr) {
    eventManager.addEvent(std::make_unique<EnemyEvent>(eventManager.gen));
    eventManager.addEvent(std::make_unique<MysteriousEvent>(eventManager.gen));
    generateDungeon();
}

Dungeon::~Dungeon() {
    delete root;
    delete &eventManager;
}

void Dungeon::generateDungeon(int depth) {
    if (root) delete root;
    root = generateNode(depth);
}

Node* Dungeon::generateNode(int depth) {
    if (depth > 5) return nullptr;

    IEvent* event = eventManager.getRandomEvent(); // 원본 객체 참조
    Node* newNode = new Node(event);

    newNode->left = generateNode(depth + 1);
    newNode->right = generateNode(depth + 1);

    return newNode;
}

void Dungeon::traverse(Node* node, int depth) {
    if (!node || depth > 5) return;
    // 생성한 객체중 현재 노드의 연결된 객체 클래스에서 트리거 작동
    node->event->trigger(depth);

    if (node->left && node->right) {
        std::cout << "선택하세요: [1] 왼쪽 or [2] 오른쪽\n";
        int choice = CinAuto();
        if (choice == 1) traverse(node->left, depth + 1);
        else traverse(node->right, depth + 1);
    }
    else {
        std::cout << "No more paths. End of dungeon.\n";
    }
}

void Dungeon::traverseDungeon() {
    if (!root) {
        std::cout << "Dungeon is empty. Generate it first.\n";
        return;
    }
    traverse(root, 0);
}
