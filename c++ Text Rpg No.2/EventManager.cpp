#include "pch.h"
#include "EventManager.h"
#include "MysteriousEvent.h"

EventManager::EventManager(unsigned int seed) : seed(seed), gen(seed) {
    initMysteriousEvents();
    initEnemyEncounters();
    initItemPickups();
}

void EventManager::triggerEvent(EventType eventType, int depth) {
    if (eventType == EventType::Event) {
        std::uniform_int_distribution<> dist(0, mysteriousEvents.size() - 1);
        int randomIndex = dist(gen);
        handleMysteriousEvent(randomIndex, depth);
    }
    else if (eventType == EventType::Enemy) {
        handleEnemyEncounter(depth);
    }
    else if (eventType == EventType::Treasure) {
        handleItemPickup(depth);
    }
    else {
        std::cout << "Unknown event type!" << std::endl;
    }
}

void EventManager::initMysteriousEvents() {
    mysteriousEvents = {
        MysteriousEvent(EventList::test1),
        MysteriousEvent(EventList::test2),
        MysteriousEvent(EventList::test3)
    };
}

void EventManager::initEnemyEncounters() {
    enemyEncountersEasy = {
        []() { std::cout << "You encounter a weak goblin!" << std::endl; },
        []() { std::cout << "A lone skeleton approaches." << std::endl; }
    };
    enemyEncountersHard = {
        []() { std::cout << "You encounter a fierce orc!" << std::endl; },
        []() { std::cout << "A deadly wraith appears!" << std::endl; }
    };
}

void EventManager::initItemPickups() {
    itemPickupsBasic = {
        []() { std::cout << "You found a basic health potion." << std::endl; },
        []() { std::cout << "You picked up a rusty sword." << std::endl; }
    };
    itemPickupsRare = {
        []() { std::cout << "You found a rare enchanted staff!" << std::endl; },
        []() { std::cout << "You picked up an ancient amulet of power." << std::endl; }
    };
}

void EventManager::handleMysteriousEvent(int eventIndex, int depth) {
    if (eventIndex >= 0 && eventIndex < mysteriousEvents.size()) {
       
        mysteriousEvents[eventIndex].trigger(depth);
    }
}

void EventManager::handleEnemyEncounter(int depth) {
    if (depth <= 3) {
        std::uniform_int_distribution<> dist(0, enemyEncountersEasy.size() - 1);
        int randomIndex = dist(gen);
        if (randomIndex >= 0 && randomIndex < enemyEncountersEasy.size()) {
            enemyEncountersEasy[randomIndex]();
        }
    }
    else {
        std::uniform_int_distribution<> dist(0, enemyEncountersHard.size() - 1);
        int randomIndex = dist(gen);
        if (randomIndex >= 0 && randomIndex < enemyEncountersHard.size()) {
            enemyEncountersHard[randomIndex]();
        }
    }
}

void EventManager::handleItemPickup(int depth) {
    if (depth <= 3) {
        std::uniform_int_distribution<> dist(0, itemPickupsBasic.size() - 1);
        int randomIndex = dist(gen);
        if (randomIndex >= 0 && randomIndex < itemPickupsBasic.size()) {
            itemPickupsBasic[randomIndex]();
        }
    }
    else {
        std::uniform_int_distribution<> dist(0, itemPickupsRare.size() - 1);
        int randomIndex = dist(gen);
        if (randomIndex >= 0 && randomIndex < itemPickupsRare.size()) {
            itemPickupsRare[randomIndex]();
        }
    }
}