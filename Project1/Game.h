#include "City.h"
#include "Player.h"
#include "Event.h"


class Game {
private:
    Player player;
    std::vector<City> cities; //���õ� ����
    int day;
    int numCity = 0;
    Event event;
    bool MarketShutdown;

public:
    Game();
    void run();
    void handleEvents();
    void handleBuy();
    void handleSell();


};


