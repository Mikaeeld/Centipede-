#include "Random.h"

bool GameRandom::randomBool(const float p)
{
    float val = (float)rand() / RAND_MAX;
    return (val < p);
}

int GameRandom::randomInt(const int begin, const int end)
{
    int val = begin + (std::rand() % (end - begin + 1));
    return val;
}