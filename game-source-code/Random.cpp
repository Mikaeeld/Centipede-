#include "Random.h"

bool randomBool(const float p) {
    auto rd = std::random_device();
    auto gen = std::mt19937{rd()};
    auto dist = std::uniform_real_distribution<float>(0, 1);
    return (dist(gen) < p);
}

int randomInt(const int begin, const int end){
    auto rd = std::random_device();
    auto gen = std::mt19937{rd()};
    auto dist = std::uniform_int_distribution<int>(begin, end);
    return dist(gen);
}