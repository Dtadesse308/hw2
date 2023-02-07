
#include <iostream>
#include "product.h"


class clothing : public Product{

    public:
    
    clothing(const std::string category, const std::string name, double price, int qty, std::string size_, std::string brand_);

    std::set<std::string> keywords() const;

    std::string displayString() const;
       
   virtual bool isMatch(std::vector<std::string>& searchTerms) const;

    virtual void dump(std::ostream& os) const;

    


    private:
    std::string size_;
    std::string brand_;

};


