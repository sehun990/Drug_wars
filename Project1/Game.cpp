#include "Game.h"
#include <iostream>
#include <chrono>
#include <thread>
// 생성자: 초기화
Game::Game() : day(1) 
{   
    // 도시 초기화
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

// 게임 실행

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
            
            // 도시별 가격 업데이트
            for (auto& city : cities) {
                city.updateInflation();
                city.updatePrices();
            }
            //이벤트 
            handleEvents();
            
            
            if (MarketShutdown) {
                std::cout << "시장이 하루동안 폐쇠되었습니다. " << std::endl;
                day++;
                continue;
            }
        }

        cities[numCity].printCityInfo(); // 도시 아이템 출력
        
        //플레이어 마약 구매 및 판매
        //선택지 고르기
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
        case 2: { // 아이템 판매
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

    std::cout << "Game over! 200만 달러를 모으지 못했습니다..\n";
}

// 이벤트 처리 (미구현)
void Game::handleEvents() {
    // 이벤트 로직을 여기에 추가
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
            // 입력 실패 처리
            std::cin.clear(); // 스트림 상태 초기화
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 잘못된 입력 제거
            std::cout << "Invalid input. Please enter a valid number.\n";
        }
        else {
            // 유효한 입력일 경우 반환
            return input;
        }
    }
}

void Game::handleBuy () 
{
    int itemIndex = getValidatedInput("Enter item index to buy: ");
    int price = cities[numCity].getDrugMarket().getPrice(itemIndex); // 도시의 마약 가격
    std::cout << "구매 가능한 개수 :" << player.getMoney() / price << std::endl;
    int quantity = getValidatedInput("Enter quantity to buy: ");
    
    std::string itemName = cities[numCity].getDrugMarket().getNameByIndex(itemIndex); // 인덱스의 마약 이름
    
    if (price > 0) {
        player.buyItem(itemName, price, quantity);
    }
    else {
        std::cout << "Item not available in this city.\n";
    }
}

void Game::handleSell() 
{
    player.printInventory(); // 플레이어 인벤토리 출력

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
    std::cout << "\033[2J";   //\033[2J: 화면 전체 지우기.
    std::cout << "\033[1;1H"; //\033[1;1H: 커서를 맨 위(1, 1)로 이동.
}


void findCityNum(Player& player)
{
    const char* states[] = { "도시를 이동합니다.", "도시를 이동합니다..", "도시를 이동합니다..." };

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            clearScreen(); // 화면 지우기 함수 필요
            std::cout << states[j] << std::endl << std::flush;
            std::this_thread::sleep_for(std::chrono::milliseconds(200)); // 200ms 대기
        }
    }
    clearScreen();
    player.moveToCity(); // 플레이어가 도시로 이동
}