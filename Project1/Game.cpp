#include "Game.h"
#include <iostream>
#include <chrono>
#include <thread>
// ������: �ʱ�ȭ
Game::Game() : day(1) 
{   
    // ���� �ʱ�ȭ
    cities.push_back(City("New York"));
    cities.push_back(City("Los Angeles"));
    cities.push_back(City("Chicago"));
    cities.push_back(City("Miami"));
    cities.push_back(City("San Francisco"));
    cities.push_back(City("Boston"));
    cities.push_back(City("Seattle"));
    cities.push_back(City("Houston"));
    cities.push_back(City("Atlanta"));
    cities.push_back(City("Las Vegas"));

    //std::cout << "Game initialized with the following cities:\n";
}

// ���� ����

int getValidatedInput(const std::string& prompt);
void clearScreen();
void findCityNum(Player& player);

void Game::run() {
    std::cout << "Starting the game...\n";
    while (day <= 30) {
        if (player.getMoney() >= 2000000) {
            std::cout << "$" << player.getMoney() << "... Congratulations! You achive your goal.\n";
            return;
        }
        findCityNum(player);
        
        std::cout << "\n--------------- Day " << day << " ---------------\n";
        
        
        if (day >= 2) {
            
            // ���ú� ���� ������Ʈ
            for (auto& city : cities) {
                city.updateInflation();
                city.updatePrices();
            }
            //�̺�Ʈ 
            handleEvents();
            
            
            if (MarketShutdown) {
                std::cout << "������ �Ϸ絿�� ���Ǿ����ϴ�. " << std::endl;
                day++;
                continue;
            }
        }

        cities[numCity].printCityInfo(); // ���� ������ ���
        
        //�÷��̾� ���� ���� �� �Ǹ�
        //������ ����
        std::cout << "\nPlayer Money: " << player.printMoney() << std::endl;
        std::cout << "Choose an action:\n";
        std::cout << "1. Buy items\n";
        std::cout << "2. Sell items\n";
        std::cout << "3. Skip to next day\n";
        int choice;
        choice = getValidatedInput("Enter choice : ");

        switch (choice) {
        case 1: {
            handleBuy();
            break;
        }
        case 2: { // ������ �Ǹ�
            handleSell();
            break;
        }
        case 3:
            std::cout << "Skipping to the next day...\n";
            break;
        default:
            std::cout << "Invalid choice. Skipping day.\n";
        }
        clearScreen();
        day++;
    }

    std::cout << "Game over! 200�� �޷��� ������ ���߽��ϴ�..\n";
}

// �̺�Ʈ ó�� (�̱���)
void Game::handleEvents() {
    // �̺�Ʈ ������ ���⿡ �߰�
    event.updateRandomNumber();
    event.triggerEvent(player, cities[numCity]);

    if (event.getRandomNumber() == 6) {
        MarketShutdown = true;
    }
    else {
        MarketShutdown = false;
    }
}

int getValidatedInput(const std::string& prompt) {
    int input;

    while (true) {
        std::cout << prompt;
        std::cin >> input;

        if (std::cin.fail()) {
            // �Է� ���� ó��
            std::cin.clear(); // ��Ʈ�� ���� �ʱ�ȭ
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // �߸��� �Է� ����
            std::cout << "Invalid input. Please enter a valid number.\n";
        }
        else {
            // ��ȿ�� �Է��� ��� ��ȯ
            return input;
        }
    }
}

void Game::handleBuy () 
{
    int itemIndex = getValidatedInput("Enter item index to buy: ");
    int price = cities[numCity].getDrugMarket().getPrice(itemIndex); // ������ ���� ����
    std::cout << "���� ������ ���� :" << player.getMoney() / price << std::endl;
    int quantity = getValidatedInput("Enter quantity to buy: ");
    
    std::string itemName = cities[numCity].getDrugMarket().getNameByIndex(itemIndex); // �ε����� ���� �̸�
    
    if (price > 0) {
        player.buyItem(itemName, price, quantity);
    }
    else {
        std::cout << "Item not available in this city.\n";
    }
}

void Game::handleSell() 
{
    player.printInventory(); // �÷��̾� �κ��丮 ���

    int itemIndex = getValidatedInput("Enter item index to sell: ");
    int quantity = getValidatedInput("Enter quantity to sell: ");
    std::string itemName = cities[numCity].getDrugMarket().getNameByIndex(itemIndex);

    int price = cities[numCity].getDrugMarket().getPrice(itemIndex);
    if (price > 0) {
        player.sellItem(itemName, price, quantity);
    }
    else {
        std::cout << "No market for this item in this city.\n";
    }
}

void clearScreen() {
    std::cout << "\033[2J";   //\033[2J: ȭ�� ��ü �����.
    std::cout << "\033[1;1H"; //\033[1;1H: Ŀ���� �� ��(1, 1)�� �̵�.
}


void findCityNum(Player& player)
{
    const char* states[] = { "���ø� �̵��մϴ�.", "���ø� �̵��մϴ�..", "���ø� �̵��մϴ�..." };

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            clearScreen(); // ȭ�� ����� �Լ� �ʿ�
            std::cout << states[j] << std::endl << std::flush;
            std::this_thread::sleep_for(std::chrono::milliseconds(200)); // 200ms ���
        }
    }
    clearScreen();
    player.moveToCity(); // �÷��̾ ���÷� �̵�
}