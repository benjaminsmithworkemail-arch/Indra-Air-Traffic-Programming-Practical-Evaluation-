#include <cstdio>
#include <cstdint>
#include <string>


#define ALPHABET_SIZE  26

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

    uint64_t* gram_1;
    uint64_t* gram_2;
    uint64_t* gram_3;
    uint64_t* gram_4;

    Trie() 
    {
        gram_1 = new uint64_t[ALPHABET_SIZE]();
        gram_2 = new uint64_t[ALPHABET_SIZE * ALPHABET_SIZE]();
        gram_3 = new uint64_t[ALPHABET_SIZE * ALPHABET_SIZE * ALPHABET_SIZE]();
        gram_4 = new uint64_t[ALPHABET_SIZE * ALPHABET_SIZE * ALPHABET_SIZE * ALPHABET_SIZE]();
    }

    ~Trie() 
    {
        delete[] gram_1;
        delete[] gram_2;
        delete[] gram_3;
        delete[] gram_4;
    }
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

    void PrintLargestGramFrequencies()
{
    // --- 1-gram ---
    uint64_t max1 = 0;
    size_t idx1 = 0;
    for (size_t i = 0; i < ALPHABET_SIZE; ++i)
        if (gram_1[i] > max1) { max1 = gram_1[i]; idx1 = i; }

    char gram1[2] = { char('a' + idx1), 0 };
    printf("Largest 1-gram: %s, count: %llu\n", gram1, max1);

    // --- 2-gram ---
    uint64_t max2 = 0;
    size_t idx2 = 0;
    for (size_t i = 0; i < ALPHABET_SIZE * ALPHABET_SIZE; ++i)
        if (gram_2[i] > max2) { max2 = gram_2[i]; idx2 = i; }

    char gram2[3];
    gram2[0] = char('a' + idx2 / ALPHABET_SIZE);
    gram2[1] = char('a' + idx2 % ALPHABET_SIZE);
    gram2[2] = 0;
    printf("Largest 2-gram: %s, count: %llu\n", gram2, max2);

    // --- 3-gram ---
    uint64_t max3 = 0;
    size_t idx3 = 0;
    for (size_t i = 0; i < ALPHABET_SIZE * ALPHABET_SIZE * ALPHABET_SIZE; ++i)
        if (gram_3[i] > max3) { max3 = gram_3[i]; idx3 = i; }

    char gram3[4];
    gram3[0] = char('a' + idx3 / (ALPHABET_SIZE * ALPHABET_SIZE));
    gram3[1] = char('a' + (idx3 / ALPHABET_SIZE) % ALPHABET_SIZE);
    gram3[2] = char('a' + idx3 % ALPHABET_SIZE);
    gram3[3] = 0;
    printf("Largest 3-gram: %s, count: %llu\n", gram3, max3);

    // --- 4-gram ---
    uint64_t max4 = 0;
    size_t idx4 = 0;
    for (size_t i = 0; i < ALPHABET_SIZE * ALPHABET_SIZE * ALPHABET_SIZE * ALPHABET_SIZE; ++i)
        if (gram_4[i] > max4) { max4 = gram_4[i]; idx4 = i; }

    char gram4[5];
    gram4[0] = char('a' + idx4 / (ALPHABET_SIZE * ALPHABET_SIZE * ALPHABET_SIZE));
    gram4[1] = char('a' + (idx4 / (ALPHABET_SIZE * ALPHABET_SIZE)) % ALPHABET_SIZE);
    gram4[2] = char('a' + (idx4 / ALPHABET_SIZE) % ALPHABET_SIZE);
    gram4[3] = char('a' + idx4 % ALPHABET_SIZE);
    gram4[4] = 0;
    printf("Largest 4-gram: %s, count: %llu\n", gram4, max4);
}
};

