/*******************************
 * Lab 3: exercise 1            *
 * Frequency table of words     *
 *******************************/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <utility>   //std::pair
#include <fstream>
#include <cassert>
#include <algorithm>

 /*******************************
  * 1. Declarations              *
  ********************************/

  // A function to test the tables created by the program
void test(const std::map<std::string, int>& t, const std::vector<std::pair<std::string, int>>& v,
    const std::string& file_name, int n);

void toLowerCase(std::string& word) {
    std::transform(word.begin(), word.end(), word.begin(), tolower);
}

bool isPunctuation(const char c) {
    //return (c == '.' || c == ',' || c == '!' || c == '?' || c == ':' || c == ';' || c == '-' || c == '(' || c == ')' || c == '"' || c == '\'');
    std::string chars = ".,!?:();\"";

    return chars.find(c) != std::string::npos; //true if c is found in chars 
    //std::string::npos As a return value, it is usually used to indicate no matches.
    //It actually means until the end of the string.
    //It is used as the value for a length parameter in the string’s member functions.
    //if no is found, it returns npos ie the end of the string
}

void removePunctuation(std::string& word) {
    word.erase(remove_if(word.begin(), word.end(), isPunctuation), word.end());
}
bool sortFunc(const std::pair<std::string, int>& pair1, const std::pair<std::string, int>& pair2) {
    if (pair1.second == pair2.second) {
        return pair1.first < pair2.first; // minst först
    }
    return pair1.second > pair2.second; // störst först
}

/*******************************
 * 2. Main function             *
 *******************************/

int main() {
    std::string name;
    std::cout << "Text file: ";
    std::cin >> name;

    std::ifstream in_File{ "../code/" + name };

    if (!in_File) {
        std::cout << "Could not open input file!!\n";
        return 0;
    }

    std::map<std::string, int> table;
    int counter{ 0 };  // to count total number of words read from the input file

    //ADD CODE to build table
    std::string in_word;
    while (in_File >> in_word) {
        removePunctuation(in_word);
        toLowerCase(in_word);
        table[in_word]++;
        counter++;
    }

    std::vector<std::pair<std::string, int>> freq;

    //ADD CODE to build vector freq

    std::copy(table.begin(), table.end(), std::back_inserter(freq));
    //back_inserter calls back_inserter_itirator which calls push_back for every value in table.

    std::sort(freq.begin(), freq.end(), sortFunc);

    /* ************** Testing **************** */

    test(table, freq, name, counter);
}





/*******************************
 * 2. Test implementation      *
 * Do not modify               *
 *******************************/

void test(const std::map<std::string, int>& t, const std::vector<std::pair<std::string, int>>& v,
    const std::string& file_name, int n) {

    std::ifstream file{ "../code/out_" + file_name };

    // Test if stream is in good state
    assert(bool(file) == true);

    std::map<std::string, int> result1;
    std::string word;
    int counter{ 0 };
    int total{ 0 };

    // load expected frequency table sorted alphabetically
    while (file >> word >> counter && counter > 0) {
        result1[word] = counter;
        total += counter;
    }

    /*
    * uppgift1_kort: 69 words
    * uppgift1.txt: 1063 words
    */

    assert(total == n);  // test if total number of words is correct
    assert(t == result1);

    std::vector<std::pair<std::string, int>> result2;

    // load expected frequency table sorted by frequence
    while (file >> word >> counter) {
        result2.push_back(std::pair{ word, counter });
    }

    assert(v == result2);

    std::cout << "\nPassed all tests successfully!!\n";
}
