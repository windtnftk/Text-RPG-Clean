#pragma once
#include "pch.h"
#include "EventManager.h"
#include "IEvent.h"
#include "Dungeon.h"
#include <chrono>
#pragma message("IEvent.h included successfully")
Dungeon::Dungeon(unsigned int seed)
    : seed(seed), eventManager(seed), root(nullptr) {
    generateDungeon();  // 던전 트리 생성
}

Dungeon::Dungeon()
    : seed(static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count())),
    eventManager(seed), root(nullptr) {
    generateDungeon();
}

Dungeon::~Dungeon() {
    delete root;
}

void Dungeon::generateDungeon(int depth) {
    if (root) delete root;
    root = generateNode(depth);
}

Node* Dungeon::generateNode(int depth) {
    if (depth > 5) return nullptr;

    std::unique_ptr<IEvent> event = eventManager.getRandomEvent();
    Node* newNode = new Node(std::move(event));

    newNode->left = generateNode(depth + 1);
    newNode->right = generateNode(depth + 1);

    return newNode;
}

void Dungeon::traverse(Node* node, int depth) {
    if (!node || depth > 5) return;

    node->event->trigger(depth);

    if (node->left && node->right) {
        std::cout << "선택하세요: [1] 왼쪽 or [2] 오른쪽\n";
        int choice;
        std::cin >> choice;

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
