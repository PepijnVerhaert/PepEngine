#include "PepEnginePCH.h"
#include "BinaryReader.h"

using namespace pep;

bool pep::BinaryToChar(const std::string& file, std::vector<char>& dest)
{
	std::ifstream input(file.c_str(), std::ios::out | std::ios::binary);
	if (!input.is_open())
	{
		std::cout << "Failed to open binary file\n";
		return false;
	}

	while (!input.eof())
	{
		char c{};
		input.read(&c, sizeof(char));
		dest.emplace_back(c);
	}
	dest.erase(--dest.cend());

	input.close();
	if (!input.good())
	{
		std::cout << "Failed to close binary file\n";
		return true;
	}
	return true;
}
