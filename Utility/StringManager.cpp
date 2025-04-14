#include <iostream>
#include <string>
#include"string.h"
#include "StringManager.h"

StringManager* StringManager::SInstance = nullptr;

 StringManager* StringManager::GetInstance()
{
    if (SInstance == nullptr)
    {
        SInstance = new StringManager();
    }
    return SInstance;
}

std::string StringManager::forgh(std::string main,int order) {
    if (main.size() == 6) { // ’·‚³‚ª7
        std::string part1 = main.substr(0, 3);
        std::string part2 = main.substr(3, 2);
        std::string part3 = main.substr(5, 1);

        switch (order)
        {
        case 1:
            return part1;
            break;
        case 2:
            return part2;
            break;
        case 3:
            return part3;
            break;
        }
    }
    else {
        std::cerr << "Invalid input" << std::endl;
    }
    return std::string();
}