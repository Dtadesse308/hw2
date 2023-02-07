#include <iostream>
#include "product.h"


class book : public Product { 

    public:

    book(const std::string category, const std::string name, double price, int qty, std::string authorName, std::string ISBN);
    
    std::set<std::string> keywords() const;

    std::string displayString() const;


   virtual bool isMatch(std::vector<std::string>& searchTerms) const;


    virtual void dump(std::ostream& os) const;

    std::string getCategory();

    virtual std::string getSpecific() ;


    private: 

    std::string authorName_;
    std::string ISBN_;
};