#pragma once

#include <string>
#include <fstream>

namespace core {

	std::string read_file(const char * file_path)
	{
		FILE *file = fopen(file_path, "rt");
		fseek(file, 0, SEEK_END);
		unsigned long leght = ftell(file);

		char *data = new char[leght + 1];
		memset(data, 0, leght + 1);

		fseek(file, 0, SEEK_SET);
		fread(data, 1, leght, file);
		fclose(file);

		std::string result(data);
		delete[] data;

		return result;
	}

}