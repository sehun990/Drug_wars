#pragma once
#include <string>
#include "random.h"

class Item 
{
protected:
    std::string name;   // ������ �̸�
    int basePrice;      // �⺻ ����

public:
    int quantity;       // ����

    // ������
    Item(const std::string& name, int basePrice, int quantity = 0);

    // ���� �Ҹ���
    virtual ~Item() = default;

    // Getter
    virtual int getPrice() const;
    std::string getName() const;

    // Setter
    void setQuantity(int newQuantity);
    void setPrice(int newPrice);

    // ������ �����ε� (==)
    bool operator==(const Item& other) const;
};

class Drug : public Item
{
protected:
    int risk; 
    
public:
    // Drug ������
    static int indexCounter;
    Drug(const std::string& name, int basePrice, int quantity, int risk)
        : Item(name, basePrice, quantity), risk(risk) {} 

    int getPrice() const override {
        return basePrice; // ���赵�� ���� ���� ���
    }
};

class Cocaine : public Drug
{
public:
    Cocaine() : Drug("Cocaine(��ī��)", 120, 10, 90) {}
};

class Marijuana : public Drug
{
public:
    Marijuana() : Drug("Marijuana(����ȭ��)", 10, 15, 30) {}
};

class Methamphetamine : public Drug
{
public:
    Methamphetamine() : Drug("Methamphetamine(�ʷ���)", 20, 5, 95) {}
};

class Heroin : public Drug
{
public:
    Heroin() : Drug("Heroin(�����)", 100, 5, 95) {}
};

class MDMA : public Drug 
{
public:
    MDMA() : Drug("MDMA(�����ͽ�)", 20, 5, 95) {}
};