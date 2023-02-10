#include <iostream>
#include <string>
#include "movie.h"
#include <set>
#include "util.h"
#include <sstream>
#include<string>

using namespace std;


std::set<std::string> Movie::keywords() const{

    set<string> keyWords;
		set<string> key2;
		set<string> key3;

    keyWords =  parseStringToWords (name_)  ;

    key2 = parseStringToWords(genre_) ;

	  set<string>::iterator it1;
    
    for (it1 = keyWords.begin(); it1 != keyWords.end(); ++it1){   
        key3.insert(*it1);
    }

    for (it1 = key2.begin(); it1 != key2.end(); ++it1){
        key3.insert(*it1);
    }

    return key3;
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

	stringstream ss;

	 ss << name_ << '\n' << "Genre: " << genre_
	 <<  " Rating: " << rating_ << '\n' 
	 <<std::fixed<<setprecision(2) << price_ <<" "
	 << qty_<< " left";
			

			return ss.str();

}

bool Movie::isMatch(std::vector<std::string>& searchTerms) const{
    return 0;
}

void Movie::dump(std::ostream& os) const{
     os << category_ << "\n" << name_ << std::fixed<<setprecision(2)<<"\n" << price_ << "\n" << qty_ << "\n" << genre_ <<  "\n" << rating_ <<endl;
}

