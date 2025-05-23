// 4.3
#include <iostream>
#include <set>
#include <sstream>

int main() {
    std::set<std::string> forbiddenWords;
    std::string line, word;

    std::getline(std::cin, line);
    std::istringstream forbiddenStream(line);
    while (forbiddenStream >> word) 
    {
        forbiddenWords.insert(word);
    }

    while (std::getline(std::cin, line)) 
    {
        std::istringstream textStream(line);
        bool firstWord = true;

        while (textStream >> word) 
        {
            if (forbiddenWords.find(word) == forbiddenWords.end()) 
            {
                if (!firstWord)
                {
                    std::cout << " ";
                }
                std::cout << word;
                firstWord = false;
            }
        }
        std::cout << "\n";
    }
    return 0;
}
