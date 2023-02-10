#include <iostream>
#include <string>
#include "book.h"
#include "util.h"
#include <sstream>
#include<string>

using namespace std;


book::book(const std::string category, const std::string name, double price, int qty, std::string authorName, string ISBN)
 : Product(category,  name,  price, qty){

     authorName_ = authorName;
     ISBN_ = ISBN;
 }

std::set<std::string> book::keywords() const{


    set<string> keyWords;
    

    keyWords = parseStringToWords(name_) ;

    set<string> authorKeys = parseStringToWords(authorName_);
    set<string>::iterator it;

    for (it = authorKeys.begin(); it != authorKeys.end(); ++it){
        keyWords.insert(*it);
    }
    
    
    keyWords.insert(ISBN_);

    return keyWords;

}
std::string book::getCategory(){
    return category_;
}

std::string book::getSpecific() {
    string specific = "";
    specific += (ISBN_ + '\n' + authorName_);
    return specific;
}

std::string book::displayString() const{

    stringstream ss;
    

    ss << name_ << '\n'<<
     "Author: " << authorName_ << " ISBN: " << ISBN_ << '\n' 
    <<std::fixed<<setprecision(2)<< price_ << " " << qty_ << " left.";

    return ss.str();
}


   bool book::isMatch(std::vector<std::string>& searchTerms) const{
       return 0;
   }


    void book::dump(std::ostream& os) const{
        os << category_ << "\n" <<std::fixed<<setprecision(2)<< name_ << "\n" << price_ << "\n" << qty_ << "\n" << ISBN_ <<  "\n" << authorName_ <<endl;
    }
