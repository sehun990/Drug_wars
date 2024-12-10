#include "random.h"
// 함수 정의
float generateRandomFloat(float min, float max) {
    static std::random_device rd;  // 랜덤 시드
    static std::mt19937 gen(rd()); // 난수 생성 엔진
    std::uniform_real_distribution<> distrib(min, max);
    return distrib(gen);
}
