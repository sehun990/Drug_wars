#include "City.h"
#include <iostream>
#include <cstdlib>

// ������
City::City(const std::string& name, float inflation)
    : name(name), inflation(inflation) {}

// ���÷��̼� ������Ʈ
void City::updateInflation() {
    // ���ѵ� ������ ������ ���÷��̼� ���� (��: 0.9 ~ 1.1)
    float change = generateRandomFloat(-0.1, 0.1);// -0.1 ~ +0.1
    inflation += change;

    // ���÷��̼� �� ���� (��: �ּ� 0.8, �ִ� 1.2)
    if (inflation < 0.8f) inflation = 0.8f;
    if (inflation > 1.2f) inflation = 1.2f;
}

// ������ ���� ���� ������Ʈ
void City::updatePrices() {
    drugMarket.applyInflation(inflation);
}

// ���� �̸� ��ȯ
std::string City::getName() const {
    return name;
}

// ���� ���� ���
void City::printCityInfo() const {
    std::cout << "City: " << name << "\n";
    drugMarket.printDrugs(name);
}

DrugMarket& City::getDrugMarket() {
    return drugMarket;
}
