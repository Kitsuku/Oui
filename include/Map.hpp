/* EPITECH PROJECT, 2018
** Map object
** File description:
** Map declaration
*/

#ifndef MAP_HPP_
# define MAP_HPP_

#include "objects/Positions.hpp"
#include "ACharacter.hpp"
#include "Bomb.hpp"
#include "Bonus.hpp"
#include "Wall.hpp"
#include "objects/AObject.hpp"
#include "Graphics.hpp"
#include "json.hpp"
#include <vector>
#include <memory>

class	Map
{
public:
	Map(int x, int y, const std::string &path);
	~Map() {}
	void	setSizeMap(int, int);
	void	generateCharacter(int);
	void	generateMap();
	void	loadMapFromSave(std::string);
	void	saveMap(std::string);
	std::vector<AObject *>	getAllObjects();
	std::vector<ACharacter *>	getAllCharacters();
	Positions	getMapSize();
	AObject	*getMapElem(unsigned int nb);
	ACharacter	*getCharacter(unsigned int nb);
	std::vector<Positions>	coordForUnbrWall();
	int	getNbMapElem();
	int	getNbCharacter();
	int	getNbCharacterAlive();
	void	addMapElem(std::unique_ptr<AObject> obj);
	void	addCharacter(std::unique_ptr<ACharacter> charac);
	void	play(Graphics *);
	void	playObjects();
	void	checkBreakWalls(Wall *);
	void	playWalls();
	void	playBombs();
	void	removeNbrBombCharacter(AObject *);
	void	checkDeleteObjects();
	void	checkDeleteCharac();
	void	checkDeleteCharacWithoutBombCheck();
	void	addNewElem(AObject *object);
	void	giveActionToCharac(const std::vector<irr::SEvent::SJoystickEvent> &joystickData);
	int	startPause(Graphics *, int, int, Map *);
	void	gameOverScreen(Graphics *);
	unsigned int	countCharacters();
	void	updateBombTimer(Bomb *, unsigned int);
	AObject	*updateBombPower(AObject *);
	void	setSpriteGroundAndBackGround();
	void	AddBonus(AObject *);
	std::string getBackground();
	std::string getGround();
	const std::string	&getPath() const;
	int getNbIAAlive();
	void	openFieldStartChara(Positions *);
	bool	isUnbrWall(std::vector<Positions>, Positions);
	void	saveObj(AObject *, std::string);
	void	saveBomb(AObject *, std::string);
	void	saveCharacter(ACharacter *, std::string);
	std::unique_ptr<AObject>	loadBomb(nlohmann::json);
	std::unique_ptr<AObject>	loadObj(nlohmann::json);
	std::unique_ptr<ACharacter>	loadCharacter(nlohmann::json);

protected:
	const std::string				&_path;
	std::vector<std::unique_ptr<AObject>>		_map;
	std::vector<std::unique_ptr<ACharacter>>	_characters;
	std::vector<Bonus>				_bonus;
	Positions					_mapSize;
	std::string					_ground;
	std::string					_backGround;
};

#endif /* !MAP_HPP_ */
