#include "Player.h"


// 생성자: 초기 돈 설정
Player::Player() : money(3000) {}

// 아이템 구매
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
                invItem.quantity += quantity;   // 수량 업데이트
                itemFound = true;
                break;
            }
        }

        if (!itemFound) { // 존재하지 않는 아이템일 때
            std::cout << "Add Item in inventory\n"; 
            inventory.push_back(Item(itemName, price, quantity)); // 새로운 아이템 추가
            return;
        }
        std::cout << "Bought " << quantity << " " << itemName << "(s).\n";
    }
    else {
        std::cout << "Not enough money to buy " << quantity << " " << itemName << "(s).\n"; // 돈이 충분치 않을 때
    }
}


void Player::sellItem(const std::string& itemName, int price, int quantity) {
    for (auto& invItem : inventory) {
        if (invItem.getName() == itemName) {
            if (invItem.quantity >= quantity) {
                invItem.quantity -= quantity; // 수량 감소
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
        money = 0; // 돈이 음수가 되지 않도록 처리
    }
}

// 현재 돈 반환
int Player::getMoney() const {
    return money;
}

std::string Player::printMoney() const {
    int money = getMoney(); // 플레이어의 돈 가져오기
    std::string moneyStr = std::to_string(money); // 숫자를 문자열로 변환
    std::string formattedMoney;

    int count = 0;
    for (auto it = moneyStr.rbegin(); it != moneyStr.rend(); ++it) {
        formattedMoney.insert(formattedMoney.begin(), *it); // 역순으로 삽입
        if (++count % 3 == 0 && (it + 1) != moneyStr.rend()) {
            formattedMoney.insert(formattedMoney.begin(), ','); // 쉼표 삽입
        }
    }

    return "$" + formattedMoney; // $ 기호 추가
}





// 인벤토리 출력

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

