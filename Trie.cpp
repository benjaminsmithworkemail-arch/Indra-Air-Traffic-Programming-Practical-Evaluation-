#include <cstdio>
#include <cstdint>
#include <string>


#define length 26

/// @brief This turns the input char to a uint32_t where 'a' = 0
/// @param c the char value to be calculated
/// @return the uint32_t value of the input char
inline uint32_t val(char c)
{
    return uint32_t(c - 'a');
}

class Trie 
{
    public:
    uint64_t gram_1[length] = {0};
    uint64_t gram_2[length * length] = {0};
    uint64_t gram_3[length * length * length] = {0};
    uint64_t gram_4[length * length * length * length] = {0};

    /// @brief This will update the trie's 1,2,3,4 grams
    /// @param s is a string with 4 or less lowercase letters only
    /// @return this will return -1 if the buffer is too big, zero optimal buffer completed, 1 for a partial buffer completion;
    int AddWindowGrams(const std::string& s)
    {
        size_t length = s.size();
        uint32_t index = 0;
        if(length > 4)
        {
            return -1; //window was to big
        }
        //this is the best case so we want to try this first
        if(length == 4)
        {
            //find the index of the first gram
            index = val(s[0]);
            //increment the 1 gram
            gram_1[index]++;

            //find the index of the second gram
            index = 26*index + val(s[1]);
            //increment the 2 gram
            gram_2[index]++;

            //find the index of the third gram
            index = 26*index + val(s[2]);
            //increment the 3 gram
            gram_3[index]++;

            //find the index of the fourth gram
            index = 26*index + val(s[3]);
            //increment the 4 gram
            gram_4[index]++;

            return 0;
        }


        if(length >= 1)
        {
            //find the index of the first gram
            index = val(s[0]);
            //increment the 1 gram
            gram_1[index]++;
        }
        
        if(length >= 2)
        {
            //find the index of the second gram
            index = 26*index + val(s[1]);
            //increment the 2 gram
            gram_2[index]++;
        }
        
         if(length >= 3)
        {
            //find the index of the third gram
            index = 26*index + val(s[2]);
            //increment the 3 gram
            gram_3[index]++;
        }

        return 1;
    }
};

