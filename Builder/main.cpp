// Nasty script to generate a single header 

#include <Windows.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

// Workaround: Force check for compilation errors
#define _GUICOMPONNENTS_HANDLELIBANDHEADERS
	#include "../GUIComponents/GUIComponents.h"
#undef _GUICOMPONNENTS_HANDLELIBANDHEADERS

int main()
{
	auto Pause = []() {
#ifdef _DEBUG
		std::cout << "Press any key to exit the application" << std::endl;
		std::getchar();
#endif
	};

	auto StringContains = [](std::string x, std::string y) {
		return x.find(y) != std::string::npos;
	};

	auto StringTrimLeft = [](std::string x, const char character = ' ') {
		return x.erase(0, x.find_first_not_of(character));
	};

	auto StringTrimRight = [](std::string x, const char character = ' ') {
		return x.erase(x.find_last_not_of(character) + 1);
	};

	auto StringTrim = [StringTrimRight, StringTrimLeft](std::string x, const char character = ' ') {
		return StringTrimLeft(StringTrimRight(x, character), character);
	};

	auto RemoveComment = [](std::string x) {
		size_t lastOf = x.find_last_of(std::string("//"));
		if (lastOf != std::string::npos && lastOf > 0)
			return x.erase(lastOf - 1);
		else
			return x;
	};

	auto ParseInclude = [StringContains](std::string file) {
		std::vector<std::string> result;
		std::ifstream includeStream(std::string("../GUIComponents/" + file));
		if (!includeStream.is_open())
		{
			std::cout << "Failed to open " << file << std::endl;
			return std::make_pair(false, result);
		}

		std::string input;
		while (std::getline(includeStream, input))
		{
			if(!StringContains(input, "#pragma once"))
				result.push_back(input);
		}

		includeStream.close();

		return std::make_pair(true, result);
	};

	if (DeleteFileW(L"../output/GUIComponents.h"))
		std::cout << "Removed 'GUIComponents.h' from directory 'output'" << std::endl;

	if (RemoveDirectoryW(L"../Output"))
		std::cout << "Removed directory 'output'" << std::endl;

	if (CreateDirectoryW(L"../Output", NULL) == FALSE)
	{
		std::cout << "Failed to create directory 'output'" << std::endl;
		Pause();
		return EXIT_FAILURE;
	}

	auto guiComponentsParseResult = ParseInclude("GUIComponents.h");
	if (!guiComponentsParseResult.first)
	{
		Pause();
		return EXIT_FAILURE;
	}

	std::vector<std::string> guiComponentHeader;
	guiComponentHeader.push_back("// Header generated on " __TIME__ " " __DATE__ "\n");

	const std::string newLine = "\n";
	bool insideNamespace = false;
	for (std::string line : guiComponentsParseResult.second)
	{
		if (StringContains(line, "namespace GUIComponents {"))
		{
			insideNamespace = true;
			guiComponentHeader.push_back(line + newLine);
		}
		else if (insideNamespace && StringContains(line, "}"))
		{
			insideNamespace = false;
			guiComponentHeader.push_back(line + newLine);
		}
		else if (insideNamespace && StringContains(line, "{"))
		{
			std::cout << "Unexpected token '{' inside namespace" << std::endl;
			Pause();

			return EXIT_FAILURE;
		}
		else if (insideNamespace && StringContains(line, "#include"))
		{
			std::string filename = StringTrim(StringTrim(RemoveComment(line).substr(9)), '"');
			guiComponentHeader.push_back(std::string("// ") + filename + newLine);
			
			auto includedFile = ParseInclude(std::string("../GUIComponents/") + filename);
			if (!includedFile.first)
			{
				Pause();
				return EXIT_FAILURE;
			}

			for (std::string includeLine : includedFile.second)
			{
				guiComponentHeader.push_back(includeLine + newLine);
			}
			
			guiComponentHeader.push_back(std::string("// eof ") + filename + newLine + newLine);
		}
		else
		{
			if(!insideNamespace || line.length() > 0)
				guiComponentHeader.push_back(line + newLine);
		}
	}

	std::ofstream guiComponentsParsedStream("../output/GUIComponents.h");
	if (!guiComponentsParsedStream.is_open())
	{
		std::cout << "Failed to create output file" << std::endl;
		return EXIT_FAILURE;
	}

	for (std::string line : guiComponentHeader)
	{
		guiComponentsParsedStream << line;
	}

	guiComponentsParsedStream.close();

	std::cout << "Parsed succesfully!" << std::endl;

	Pause();
	return EXIT_SUCCESS;
}