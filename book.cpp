#include <iostream>
#include <string>
#include "book.h"
#include "util.h"

using namespace std;


book::book(const std::string category, const std::string name, double price, int qty, std::string authorName, string ISBN)
 : Product(category,  name,  price, qty){

     authorName_ = authorName;
     ISBN_ = ISBN;
 }

std::set<std::string> book::keywords() const{


    set<string> keyWords;

    keyWords = parseStringToWords (name_) ;
    keyWords.insert(ISBN_);

    return keyWords;

}

std::string book::displayString() const{

    string word = name_ + '\n';
    word += "Author: " + authorName_ + " ISBN: " + ISBN_ + '\n' 
    + to_string(price_) + " " + to_string(qty_) + " left.";

    return word;
}


   bool book::isMatch(std::vector<std::string>& searchTerms) const{
       return 0;
   }


    void book::dump(std::ostream& os) const{
        os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << authorName_ <<  "\n" << ISBN_ <<endl;
    }
