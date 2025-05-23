#include <iostream>
#include <fstream>
#include <string>

const std::string errorOpenFile = "Error opening file: ";
const std::string errorInputFormat = "Usage: comparefiles.exe <file1> <file2>/n";
const std::string diffrentResult = "Files are different. Line number is ";
const std::string equalResult = "Files are equal/n";

bool IsCorrectOpenFile(std::ifstream& file, const std::string& fileName) 
{
    file.open(fileName);
    if (!file.is_open()) 
    {
        std::cout << errorOpenFile << fileName << "/n";
        return false;
    }
    return true;
}

bool CheckRemainingLines(std::ifstream& file, int lineNumber) 
{
    std::string line;
    if (std::getline(file, line)) 
    {
        std::cout << diffrentResult << lineNumber << "/n";
        return true;
    }
    return false;
}

int CompareFiles(const std::string& file1, const std::string& file2) 
{
    std::ifstream firstFile, secondFile;
    if (!IsCorrectOpenFile(firstFile, file1) || !IsCorrectOpenFile(secondFile, file2))
    {
        return 1;
    }

    std::string firstFileLine, secondFileLine;
    int lineNumber = 1;
    while (std::getline(firstFile, firstFileLine) && std::getline(secondFile, secondFileLine)) 
    {
        if (firstFileLine != secondFileLine) 
        {
            std::cout << diffrentResult << lineNumber << "/n";
            return 1;
        }
        lineNumber++;
    }

    if (CheckRemainingLines(firstFile, lineNumber) || CheckRemainingLines(secondFile, lineNumber)) 
    {
        return 1;
    }

    std::cout << equalResult;
    return 0;
}

int main(int argc, char* argv[]) 
{
    if (argc != 3) 
    {
        std::cerr << errorInputFormat;
        return 1;
    }

    return CompareFiles(argv[1], argv[2]);
}