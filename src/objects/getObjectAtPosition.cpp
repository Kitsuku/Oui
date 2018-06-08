/*
** EPITECH PROJECT, 2018
** getObjectAtPosition.cpp
** File description:
** function that return the index of object at position from a vector
*/

#include <iostream>
#include "AObject.hpp"

int	getObjectAtPosition(float posX, float posY,
			std::vector<AObject *> objects)
{
	int		final_index = -1;
	int		count_index = 0;
	Positions	actual_object_pos;

	for (auto it = objects.begin(); it != objects.end(); it++) {
		actual_object_pos = (*it)->getPos();
		if (actual_object_pos.x == posX &&
		actual_object_pos.y == posY) {
			final_index = count_index;
		}
		count_index += 1;
	}
	return final_index;
}
