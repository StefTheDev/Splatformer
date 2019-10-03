#include "LevelLoader.h"
#include <fstream>

#include "Platform.h"
#include "JumpPlatform.h"
#include "TimePlatform.h"
#include "RespawnPlatform.h"
#include "Coin.h"
#include "Ball.h"

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

TileInfo collateTiles(int _x, int _y, std::vector<std::vector<std::string>>& _tiles) {
	int width = 1, height = 1;
	std::string origVal = _tiles[_y][_x];
	std::vector<std::string> args = splitBy(_tiles[_y][_x], ":");
	_tiles[_y][_x] = "SKIP";

	int lOffset = 1;
	while ((_x - lOffset) > 0 && origVal == _tiles[_y][_x - lOffset]) {
		width++;
		_tiles[_y][_x - lOffset] = "SKIP";
		lOffset++;
	}
	lOffset--;

	int rOffset = 1;
	while ((_x + rOffset) < _tiles[_y].size() && origVal == _tiles[_y][_x + rOffset]) {
		width++;
		_tiles[_y][_x + rOffset] = "SKIP";
		rOffset++;
	}
	rOffset--;

	int uOffset = 1;
	while ((_y - uOffset) > 0) {
		bool foundSomething = false;
		for (int i = (_x - lOffset); i < (_x + rOffset); i++) {
			if (origVal == _tiles[_y - uOffset][i]) {
				_tiles[_y - uOffset][i] = "SKIP";
				foundSomething = true;
			}
		}
		if (foundSomething) {
			height++;
			uOffset++;
		} else {
			break;
		}
	}
	uOffset--;

	int dOffset = 1;
	while ((_y + dOffset) < _tiles.size()) {
		bool foundSomething = false;
		for (int i = (_x - lOffset); i < (_x + rOffset + 1); i++) {
			if (origVal == _tiles[_y + dOffset][i]) {
				_tiles[_y + dOffset][i] = "SKIP";
				foundSomething = true;
			}
		}
		if (foundSomething) {
			height++;
			dOffset++;
		} else {
			break;
		}
	}
	dOffset--;

	float xOffset = ((float)rOffset - (float)lOffset) / 2.0f;
	float yOffset = ((float)uOffset - (float)dOffset) / 2.0f;

	TileInfo retInfo;
	retInfo.dimensions = Vector2(width, height);
	retInfo.position = Vector2((float)_x + xOffset, (float)_y + yOffset);

	return retInfo;
}

bool LevelLoader::LoadLevel(std::string _levelPath, std::vector<std::unique_ptr<Entity>>& _sceneEntities, std::vector<RespawnPlatform*>& _sceneRespawns) {
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
				if (args[0] == "SKIP") {
					//Just don't do anything
					continue;
				}else if (args[0] == "P") {
					_sceneEntities.push_back(std::move(std::make_unique<Platform>(collateTiles(x, y, tiles))));
				}else if (args[0] == "J") {
					_sceneEntities.push_back(std::move(std::make_unique<JumpPlatform>(collateTiles(x, y, tiles), std::stoi(args[1]), std::stoi(args[2]))));
				} else if (args[0] == "T") {
					_sceneEntities.push_back(std::move(std::make_unique<TimePlatform>(collateTiles(x, y, tiles), std::stof(args[1]), std::stof(args[2]))));
				}else if (args[0] == "C") {
					_sceneEntities.push_back(std::move(std::make_unique<Coin>(Vector2(x, y))));
				}else if (args[0] == "B") {
					_sceneEntities.push_back(std::move(std::make_unique<Ball>(Vector2(x, y))));
				}else if (args[0] == "R") {
					_sceneEntities.push_back(std::move(std::make_unique<RespawnPlatform>(collateTiles(x, y, tiles), std::stoi(args[1]))));
					_sceneRespawns.push_back(static_cast<RespawnPlatform*>(_sceneEntities.back().get()));
				}
			}
		}
	}

	return true;
}
