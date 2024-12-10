#include "City.h"
#include <iostream>
#include <cstdlib>

// 생성자
City::City(const std::string& name, float inflation)
    : name(name), inflation(inflation) {}

// 인플레이션 업데이트
void City::updateInflation() {
    // 제한된 범위의 난수로 인플레이션 변동 (예: 0.9 ~ 1.1)
    float change = generateRandomFloat(-0.1, 0.1);// -0.1 ~ +0.1
    inflation += change;

    // 인플레이션 값 제한 (예: 최소 0.8, 최대 1.2)
    if (inflation < 0.8f) inflation = 0.8f;
    if (inflation > 1.2f) inflation = 1.2f;
}

// 도시의 마약 가격 업데이트
void City::updatePrices() {
    drugMarket.applyInflation(inflation);
}

// 도시 이름 반환
std::string City::getName() const {
    return name;
}

// 도시 정보 출력
void City::printCityInfo() const {
    std::cout << "City: " << name << "\n";
    drugMarket.printDrugs(name);
}

DrugMarket& City::getDrugMarket() {
    return drugMarket;
}
