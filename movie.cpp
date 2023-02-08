#include <iostream>
#include <string>
#include "movie.h"
#include <set>

using namespace std;


std::set<std::string> Movie::keywords() const{

    set<string> keyWords;

    keyWords = parseStringToWords (name_) ;
    keyWords.insert(genre_);

    return keyWords;
}

Movie::Movie( const std::string category, const std::string name, double price, int qty, std::string genre, std::string rating)
 : Product(category,  name,  price, qty){
     
     genre_ = genre;
    rating_ = rating;
}

std::string Movie::getCategory(){
    return category_;
}

std::string Movie::getSpecific() {
    string specific = "";
    specific += (genre_ + '\n' + rating_);
    return specific;
}

std::string Movie::displayString() const{

string word = name_ + '\n';
word += "Genre: " + genre_ + " Rating: " + rating_ + '\n' 
+ to_string(price_) + " " + to_string(qty_) + " left.";

return word;
}

bool Movie::isMatch(std::vector<std::string>& searchTerms) const{
    return 0;
}

void Movie::dump(std::ostream& os) const{
     os << category_ << "\n" << name_ << std::fixed<<setprecision(2)<<"\n" << price_ << "\n" << qty_ << "\n" << genre_ <<  "\n" << rating_ <<endl;
}

