#pragma once
#include "Player.h"
#include "City.h"
#include "random.h"

class Event {
private:
    int randomNumber; // 랜덤 숫자 저장
    int predict = -1;

public:
    Event(); // 생성자에서 랜덤 숫자 생성
    void updateRandomNumber();
    int getRandomNumber() const; // 생성된 랜덤 숫자를 반환
    void setPredict(int eventNumber);
    void clearPredict();
    void triggerEvent(Player& player, City& city);
    
};
