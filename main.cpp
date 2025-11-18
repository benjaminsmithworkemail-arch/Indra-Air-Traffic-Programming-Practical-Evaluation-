#include <cstdio>
#include <string>
#include <fstream>
#include <vector>
#include <cstddef>
#include "Trie.cpp"

int main()
{
    //file name
    const char* filename = "Indra_Data_Set_Large_File.txt";

    //open the file
    std::ifstream file(filename, std::ios::binary);
    if (!file)
    {
        printf("Could not open file %s", filename);
        return 1;
    }

    //create the trie that holds all findings
    Trie trie;

    const size_t bufferSize = 1024 * 1024; // 1MB buffer
    std::vector<char> buffer(bufferSize);

    std::string window(4, 0); // initialize with 4 placeholder characters

    //get the first 4 chars and prep them in window
    for (int i = 0; i < 4; i++)
    {
        char c;
        if (!file.get(c))
        {
            printf("could not grab first 4 chars");
            return 1;
        }
        window[i] = c;
    }    
    
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
   
}

/// @brief This updates the window for the trie
/// @param s the address of the string bufffer
/// @param nextLeter the letter to be added
void updateWindow(std::string& s, char nextLetter)
{
    s[0] = s[1];
    s[1] = s[2];
    s[2] = s[3];
    s[3] = nextLetter;
}
