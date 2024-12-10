#pragma once
#include "Item.h"
#include <vector>
#include <string>
#include <iostream>

class DrugMarket {
private:
    std::vector<Drug> drugs;          // 마약 리스트
    static int drugIndexCounter;      // 고유 Drug 인덱스
    float drugInflation;              // 현재 인플레이션 값

public:
    DrugMarket();                     // 생성자
    void addDrug(const std::string& name, int basePrice, int quantity, int risk);
    void printDrugs(const std::string& cityName) const;
    int getPrice(int itemIndex) const;
    std::string getNameByIndex(int itemIndex) const;
    void applyInflation(float inflation);
    void updateInflation();
};
