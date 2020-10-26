// Include list
// ************
#include "mks_grafunc.h"
#include <string>
#include <cstdlib>

// CPP File Reader
// ***************
typedef std::string(*PathBuilder) (const std::string& filePath);
std::string mks_grafunc::getFilePath(const std::string& filePath)
{
	static std::string(*pathBuilder) (std::string const&) = getPathBuilder();
	return (*pathBuilder)(filePath);
}

std::string const& mks_grafunc::getRoot()
{
	static char const* envRoot = getenv("LOGL_ROOT_PATH");
	static char const* genedRoot = (envRoot != nullptr ? envRoot : genRoot);
	static std::string root = (genedRoot != nullptr ? genedRoot : "");
	return root;
}

PathBuilder mks_grafunc::getPathBuilder()
{
	if (getRoot() != "") {
		return &mks_grafunc::getPathR_Root;
	}
	else {
		return &mks_grafunc::getPathR_Binary;
	}
}

std::string mks_grafunc::getPathR_Root(const std::string& filePath)
{
	return getRoot() + std::string("/") + filePath;
}

std::string mks_grafunc::getPathR_Binary(const std::string& filePath)
{
	return "../../../" + filePath;
}
