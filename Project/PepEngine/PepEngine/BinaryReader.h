#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <cassert>

namespace pep
{
	bool BinaryToChar(const std::string& file, std::vector<char>& dest);
}