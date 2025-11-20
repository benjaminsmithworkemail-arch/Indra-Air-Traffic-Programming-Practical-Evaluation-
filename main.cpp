#include <cstdio>
#include <string>
#include <cstring>
#include <fstream>
#include <vector>
#include <cstddef>
#include "Trie.hpp"

/// @brief This updates the window for the trie
/// @param s the address of the string bufffer
/// @param nextLetter the letter to be added
void updateWindow(std::string& s, char nextLetter)
{
    s[0] = s[1];
    s[1] = s[2];
    s[2] = s[3];
    s[3] = nextLetter;
}

int main()
{
    printf("Started:\n");
    
    //file name (this is for local testing purposes)
    const char* filename = "C:\\Users\\Ben Smith\\OneDrive\\Desktop\\School documents\\OutsideWork\\Indra-Air-Traffic-Programming-Practical-Evaluation\\Test_File.txt";

    //open the file
    std::ifstream file(filename, std::ios::binary);
    if (!file)
    {
        printf("Could not open file: %s\n", filename);
        return 1;
    }
    else
    {
        printf("File: %s open\n", filename);
    }
    
    //create the trie that holds all findings
    Trie trie;
    
    const size_t bufferSize = 1024 * 1024; // 1MB buffer used to reduce file read calls
    std::vector<char> buffer(bufferSize);

    std::string window;

    char c;
    // Fill the window with first 4 lowercase letters
    while (window.size() < 4 && file.get(c))
    {
        window.push_back(c);
    }   
    trie.AddWindowGrams(window);
    
    //read 1MB chunks
    while (file)
    {
        file.read(buffer.data(), buffer.size());
        std::streamsize bytesRead = file.gcount();
        for (std::streamsize i = 0; i < bytesRead; i++)
        {            
            updateWindow(window, buffer[i]);       // slide the window
            trie.AddWindowGrams(window);           // update grams           
        }
        
    }
    file.close(); 

    // Count the last 3-gram (chars 1,2,3,4 excluding first char)
    std::string last3 = window.substr(1, 3);
    trie.AddWindowGrams(last3);

    // Count the last 2-gram (chars 2,3,4 excluding first 2)
    std::string last2 = window.substr(2, 2);
    trie.AddWindowGrams(last2);

    // Count the last 1-gram (last character only)
    std::string last1 = window.substr(3, 1);
    trie.AddWindowGrams(last1);

    trie.PrintLargestGramFrequencies();
}

 
