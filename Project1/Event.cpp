#include "Event.h"

Event::Event() {
    updateRandomNumber();
}

void Event::updateRandomNumber() {
    if (predict != -1) {
        randomNumber = predict;
    }
    else {
        static std::random_device rd; // �õ� ����
        static std::mt19937 gen(rd()); // Mersenne Twister ����
        std::uniform_int_distribution<> distrib(1, 7); // 1���� 7���� ����

        randomNumber = distrib(gen); // ���� ���� ����
    }
}

// ������ ���� ���ڸ� ��ȯ
int Event::getRandomNumber() const {
    return randomNumber;
}

//���� ���� ����
void Event::setPredict(int eventNumber) {
    predict = eventNumber;
}

void Event::clearPredict() {
    predict = -1;
}
// ���� ���ڿ� ���� �̺�Ʈ ����
void Event::triggerEvent(Player& player, City& city) {
    if (predict != -1) {
        randomNumber = predict;
        const_cast<Event*>(this)->clearPredict();
    }

    switch (randomNumber) {
    case 1: // ���� ����
    {
        //std::cout << "Event 1: ������ ����� �˹��մϴ�!" << std::endl;
        int penalty = std::min(player.getMoney() / 10, 1000); 
        player.addMoney(-penalty);
        std::cout << "�������� $" << penalty << "�󳳱��� ���ƽ��ϴ�."
            << " ���� �ڻ�: " << player.printMoney() << std::endl;
    }
    break;

    case 2: // ���� ����
    {
        //std::cout << "Event 2: ������ ����� �����߽��ϴ�!" << std::endl;
        int stolenMoney = std::min(player.getMoney() / 5, 500); // �ڻ��� 20% �Ǵ� �ִ� 500$
        player.addMoney(-stolenMoney);
        std::cout << "$" << stolenMoney << "�� ��Ż���߽��ϴ�."
            << " ���� �ڻ�: " << player.printMoney() << std::endl;
    }
    break;

    case 3: // ���ο� ������ �߰�
    {
        //std::cout << "Event 3: ���ο� ���� �������� �߰��Ǿ����ϴ�!" << std::endl;
        city.getDrugMarket().addDrug("Special Drug", 1000, 20, 1); // �ӽ� ������ �߰�
        std::cout << "���� " << city.getName() << "�� ���ο� ������ 'Special Drug'�� �߰��Ǿ����ϴ�."
            << std::endl;
    }
    break;

    case 4: // ���� �̺�Ʈ
    {
        //std::cout << "Event 4: Ư�� ���� ���ݿ� ������ �ֽ��ϴ�!" << std::endl;
        city.getDrugMarket().applyInflation(1.2f); // Ư�� ���� ���
        std::cout << "���� " << city.getName() << "�� �Ϻ� ������ ������ ����߽��ϴ�!" << std::endl;
    }
    break;

    case 5: // Ư�� ����
    {
        //std::cout << "Event 5: �̷� ����! ���� �� �̺�Ʈ�� ����˴ϴ�." << std::endl;
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(1, 7);

        int predictedEvent = distrib(gen);
        const_cast<Event*>(this)->setPredict(predictedEvent);  // ���� ����
        const char* eventPrompt[] = { "","������ ����� �˹��� ��", "������ ����� ������ ��", "���ο� ���� �������� �߰� �� ��", "Ư�� ���� ���ݿ� ������ ���� ��", "�̷� ����! ���� �� �̺�Ʈ�� ����� ��", "������ ���� �Ϸ� ���� ���� ��", ""};
        std::cout << "���� ������ ����� " << eventPrompt[predictedEvent] << " �Դϴ�....\n";
    }
    break;
      

    case 6: // ���� ��� //Game���� ����ó���� �ؼ� �ʿ� ������ �� �𸣰���
    {
        //std::cout << "Event 6: ������ ���� �Ϸ� ���� ���Ǿ����ϴ�!" << std::endl;
        std::cout << "�ƹ� �ൿ�� �� �� �����ϴ�. ���� ���� �Ѿ�ϴ�." << std::endl;
    }
    break;

    case 7: // �ƹ� �ϵ� ���� ��
    {
       // std::cout << "Event 7: ������ �ƹ� �ϵ� �Ͼ�� �ʾҽ��ϴ�." << std::endl;
    }
    break;

    default:
        std::cout << "Unknown Event." << std::endl;
        break;
    }
}

