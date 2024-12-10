#pragma once
#include "Item.h"
#include <vector>
#include <string>
#include <iostream>

class DrugMarket {
private:
    std::vector<Drug> drugs;          // ���� ����Ʈ
    static int drugIndexCounter;      // ���� Drug �ε���
    float drugInflation;              // ���� ���÷��̼� ��

public:
    DrugMarket();                     // ������
    void addDrug(const std::string& name, int basePrice, int quantity, int risk);
    void printDrugs(const std::string& cityName) const;
    int getPrice(int itemIndex) const;
    std::string getNameByIndex(int itemIndex) const;
    void applyInflation(float inflation);
    void updateInflation();
};
