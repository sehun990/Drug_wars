#pragma once
#include "Player.h"
#include "City.h"
#include "random.h"

class Event {
private:
    int randomNumber; // ���� ���� ����
    int predict = -1;

public:
    Event(); // �����ڿ��� ���� ���� ����
    void updateRandomNumber();
    int getRandomNumber() const; // ������ ���� ���ڸ� ��ȯ
    void setPredict(int eventNumber);
    void clearPredict();
    void triggerEvent(Player& player, City& city);
    
};
