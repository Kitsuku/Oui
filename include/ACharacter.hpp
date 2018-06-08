/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** abstract class character
*/

#include <vector>
#include "action.hpp"
<<<<<<< HEAD
#include "AObject.hpp"
=======
#include "objects/AObject.hpp"
>>>>>>> origin/Paul/generation_map

#ifndef ACHARACTER_HPP_
# define ACHARACTER_HPP_

class	ACharacter
{
public:
	/* Constructor */
	ACharacter(int, Positions);
<<<<<<< HEAD
	/* Destructor */
	~ACharacter();
=======
	ACharacter() {}
	/* Destructor */
	~ACharacter() {}
>>>>>>> origin/Paul/generation_map
	/* Methods */
	virtual void		defineAction(int touche,
		std::vector<AObject *> objects) const { objects = objects; touche = touche;}; // = 0 normalement
	void			doAction(Action, std::vector<AObject *>);
	//checkDie ???
	Positions		getPos();
	std::vector<int>	getSprites(std::string);
<<<<<<< HEAD
=======
	int			getPlayerNbr() { return _nbrPlayer; }
	int			getBombNbr() { return _nbrBomb; }
	int			getFireRange() { return _fireRange; }
	float			getSpeed() { return _speed; }
	bool			getWallPass() { return _wallPass; }
	bool			getIsDead() { return _isDead; }
	void			setPos(Positions pos) { _position = pos; }
>>>>>>> origin/Paul/generation_map
	void			moveLeft(std::vector<AObject *>);
	void			moveUp(std::vector<AObject *>);
	void			moveRight(std::vector<AObject *>);
	void			moveDown(std::vector<AObject *>);
	void			putBomb(std::vector<AObject *>);
	void			checkDeath();
<<<<<<< HEAD
=======
	void			setNbrPlayer(int nbrPlayer) { _nbrPlayer = nbrPlayer; }
	void			setNbrBomb(int nbrBomb) { _nbrBomb = nbrBomb; }
	void			setFireRange(int fireRange) { _fireRange = fireRange; }
	void			setSpeed(float speed) { _speed = speed; }
	void			setWallPass(bool wallPass) { _wallPass = wallPass; }
	void			setIsDead(bool isDead) { _isDead = isDead; }
	void			setLeftSprites(std::vector<int> sprites) { _leftSprites = sprites; }
	void			setRightSprites(std::vector<int> sprites) { _rightSprites = sprites; }
	void			setUpSprites(std::vector<int> sprites) { _upSprites = sprites; }
	void			setDownSprites(std::vector<int> sprites) { _downSprites = sprites; }
>>>>>>> origin/Paul/generation_map

protected:
	int			_nbrPlayer;
	int			_nbrBomb;
	int			_fireRange;
	float			_speed;
	bool			_wallPass;
	Positions		_position;
	bool			_isDead;
	std::vector<int>	_leftSprites;
	std::vector<int>	_rightSprites;
	std::vector<int>	_upSprites;
	std::vector<int>	_downSprites;
};

#endif
