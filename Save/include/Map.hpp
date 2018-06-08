//
// EPITECH PROJECT, 2018
// Map object
// File description:
// 
//

#ifndef MAP_HPP_
# define MAP_HPP_

#include "objects/positions.hpp"
#include "ACharacter.hpp"
#include "AObject.hpp"
#include <vector>
#include <memory>

class	Map
{
public:
	Map(int x, int y) { _mapSize.x = x; _mapSize.y = y; }
	~Map() {}
	void	generateMap() {}
	void	loadMapFromSave(std::string);
	void	saveMap();
	Positions	getMapSize() { return _mapSize; }
	AObject	*getMapElem(unsigned int nb) {
		if (nb < _map.size())
			return _map.at(nb).get();
		return nullptr;
	}
	ACharacter	*getCharacter(unsigned int nb) {
		if (nb < _characters.size())
			return _characters.at(nb).get();
		return nullptr;
	}
	int	getNbMapElem() { return _map.size(); }
	int	getNbCharacter() { return _characters.size(); }
	void	addMapElem(std::unique_ptr<AObject> obj) { _map.push_back(std::move(obj)); }
	void	addCharacter(std::unique_ptr<ACharacter> charac) { _characters.push_back(std::move(charac)); }
protected:
	std::vector<std::unique_ptr<AObject>>	_map;
	std::vector<std::unique_ptr<ACharacter>>	_characters;	
	Positions				_mapSize;	
};

#endif /* !MAP_HPP_ */
