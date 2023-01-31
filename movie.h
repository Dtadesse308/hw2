#include <iostream>
#include "product.h"
using namespace std;

class movie : public product{

    std::set<std::string> keywords();

    std::string displayString();


    private:
    std::string genre;
    
}