#pragma once
#include "Item.h"
#include "DrugMarket.h"
#include <vector>
#include <string>

class City {
private:
    std::string name; // 도시 이름
    float inflation;

public:
    City(const std::string& name, float inflation = 1.0f);
    DrugMarket drugMarket; // 마약 시장
    void updateInflation();  // 인플레이션 업데이트
    void updatePrices();     // 도시의 마약 가격 업데이트
    DrugMarket& getDrugMarket();

    
    std::string getName() const;                       // 도시 이름 반환
    void printCityInfo() const;                        // 도시 정보 출력
};

