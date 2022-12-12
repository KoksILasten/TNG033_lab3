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

int main() {
    // Create a map to store the subjects of words and their corresponding anagrams
    std::map<std::string, std::vector<std::string>> subjects;

    // Open the input file
    std::ifstream input("../uppgift2.txt");

    if (!input) {
        std::cout << "Could not open input file!!\n";
        return 0;
    }

    // Read words from the input file and add them to the map
    //std::string word;
    std::vector<std::string> words;
    //std::istream_iterator<string>(input)
    std::copy(std::istream_iterator<std::string>(input), std::istream_iterator<std::string>(), std::back_inserter(words)); // //std::copy takes an input iterator and an output iterator and copies the values from the input iterator to the output iterator.
    //while (input >> word) {
        // Sort the characters of the word alphabetically
    std::sort(words.begin(), words.end());

    // Add the word to the list of anagrams for its subject
    std::for_each(words.begin(), words.end(), [subjects](std::string aWord) {
        //subjects[a].push_back(a); 
        std::string copyWord{ aWord };
    std::sort(aWord.begin(), aWord.end());

    auto found = std::find(subjects[copyWord].first(), subjects[copyWord].end(), aWord)

        });
    //subjects[words].push_back(words);
//}

// Create an output file stream
    std::ofstream output("output.txt");

    // Write the number of words read from the input file
    output << "Total number of words: " << subjects.size() << std::endl;

    // Iterate over the map and write the anagrams for each subject
    for (const auto& [subject, anagrams] : subjects) {
        // Write the anagrams only if there are two or more
        if (anagrams.size() >= 2) {
            output << "Subject: " << subject << std::endl;
            output << "Anagrams: ";

            // Use the std::for_each algorithm to write the anagrams to the output stream
            std::for_each(anagrams.begin(), anagrams.end(), [&output](const std::string& word) {
                output << word << " ";
                });

            // Write the number of anagrams for this subject
            output << "(" << anagrams.size() << " words)" << std::endl;
        }
    }

    return 0;
}