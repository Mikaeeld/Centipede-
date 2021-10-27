#pragma once

#include <random>

//Implements basic RNG functions

/**
 * @brief returns bool with random state
 * 
 * @param p float between 0 and 1, probability of returning true
 * @return true 
 * @return false 
 */
bool randomBool(const float p = 0.5);

/**
 * @brief Returns a random integer within provided range
 * 
 * @param begin Beginning of range
 * @param end End of Range
 * @return int 
 */
int randomInt(const int begin, const int end);