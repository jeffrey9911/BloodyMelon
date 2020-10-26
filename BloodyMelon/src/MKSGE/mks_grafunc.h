#pragma once
// Include list
// ************
#include <string>
#include <cstdlib>

// Variables list
// **************
const char* genRoot = ""; // Create a copy of this project and Set to your solution path 

class mks_grafunc
{
	// FILE READER WRITER
	// ******************
private:
	typedef std::string(*PathBuilder) (const std::string& filePath);
	static std::string const& getRoot();
	static PathBuilder getPathBuilder();
	static std::string getPathR_Root(const std::string& filePath);
	static std::string getPathR_Binary(const std::string& filePath);
public:
	static std::string getFilePath(const std::string& filePath);

};

