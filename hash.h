#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <cctype>
#include <ctime>
#include <cstdlib>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
				if(k == "") return 0;
        unsigned long long w[5] = {0, 0, 0, 0, 0};
				int index = k.size()-1;
				for(unsigned int i = 0; i < (k.size()-1)/6 + 1; i++) {
					int multiplier = 1;
					for(int j = 5; j >= 0; j--) {
						w[4-i] += letterDigitToNumber(k[index])*multiplier;
						multiplier*=36;
						index --;
						if(index < 0) break;
					}
					
				}
				unsigned long long hashValue = 0;
				for(int i = 0; i < 5; i++) {
					hashValue += rValues[i]*w[i];
				}
				return hashValue;

    }
    
    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
				HASH_INDEX_T returnNum;
				if(letter > 96) {
					returnNum = int(letter - 97);
				}
				else if (letter > 64) {
					returnNum = int(letter - 65);
				}
				else {
					returnNum = int(letter - 22);
				}
				return returnNum;
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
