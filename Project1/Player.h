#pragma once
#include "Item.h"
#include "random.h"
#include <string>
#include <vector>
#include <iostream>

class Player {
private:
    int money;
    std::vector<Item> inventory; // Item ∞¥√º∏¶ ¿˙¿Â«œ¥¬ ∫§≈Õ

public:
    Player();
    int moveToCity(void);
    void buyItem(const std::string& item, int price, int quantity);
    void sellItem(const std::string& item, int price, int quantity);
    int getMoney() const;
    void addMoney(int amount);
    std::string printMoney() const;
    void printInventory() const;
};