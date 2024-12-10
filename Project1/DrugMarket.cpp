#include "DrugMarket.h"
#include <cstdlib>
#include <ctime>
#include <iomanip>  
// static 멤버 초기화
int DrugMarket::drugIndexCounter = 1;

// 생성자
DrugMarket::DrugMarket() : drugInflation(1.0f) {
    drugs.emplace_back(Cocaine());
    drugs.emplace_back(Marijuana());
    drugs.emplace_back(Methamphetamine());
    drugs.emplace_back(Heroin());
    drugs.emplace_back(MDMA());
}

// 마약 추가
void DrugMarket::addDrug(const std::string& name, int basePrice, int quantity, int risk) {
    drugs.emplace_back(name, basePrice, quantity, risk);
}

// 마약 정보 출력
void DrugMarket::printDrugs(const std::string& cityName) const {
    std::cout << "Drugs available in " << cityName << ":\n-------------------------------------\n";
    for (std::size_t i = 0; i < drugs.size(); ++i) {
        const auto& drug = drugs[i];
        std::cout << "[" << i << "] " << drug.getName()
            << ": $" << drug.getPrice() << "\n";
    }
    std::cout << "-------------------------------------\n";
}

// 특정 마약 가격 반환
int DrugMarket::getPrice(int itemIndex) const {
    if (itemIndex >= 0 && itemIndex < static_cast<int>(drugs.size())) {
        return drugs[itemIndex].getPrice();
    }
    std::cerr << "Error: Invalid item index.\n";
    return -1;
}

// 특정 마약 이름 반환
std::string DrugMarket::getNameByIndex(int itemIndex) const {
    if (itemIndex >= 0 && itemIndex < static_cast<int>(drugs.size())) {
        return drugs[itemIndex].getName();
    }
    std::cerr << "Error: Invalid item index.\n";
    return "";
}

// 인플레이션 적용
void DrugMarket::applyInflation(float inflation) {
     // 한 번만 호출
    for (auto& drug : drugs) {
        updateInflation(); 
        
        int basePrice = drug.getPrice();
        if (basePrice <= 0) 
        {
            basePrice = 1;
        }
        int newPrice = static_cast<int>(basePrice * inflation * drugInflation);
        drug.setPrice(newPrice);
    }
}

// 인플레이션 업데이트
void DrugMarket::updateInflation() {
    float change = generateRandomFloat(-0.1, 0.2); // -0.1 ~ +0.1
    if ((drugInflation + change) > 0) {
        drugInflation += change;
    }
    
    if (drugInflation < 0.8f) drugInflation *= 1.3f; // 값이 몰리는 것을 방지
    if (drugInflation > 1.3f) drugInflation *= 0.8f;
}
