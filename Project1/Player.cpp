#include "Player.h"


// ������: �ʱ� �� ����
Player::Player() : money(3000) {}

// ������ ����
int Player::moveToCity() {
    return generateRandomFloat(0, 10);
}

void Player::buyItem(const std::string& itemName, int price, int quantity) {
    int totalCost = price * quantity;
    if (money >= totalCost) {
        money -= totalCost;

        bool itemFound = false;
        for (auto& invItem : inventory) {
            if (invItem.getName() == itemName) {
                invItem.quantity += quantity;   // ���� ������Ʈ
                itemFound = true;
                break;
            }
        }

        if (!itemFound) { // �������� �ʴ� �������� ��
            std::cout << "Add Item in inventory\n"; 
            inventory.push_back(Item(itemName, price, quantity)); // ���ο� ������ �߰�
            return;
        }
        std::cout << "Bought " << quantity << " " << itemName << "(s).\n";
    }
    else {
        std::cout << "Not enough money to buy " << quantity << " " << itemName << "(s).\n"; // ���� ���ġ ���� ��
    }
}


void Player::sellItem(const std::string& itemName, int price, int quantity) {
    for (auto& invItem : inventory) {
        if (invItem.getName() == itemName) {
            if (invItem.quantity >= quantity) {
                invItem.quantity -= quantity; // ���� ����
                money += price * quantity;

                std::cout << "Sold " << quantity << " " << itemName << "(s).\n";

                if (invItem.quantity == 0) {
                    inventory.erase(std::remove(inventory.begin(), inventory.end(), invItem), inventory.end());
                }
                return;
            }
            else {
                std::cout << "Not enough " << itemName << "(s) to sell.\n";
                return;
            }
        }
    }

    std::cout << "You don't have any " << itemName << " to sell.\n";
}

void Player::addMoney(int amount) {
    money += amount;
    if (money < 0) {
        money = 0; // ���� ������ ���� �ʵ��� ó��
    }
}

// ���� �� ��ȯ
int Player::getMoney() const {
    return money;
}

std::string Player::printMoney() const {
    int money = getMoney(); // �÷��̾��� �� ��������
    std::string moneyStr = std::to_string(money); // ���ڸ� ���ڿ��� ��ȯ
    std::string formattedMoney;

    int count = 0;
    for (auto it = moneyStr.rbegin(); it != moneyStr.rend(); ++it) {
        formattedMoney.insert(formattedMoney.begin(), *it); // �������� ����
        if (++count % 3 == 0 && (it + 1) != moneyStr.rend()) {
            formattedMoney.insert(formattedMoney.begin(), ','); // ��ǥ ����
        }
    }

    return "$" + formattedMoney; // $ ��ȣ �߰�
}





// �κ��丮 ���

void Player::printInventory() const {
    if (inventory.empty()) {
        std::cout << "Inventory is empty.\n";
        return;
    }

    std::cout << "Inventory:\n";
    for (const auto& item : inventory) {
        std::cout << "- " << item.getName() << ": " << item.quantity << "\n";
    }
}

