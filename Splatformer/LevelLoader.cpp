#include "LevelLoader.h"
#include <fstream>

#include "JumpPlatform.h"

std::vector<std::string> splitBy(std::string _sentence, std::string _delim) {
	std::vector<std::string> words;

	auto start = 0U;
	auto end = _sentence.find(_delim);

	while (end != std::string::npos) {
		words.push_back(_sentence.substr(start, end - start));
		start = end + _delim.length();
		end = _sentence.find(_delim, start);
	}

	words.push_back(_sentence.substr(start, end));

	return words;
}

bool LevelLoader::LoadLevel(std::string _levelPath, std::vector<std::unique_ptr<Entity>>& _sceneEntities) {
	std::ifstream inFile;
	std::vector<std::vector<std::string>> tiles;

	inFile = std::ifstream(_levelPath);
	if (inFile.is_open()) {
		//Split up and output
		std::string line;
		while (std::getline(inFile, line)) {
			tiles.push_back(splitBy(line, ","));
		}

	} else {
		return false;
	}


	for (int y = 0; y < tiles.size(); y++) {
		for (int x = 0; x < tiles[y].size(); x++) {
			if (tiles[y][x] != "") {
				std::vector<std::string> args = splitBy(tiles[y][x], ":");
				if (args[0] == "J") {
					_sceneEntities.push_back(std::move(std::make_unique<JumpPlatform>(Vector2(x, y), std::stoi(args[1]), std::stoi(args[2]))));
				}
			} else {
				//std::cout << " ";
			}
		}
		std::cout << "\n";
	}

	return true;
}
