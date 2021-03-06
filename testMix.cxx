#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

void testMix()
{
    // in your case you'll have a file
  std::ifstream ifile("base_list-A4-unrestricted.csv");
  //std::stringstream ifile("User1, 21, 70\nUser2, 25,68"); 

    std::string line; // we read the full line here
    while (std::getline(ifile, line)) // read the current line
    {
      
      std::istringstream iss(line); // construct a string stream from line

        // read the tokens from current line separated by comma
        std::vector<std::string> tokens; // here we store the tokens
        std::string token; // current toxken
        while (std::getline(iss, token, ','))
        {
            tokens.push_back(token); // add the token to the vector
        }

        // map the tokens into our variables
        std::string name = tokens[0];
        int latDeg = std::stoi(tokens[1]);
        double latMin = std::stoi(tokens[2]);
	std::string latCar = tokens[3];
	int longDeg = std::stoi(tokens[4]);
        double longMin = std::stoi(tokens[5]);
	std::string longCar = tokens[6];
	//double alt = std::stoi(tokens[7]); // will crash, as altitude isn't filled for all fields
	std::string primaryOperator = tokens[8];
	//int yearEst = std::stoi(tokens[9]);
	std::string facType = tokens[10];
	std::string seasonality = tokens[11];
	std::string currentStatus = tokens[12];
	
        std::cout << " " << std::endl;
        std::cout << "\t Name: " << name << std::endl;
        std::cout << "\t Lat (deg): " << latDeg << std::endl;
        std::cout << "\t Lat (mins): " << latMin << std::endl;
	std::cout << "\t Lat cardinality: " << latCar << std::endl;
	std::cout << "\t Long (deg): " << longDeg << std::endl;
	std::cout << "\t Long (mins): " << longMin << std::endl;
	std::cout << "\t Long cardinality: " << longCar << std::endl;
	//std::cout << "\t Altitude: " << alt << std::endl;
	std::cout << "\t Primary operator: " << primaryOperator << std::endl;
	//std::cout << "\t Year established: " << yearEst << std::endl;
	std::cout << "\t Facility type: " << facType << std::endl;
	std::cout << "\t Seasonality: " << seasonality << std::endl;
	std::cout << "\t Current status: " << currentStatus << std::endl;
	
    }

    
    

    return;
}
