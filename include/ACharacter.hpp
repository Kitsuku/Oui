/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** abstract class character
*/

#ifndef ACHARACTER_HPP_
# define ACHARACTER_HPP_

#include <vector>
#include <memory>
#include <irrlicht.h>
#include "Action.hpp"
#include "AObject.hpp"

class	ACharacter
{
public:
	/* Constructors */
	ACharacter(int, Positions,
		std::vector<std::string>, std::string, std::string);
	ACharacter();
	/* Destructor */
	~ACharacter();
	/* Methods */
	virtual AObject	*defineAction(const
		irr::SEvent::SJoystickEvent &, std::vector<AObject *>) = 0;
	AObject				*doAction(std::vector<AObject *>);
	void				setNbrPlayer(int);
	void				setPos(Positions);
	void				setSprites(std::vector<std::string>);
	void				setAction(Action);
	void				setNbrMaxBomb(int);
	void				setNbrPutBomb(int);
	void				setSpeed(float);
	void				setWallPass(bool);
	void				setIsDead(bool);
	void				setFireRange(int);
	int				getNbrPlayer();
	Positions			getPos();
	std::vector<std::string>	getSprites();
	Action				getAction();
	int				getNbrMaxBomb();
	int				getNbrPutBomb();
	float				getSpeed();
	bool				getWallPass();
	bool				getIsDead();
	int				getFireRange();
	unsigned int			getDelayDead();
	void				addDelayDead();
	void				moveLeft(std::vector<AObject *>);
	void				moveRight(std::vector<AObject *>);
	void				moveUp(std::vector<AObject *>);
	void				moveDown(std::vector<AObject *>);
	AObject				*putBomb(std::vector<AObject *>);
	void				checkPlayerDeath(
						std::vector<AObject *>);
	void				checkBonus(std::vector<AObject *>);
	void				removePutBomb();
	Action				getOldDir();
	Action				getOldAction();
	std::string			getBombLiveSprite();
	std::string			getBombDeathSprite();
	void				setOldDir(Action);
	void				setOldAction(Action);
	void				setBombLiveSprite(std::string);
	void				setBombDeathSprite(std::string);
	void				setDelayDead(unsigned int);

protected:
	Action				_oldDir;
	Action				_oldAction;
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
	unsigned int			_delayDead;
};

#endif
