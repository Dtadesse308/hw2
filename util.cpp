#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/

    // I'll have dinner 
std::set<std::string> parseStringToWords(string rawWords)
{
set<string> words;
string currWord = "";

for (int i = 0; i < rawWords.length(); i++){
   
    
     //if a capital letter or a lowercase letter
     if ( ((rawWord[i]) >= 65 && (rawWord[i] <= 90)) || (( (rawWord[i]) >= 97 ) && (rawWord[i] <= 122) ) || 
     ((rawWord[i]) >= 48 ) && (rawWord[i] <= 57)  ) ){
         couter++;
         currWord += rawWord[i];
         
     }
     else {
        if (currWord.length() >= 2){
            words.insert(currWord);         
            currWord = "";
        }
     }

}

}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
