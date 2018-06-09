/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** abstract class character
*/

#include <vector>
#include <memory>
#include "Action.hpp"
#include "AObject.hpp"
#include "Graphics.hpp"

#ifndef ACHARACTER_HPP_
# define ACHARACTER_HPP_

class	ACharacter
{
public:
	/* Constructor */
	ACharacter(int, Positions,
		std::vector<std::string>, std::string, std::string);
	/* Destructor */
	~ACharacter();
	/* Methods */
	virtual void		defineAction(const
		irr::SEvent::SJoystickEvent &, std::vector<AObject *>) = 0;
	std::unique_ptr<AObject>	doAction(std::vector<AObject *>);
	Positions			getPos();
	std::vector<std::string>	getSprites();
	Action				getAction();
	int				getNbrPlayer();
	bool				getIsDead();
	void				moveLeft(std::vector<AObject *>);
	void				moveRight(std::vector<AObject *>);
	void				moveUp(std::vector<AObject *>);
	void				moveDown(std::vector<AObject *>);
	std::unique_ptr<AObject>	putBomb(std::vector<AObject *>);
	void				checkDeath(std::vector<AObject *>);
	void				checkBonus(std::vector<AObject *>);
	void				removePutBomb();

protected:
	int				_nbrPlayer;
	int				_nbrMaxBomb;
	int				_nbrPutBomb;
	int				_fireRange;
	float				_speed;
	bool				_wallPass;
	Action				_action;
	Positions			_position;
	bool				_isDead;
	std::vector<std::string>	_sprites;
	std::string			_bombLiveSprites;
	std::string			_bombDeathSprites;
};

#endif
