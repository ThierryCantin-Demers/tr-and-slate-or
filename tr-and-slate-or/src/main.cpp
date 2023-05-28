#include <iostream>
#include "TranslationManager.h"

using namespace translation;

int main()
{
    TranslationManager::getInstance().setLanguage( "fr" );
    std::cout << TR( "My horse is fat." ) << std::endl;
    std::cout << "Hello, World!" << std::endl;
}
