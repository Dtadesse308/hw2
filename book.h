#include <iostream>
#include "product.h"


class book : public product{
    
    std::set<std::string> keywords();

    std::string displayString();

    private: 
    std::string authorName;
    int ISBN;
}