#pragma once
// Include list
// ************
#include <string>
#include <cstdlib>

// Variables list
// **************
const std::string genRoot = "C:/Users/Yaojie/iCloudDrive/EduCloud/2020_F/GDW/$Dev/BloodyMelon/BloodyMelon"; // Create a copy of this project and Set to your solution path 

class mks_GE
{
	// File path generator
	// *******************
public:
	static std::string genPath(std::string filePath);
};

