#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

int testMix()
{
    // in your case you'll have a file
    // std::ifstream ifile("input.txt");
    std::stringstream ifile("User1, 21, 70\nUser2, 25,68"); 

    std::string line; // we read the full line here
    while (std::getline(ifile, line)) // read the current line
    {
      std::istringstream iss(line); // construct a string stream from line

        // read the tokens from current line separated by comma
        std::vector<std::string> tokens; // here we store the tokens
        std::string token; // current token
        while (std::getline(iss, token, ','))
        {
            tokens.push_back(token); // add the token to the vector
        }

        // we can now process the tokens
        // first display them
        std::cout << "Tokenized line: ";
        for (const auto& elem : tokens)
            std::cout << "[" << elem << "]";
        std::cout << std::endl;

        // map the tokens into our variables, this applies to your scenario
        std::string name = tokens[0]; // first is a string, no need for further processing
        int age = std::stoi(tokens[1]); // second is an int, convert it
        int height = std::stoi(tokens[2]); // same for third
        std::cout << "Processed tokens: " << std::endl;
        std::cout << "\t Name: " << name << std::endl;
        std::cout << "\t Age: " << age << std::endl;
        std::cout << "\t Height: " << height << std::endl;
    }
}
