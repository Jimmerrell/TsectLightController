#pragma once

#include <iostream>
#include <string>
#include <map>


namespace Utils
{
    static enum COLOR
    {
        RED = 31,
        GREEN = 32,
        YELLOW = 33,
        WHITE = 37
    };

    static inline void print(std::string str, COLOR color = COLOR::WHITE, int newLine = 1)
    {
        std::string output;
        
        output += "\033[1;";

        output += std::to_string(color);

        output += 'm';

        output += str;

        output += "\033[0m";

        std::cout << output;

        for (int i = 0; i < newLine; i++)
            std::cout << "\n";
    }
};

