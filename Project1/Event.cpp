#include "Event.h"

Event::Event() {
    updateRandomNumber();
}

void Event::updateRandomNumber() {
    if (predict != -1) {
        randomNumber = predict;
    }
    else {
        static std::random_device rd; // 시드 생성
        static std::mt19937 gen(rd()); // Mersenne Twister 엔진
        std::uniform_int_distribution<> distrib(1, 7); // 1부터 7까지 설정

        randomNumber = distrib(gen); // 랜덤 숫자 생성
    }
}

// 생성된 랜덤 숫자를 반환
int Event::getRandomNumber() const {
    return randomNumber;
}

//예측 랜덤 숫자
void Event::setPredict(int eventNumber) {
    predict = eventNumber;
}

void Event::clearPredict() {
    predict = -1;
}
// 랜덤 숫자에 따라 이벤트 실행
void Event::triggerEvent(Player& player, City& city) {
    if (predict != -1) {
        randomNumber = predict;
        const_cast<Event*>(this)->clearPredict();
    }

    switch (randomNumber) {
    case 1: // 경찰 등장
    {
        //std::cout << "Event 1: 경찰이 당신을 검문합니다!" << std::endl;
        int penalty = std::min(player.getMoney() / 10, 1000); 
        player.addMoney(-penalty);
        std::cout << "경찰에게 $" << penalty << "상납금을 바쳤습니다."
            << " 현재 자산: " << player.printMoney() << std::endl;
    }
    break;

    case 2: // 강도 등장
    {
        //std::cout << "Event 2: 강도가 당신을 습격했습니다!" << std::endl;
        int stolenMoney = std::min(player.getMoney() / 5, 500); // 자산의 20% 또는 최대 500$
        player.addMoney(-stolenMoney);
        std::cout << "$" << stolenMoney << "를 강탈당했습니다."
            << " 현재 자산: " << player.printMoney() << std::endl;
    }
    break;

    case 3: // 새로운 아이템 추가
    {
        //std::cout << "Event 3: 새로운 마약 아이템이 추가되었습니다!" << std::endl;
        city.getDrugMarket().addDrug("Special Drug", 1000, 20, 1); // 임시 아이템 추가
        std::cout << "도시 " << city.getName() << "에 새로운 아이템 'Special Drug'이 추가되었습니다."
            << std::endl;
    }
    break;

    case 4: // 가격 이벤트
    {
        //std::cout << "Event 4: 특정 마약 가격에 변동이 있습니다!" << std::endl;
        city.getDrugMarket().applyInflation(1.2f); // 특정 가격 상승
        std::cout << "도시 " << city.getName() << "의 일부 아이템 가격이 상승했습니다!" << std::endl;
    }
    break;

    case 5: // 특별 예언
    {
        //std::cout << "Event 5: 미래 예언! 다음 날 이벤트가 예고됩니다." << std::endl;
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(1, 7);

        int predictedEvent = distrib(gen);
        const_cast<Event*>(this)->setPredict(predictedEvent);  // 예언 저장
        const char* eventPrompt[] = { "","경찰이 당신을 검문할 것", "강도가 당신을 습격할 것", "새로운 마약 아이템이 추가 될 것", "특정 마약 가격에 변동이 있을 것", "미래 예언! 다음 날 이벤트가 예고될 것", "시장이 오늘 하루 동안 폐쇄될 것", ""};
        std::cout << "다음 도시의 사건은 " << eventPrompt[predictedEvent] << " 입니다....\n";
    }
    break;
      

    case 6: // 시장 폐쇄 //Game에서 예외처리를 해서 필요 유무를 잘 모르겠음
    {
        //std::cout << "Event 6: 시장이 오늘 하루 동안 폐쇄되었습니다!" << std::endl;
        std::cout << "아무 행동도 할 수 없습니다. 다음 날로 넘어갑니다." << std::endl;
    }
    break;

    case 7: // 아무 일도 없는 날
    {
       // std::cout << "Event 7: 오늘은 아무 일도 일어나지 않았습니다." << std::endl;
    }
    break;

    default:
        std::cout << "Unknown Event." << std::endl;
        break;
    }
}

