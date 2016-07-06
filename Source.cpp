#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <string>
#include <iomanip>
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define PATHSIZE 1001		// number of characters for path plus \0
#define FILENAME "script"	// script file name
#define VERSION "v0.1 - 21.06.2016."

bool str_compare(const std::string a, const std::string b) {
	return strcmp(a.c_str(), b.c_str()) < 0 ? true : false;
}

int main(int argc, char* argv[]) {

	char path[PATHSIZE];
	std::string command;

	if(argc > 1)
		command = argv[1];
	else
		command = "MACRO";

	if (!strcmp(command.c_str(), "ver")) {
		std::cout << VERSION << std::endl;
		return 0;
	}
	
	auto status = GetCurrentDirectoryA(PATHSIZE - 1, path);

	if (status == 0) {
		std::cout << "Reading of current folder failed!\nPress key to exit..." << std::endl;
		getchar();
		return -1;
	}

	if (status >= PATHSIZE) {
		std::cout << "Path too long!\nMaximum " << PATHSIZE - 1 << " characters allowed.\nPress key to exit..." << std::endl;
		getchar();
		return -1;
	}

	char* temp_path = (char*)malloc(sizeof(path) + 7);

	if (temp_path == NULL) {
		std::cout << "Memory allocation failed!\nPress key to exit..." << std::endl;
		getchar();
		return -2;
	}

	strcpy(temp_path, path);
	strcat(temp_path, "\\*.dwg");

	std::list<std::string> dwg_list;
	WIN32_FIND_DATAA FindFileData;
	HANDLE hFind = FindFirstFileA(temp_path, &FindFileData);

	if (hFind != INVALID_HANDLE_VALUE) do {
		dwg_list.push_back(FindFileData.cFileName);
	} while (FindNextFileA(hFind, &FindFileData) != 0);

	FindClose(hFind);
	free(temp_path);

	std::ifstream ifs;
	std::ofstream ofs;
	std::string filename;

	for (int i = 1; i < 1000; ++i) {
		std::stringstream ss;
		ss << path << "\\" << FILENAME << std::setw(3) << std::setfill('0') << i << ".scr";
		filename = ss.str();
		ifs.open(filename.c_str());
		if (ifs.fail())
			break;
		ifs.close();
	}

	ofs.open(filename);
	if (ofs.fail()) {
		std::cout << "Script file creation error!\nPress key to exit..." << std::endl;
		getchar();
		return -1;
	}
	
	dwg_list.sort(str_compare);

	while (!dwg_list.empty()) {
		ofs << "_.open \"" << path << "\\" << dwg_list.front() << "\" " << command << " _.qsave _.close" << std::endl;
		dwg_list.pop_front();
	}

	ofs.close();

	std::cout << "Script created!\nPress key to exit..." << std::endl;

	getchar();
	return 0;
}

