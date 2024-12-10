#pragma once
#include "Item.h"
#include "DrugMarket.h"
#include <vector>
#include <string>

class City {
private:
    std::string name; // ���� �̸�
    float inflation;

public:
    City(const std::string& name, float inflation = 1.0f);
    DrugMarket drugMarket; // ���� ����
    void updateInflation();  // ���÷��̼� ������Ʈ
    void updatePrices();     // ������ ���� ���� ������Ʈ
    DrugMarket& getDrugMarket();

    
    std::string getName() const;                       // ���� �̸� ��ȯ
    void printCityInfo() const;                        // ���� ���� ���
};

