/*
** EPITECH PROJECT, 2018
** Indie studio
** File description:
** Exception functions
*/

#include "MyException.hpp"

MyException::MyException(const std::string &msg): _msg(msg)
{
}

const char	*MyException::what() const noexcept
{
	return _msg.c_str();
}