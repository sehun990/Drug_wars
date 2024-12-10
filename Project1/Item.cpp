#include "Item.h"

// ������
Item::Item(const std::string& name, int basePrice, int quantity)
    : name(name), basePrice(basePrice), quantity(quantity) {}

// ���� ��ȯ
int Item::getPrice() const {
    return basePrice;
}

// �̸� ��ȯ
std::string Item::getName() const {
    return name;
}

// ���� ����
void Item::setQuantity(int newQuantity) {
    quantity = newQuantity;
}

void Item::setPrice(int newPrice) {
    basePrice = newPrice;
}

bool Item::operator==(const Item& other) const {
    return name == other.name; // ������ �̸��� ������ �����ϴٰ� ����
}