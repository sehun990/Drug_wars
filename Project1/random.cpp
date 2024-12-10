#include "random.h"
// �Լ� ����
float generateRandomFloat(float min, float max) {
    static std::random_device rd;  // ���� �õ�
    static std::mt19937 gen(rd()); // ���� ���� ����
    std::uniform_real_distribution<> distrib(min, max);
    return distrib(gen);
}
