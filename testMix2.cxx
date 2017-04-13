#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

void basesCampsRootifier()
{

  TFile f("tree1.root","recreate");
  TTree t1("t1","a simple Tree with simple variables");

  // BASE LIST VARS:
  std::string name;
  
  int latDeg;
  double latMin;
  std::string latCar;
  double fullLat;
  
  int longDeg;
  double longMin;
  std::string longCar;
  double fullLong;
  
  double alt; // will crash, as altitude isn't filled for all fields
  std::string primaryOperator;
  int yearEst;
  std::string facType;
  std::string seasonality;
  std::string currentStatus;

  t1.Branch("name",&name);
  
  t1.Branch("latDeg",&latDeg,"latDeg/I");
  t1.Branch("latMin",&latMin,"latMin/D");
  t1.Branch("latCar",&latCar);
  t1.Branch("fullLat",&fullLat);
  
  t1.Branch("longDeg",&longDeg,"longDeg/I");
  t1.Branch("longMin",&longMin,"longMin/D");
  t1.Branch("longCar",&longCar);
  t1.Branch("fullLong",&fullLong);

  t1.Branch("alt",&alt);
  t1.Branch("primaryOperator",&primaryOperator);
  t1.Branch("yearEst",&yearEst,"yearEst/I");
  t1.Branch("facType",&facType);
  t1.Branch("seasonality",&seasonality);
  t1.Branch("currentStatus",&currentStatus);

  // CUSTOM VARS (calculated from the base list)
  
  // Load base list
  std::ifstream ifile("base_list-A4-unrestricted.csv");

  std::string line; 
  while (std::getline(ifile, line))
    {
      
      std::istringstream iss(line); // construct a string stream from line

      // read the tokens from current line separated by comma
      std::vector<std::string> tokens; // here we store the tokens
      std::string token; // current token
      while (std::getline(iss, token, ','))
        {
	  tokens.push_back(token); // add the token to the vector
        }

      // map the tokens into our variables
      name = tokens[0];
      latDeg = std::stoi(tokens[1]);
      latMin = std::stof(tokens[2]);
      latCar = tokens[3];
      longDeg = std::stoi(tokens[4]);
      longMin = std::stof(tokens[5]);
      longCar = tokens[6];
      alt = std::stof(tokens[7]); // will crash, as altitude isn't filled for all fields
      primaryOperator = tokens[8];
      yearEst = std::stoi(tokens[9]);
      facType = tokens[10];
      seasonality = tokens[11];
      currentStatus = tokens[12];

      fullLat = -latDeg - latMin/60;
      
      if(longCar == "E")
	{
	  fullLong = longDeg + (longMin)/60;
	}

      else if(longCar == "W")
	{
	  fullLong = -(longDeg + (longMin)/60);
	}

      t1.Fill();

      /*
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
*/
      
    }

  t1.Write();
  std::cout << "Tree written" << std::endl;
    

  return;
}
