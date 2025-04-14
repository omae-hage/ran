#pragma once
#include <iostream>
#include <string>

class StringManager
{
private:
    static StringManager* SInstance;

public:
    static StringManager* GetInstance();
    std::string forgh(std::string main,int order);
};