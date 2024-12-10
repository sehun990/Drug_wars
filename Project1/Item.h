#pragma once
#include <string>
#include "random.h"

class Item 
{
protected:
    std::string name;   // 아이템 이름
    int basePrice;      // 기본 가격

public:
    int quantity;       // 수량

    // 생성자
    Item(const std::string& name, int basePrice, int quantity = 0);

    // 가상 소멸자
    virtual ~Item() = default;

    // Getter
    virtual int getPrice() const;
    std::string getName() const;

    // Setter
    void setQuantity(int newQuantity);
    void setPrice(int newPrice);

    // 연산자 오버로드 (==)
    bool operator==(const Item& other) const;
};

class Drug : public Item
{
protected:
    int risk; 
    
public:
    // Drug 생성자
    static int indexCounter;
    Drug(const std::string& name, int basePrice, int quantity, int risk)
        : Item(name, basePrice, quantity), risk(risk) {} 

    int getPrice() const override {
        return basePrice; // 위험도에 따라 가격 상승
    }
};

class Cocaine : public Drug
{
public:
    Cocaine() : Drug("Cocaine(코카인)", 120, 10, 90) {}
};

class Marijuana : public Drug
{
public:
    Marijuana() : Drug("Marijuana(마리화나)", 10, 15, 30) {}
};

class Methamphetamine : public Drug
{
public:
    Methamphetamine() : Drug("Methamphetamine(필로폰)", 20, 5, 95) {}
};

class Heroin : public Drug
{
public:
    Heroin() : Drug("Heroin(헤로인)", 100, 5, 95) {}
};

class MDMA : public Drug 
{
public:
    MDMA() : Drug("MDMA(엑스터시)", 20, 5, 95) {}
};