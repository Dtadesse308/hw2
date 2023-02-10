#include <iostream>
#include <string>
#include "clothing.h"

using namespace std;

clothing::clothing(const std::string category, const std::string name, double price, int qty, std::string size, std::string brand) 
 : Product(category,  name,  price, qty) {

    size_ = size;
    brand_ = brand;
 }

std::set<std::string> clothing::keywords() const{
    
    set<string> keyWords;
    set<string> brandsSet = parseStringToWords(brand_);

    keyWords = parseStringToWords (name_) ;
    keyWords.insert(brandsSet.begin(), brandsSet.end() );

    return keyWords;
}

std::string clothing::getCategory(){
    return category_;
}

std::string clothing::getSpecific() {
    string specific = "";
    specific += (size_ + '\n' + brand_);
    return specific;
}

std::string clothing::displayString() const{

string word = name_ + '\n';
word += "Size: " + size_ + " Brand: " + brand_ + '\n' 
+ to_string(price_) + " " + to_string(qty_) + " left.";

    return word;
}


   bool clothing::isMatch(std::vector<std::string>& searchTerms) const{
       return 0;
   }

    void clothing::dump(std::ostream& os) const{
        os << category_ << "\n" <<std::fixed<<setprecision(2)<< name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ <<  "\n" << brand_ <<endl;
    }


