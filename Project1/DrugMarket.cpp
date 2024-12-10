#include "DrugMarket.h"
#include <cstdlib>
#include <ctime>
#include <iomanip>  
// static ��� �ʱ�ȭ
int DrugMarket::drugIndexCounter = 1;

// ������
DrugMarket::DrugMarket() : drugInflation(1.0f) {
    drugs.emplace_back(Cocaine());
    drugs.emplace_back(Marijuana());
    drugs.emplace_back(Methamphetamine());
    drugs.emplace_back(Heroin());
    drugs.emplace_back(MDMA());
}

// ���� �߰�
void DrugMarket::addDrug(const std::string& name, int basePrice, int quantity, int risk) {
    drugs.emplace_back(name, basePrice, quantity, risk);
}

// ���� ���� ���
void DrugMarket::printDrugs(const std::string& cityName) const {
    std::cout << "Drugs available in " << cityName << ":\n-------------------------------------\n";
    for (std::size_t i = 0; i < drugs.size(); ++i) {
        const auto& drug = drugs[i];
        std::cout << "[" << i << "] " << drug.getName()
            << ": $" << drug.getPrice() << "\n";
    }
    std::cout << "-------------------------------------\n";
}

// Ư�� ���� ���� ��ȯ
int DrugMarket::getPrice(int itemIndex) const {
    if (itemIndex >= 0 && itemIndex < static_cast<int>(drugs.size())) {
        return drugs[itemIndex].getPrice();
    }
    std::cerr << "Error: Invalid item index.\n";
    return -1;
}

// Ư�� ���� �̸� ��ȯ
std::string DrugMarket::getNameByIndex(int itemIndex) const {
    if (itemIndex >= 0 && itemIndex < static_cast<int>(drugs.size())) {
        return drugs[itemIndex].getName();
    }
    std::cerr << "Error: Invalid item index.\n";
    return "";
}

// ���÷��̼� ����
void DrugMarket::applyInflation(float inflation) {
     // �� ���� ȣ��
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

// ���÷��̼� ������Ʈ
void DrugMarket::updateInflation() {
    float change = generateRandomFloat(-0.1, 0.2); // -0.1 ~ +0.1
    if ((drugInflation + change) > 0) {
        drugInflation += change;
    }
    
    if (drugInflation < 0.8f) drugInflation *= 1.3f; // ���� ������ ���� ����
    if (drugInflation > 1.3f) drugInflation *= 0.8f;
}
