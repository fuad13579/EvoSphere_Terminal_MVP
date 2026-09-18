#pragma once

#include <random>

#include "Utils/Constants.h"

namespace EvoSphere
{
    struct OrbRoll
    {
        int first;
        int second;
        int total;
    };

    // Returns a random int between min and max
    // inline means that the function is defined in a header file and can be included in multiple translation units without violating the One Definition Rule (ODR). It allows the function to have internal linkage, meaning each translation unit gets its own copy of the function. This is particularly useful for small utility functions, as it avoids multiple definitions while still allowing the function to be used across different source files.
    inline int randomInt(int min, int max)
    {
        static std::random_device device; //random_device is a non-deterministic random number generator that provides random numbers based on hardware entropy sources, such as thermal noise or other unpredictable physical processes. It is used to seed the Mersenne Twister generator to ensure that the generated random numbers are not predictable and have a high degree of randomness.
        static std::mt19937 generator(device());//mt19937 is a pseudorandom number generator (PRNG) that implements the Mersenne Twister algorithm. It is a widely used PRNG known for its fast generation of high-quality random numbers with a long period (2^19937-1). The generator is seeded with the random_device to ensure that the generated random numbers are not predictable and have a high degree of randomness.

        std::uniform_int_distribution<int> distribution(min, max);//uniform_int_distribution is a random number distribution that produces integers uniformly distributed across a specified range. In this case, it generates random integers between the provided min and max values (inclusive). The distribution is used in conjunction with the Mersenne Twister generator to produce random numbers that follow the uniform distribution, ensuring that each integer in the specified range has an equal probability of being selected.
        return distribution(generator);//uniform_int_distribution is a random number distribution that produces integers uniformly distributed across a specified range. In this case, it generates random integers between the provided min and max values (inclusive). The distribution is used in conjunction with the Mersenne Twister generator to produce random numbers that follow the uniform distribution, ensuring that each integer in the specified range has an equal probability of being selected.
    }

    inline int rollOrb()//rollOrb is a function that simulates the rolling of a single orb in the game. It generates a random integer between ORB_MIN_VALUE and ORB_MAX_VALUE, which represent the minimum and maximum values that an orb can have. The function uses the randomInt function to generate the random value, ensuring that each possible orb value has an equal chance of being selected. This function is useful for determining the outcome of orb rolls during gameplay, adding an element of chance and unpredictability to the game mechanics.
    {
        return randomInt(ORB_MIN_VALUE, ORB_MAX_VALUE);
    }
    

    inline OrbRoll rollTwoOrbs()//rollTwoOrbs is a function that simulates the rolling of two orbs in the game. It generates two random integers, each representing the value of an orb, by calling the rollOrb function twice. The function then calculates the total value of the two rolled orbs by summing their individual values. Finally, it returns an OrbRoll struct containing the first orb's value, the second orb's value, and their total. This function is useful for determining the outcome of rolling two orbs during gameplay, adding an element of chance and unpredictability to the game mechanics.
    {
        const int first = rollOrb();
        const int second = rollOrb();

        return { first, second, first + second };
    }
    inline int randomIndex(int size)//size is the number of elements in the collection for which we want to generate a random index. The function will return a random integer between 0 and size - 1, which can be used as an index to access elements in the collection.
    {
        if (size <= 0)
        {
            return -1;
        }

        return randomInt(0, size - 1);//size-1 because the index is 0-based
    }
}