#include <iostream>
#include "CharacterTest.cpp"

#define GREEN "\033[0;32m"
#define WHITE "\033[m"


int main() 
{

    AllTests::runAllTests();
    CharacterTest::runTests();
    WizardTest::runTests();
    KnightTest::runTests();

    return 0;
}
