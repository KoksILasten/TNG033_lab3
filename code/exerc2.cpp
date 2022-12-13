/*****************************************
 * Lab 3: exercise 2                      *
 * Anagrams table                         *
 ******************************************/

 //#include <iostream>

 //int main() {
 //
 //    // ADD CODE
 //}
#include <iostream>
#include <algorithm>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <set>

using table_entry = std::pair < std::string, std::set<std::string>>;

int main() {
    // Create a map to store the subjects of words and their corresponding anagrams
    std::map<std::string, std::set<std::string>> subjects;

    // Open the input file
    std::ifstream input("../code/uppgift2.txt");

    if (!input) {
        std::cout << "Could not open input file!!\n";
        return 0;
    }

    // Read words from the input file and add them to the map
    //std::string word;
    std::vector<std::string> words;
    //std::istream_iterator<string>(input)
    std::copy(std::istream_iterator<std::string>(input), std::istream_iterator<std::string>(), std::back_inserter(words)); 
    // std::copy takes an input iterator and an output iterator and copies the values from the input iterator to the output iterator.
    //while (input >> word) {
        // Sort the characters of the word alphabetically
    //std::sort(words.begin(), words.end()); //not really needed

    // Add the word to the list of anagrams for its subject'

    std::for_each(words.begin(), words.end(), [&subjects](std::string aWord) {

        //subjects[a].push_back(a); //does not exist
        //std::string copyWord{ aWord }; //
        std::string temp = aWord;
        	
        std::sort(aWord.begin(), aWord.end());
	    subjects[aWord].insert(temp);
		});


// Create an output file stream
    std::ofstream output("../code/output.txt");

    // Write the number of words read from the input file
    output << "Total number of words: " << words.size() << std::endl;

    // Iterate over the map and write the anagrams for each subject
    //for (const auto& [subject, anagrams] : subjects) {

    output << std::endl << "-- ANAGRAMS --" << std::endl;
    std::for_each(subjects.begin(), subjects.end(), [&output](table_entry p) {
        // Write the anagrams only if there are two or more
        if (p.second.size() >= 2) {

            // Use the std::for_each algorithm to write the anagrams to the output stream
            std::copy(p.second.begin(), p.second.end(), std::ostream_iterator<std::string>(output, " "));

            output << " --> " << p.second.size() << " words." << std::endl;
        }
        });

    return 0;
}