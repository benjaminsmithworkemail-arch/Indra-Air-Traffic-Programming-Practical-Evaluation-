#include <cstdio>
#include "Trie.cpp"

int main()
{
    printf("hello world");

    //this is the sliding window
    std::string window;
    window.reserve(4);
}

/// @brief This updates the window for the trie
/// @param s the address of the string bufffer
/// @param nextLeter the letter to be added
void updateWindow(std::string& s, char nextLeter)
{
    s[0] = s[1];
    s[1] = s[2];
    s[2] = s[3];
    s[3] = nextLeter;
}
