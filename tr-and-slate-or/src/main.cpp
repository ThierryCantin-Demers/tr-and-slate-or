#include <iostream>
//#include "nlohmann/json.hpp"
#include "CTranslationManager.h"

//using json = nlohmann::json;
using namespace util;

int main()
{
    CTranslationManager::getInstance().setLanguage( "fr" );
    std::cout << TR( "My horse is fat." ) << std::endl;
    std::cout << "Hello, World!" << std::endl;
}
