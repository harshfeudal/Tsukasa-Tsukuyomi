#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

class Dotenv {
public:
	Dotenv(const std::string& filename)
	{
		std::ifstream file(filename);
		if (!file.is_open()) {
			std::cerr << "Failed to open file: " << filename << std::endl;
			return;
		}

		std::string line;
		while (std::getline(file, line)) {
			if (line.empty() || line[0] == '#')
				continue;

			size_t pos = line.find('=');
			if (pos == std::string::npos)
				continue;

			std::string key = line.substr(0, pos);
			std::string value = line.substr(pos + 1);

			if (!value.empty() && value[0] == '"' && value[value.size() - 1] == '"')
			{
				value = value.substr(1, value.size() - 2);
			}
			m_data[key] = value;
		}
	}

	std::string get(const std::string& key) const
	{
		auto it = m_data.find(key);
		if (it != m_data.end()) {
			return it->second;
		}
		return "";
	}

private:
	std::unordered_map<std::string, std::string> m_data;
};
