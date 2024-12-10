#include "Item.h"

// 생성자
Item::Item(const std::string& name, int basePrice, int quantity)
    : name(name), basePrice(basePrice), quantity(quantity) {}

// 가격 반환
int Item::getPrice() const {
    return basePrice;
}

// 이름 반환
std::string Item::getName() const {
    return name;
}

// 수량 설정
void Item::setQuantity(int newQuantity) {
    quantity = newQuantity;
}

void Item::setPrice(int newPrice) {
    basePrice = newPrice;
}

bool Item::operator==(const Item& other) const {
    return name == other.name; // 아이템 이름이 같으면 동일하다고 간주
}