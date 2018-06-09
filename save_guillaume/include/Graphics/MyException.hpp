/*
** EPITECH PROJECT, 2018
** Indie studio
** File description:
** Exception function
*/

#ifndef MYEXCEPTION_HPP_
	#define MYEXCEPTION_HPP_
	#include <exception>
	#include <string>

	class MyException: public std::exception
	{
	public:
		MyException(const std::string &msg);
		const char		*what() const noexcept override;
	private:
		const std::string	_msg;
	};

#endif /* !MYEXCEPTION_HPP_ */
