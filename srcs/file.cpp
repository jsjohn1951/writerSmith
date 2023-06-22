/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:22:02 by wismith           #+#    #+#             */
/*   Updated: 2023/06/22 14:38:21 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/file.hpp"

using namespace wil;

file::file(const std::string &name) : fileName(name), buffer() {}

file::~file() {}

void	file::read()
{
	std::ifstream	infile(this->fileName.c_str());

	if (infile.good())
	{
		for (std::string line; getline(infile, line); )
		{
			line += "\r\n";
			buffer.insert(buffer.end(), line);
		}
		infile.close();
	}
}

void	file::write()
{
	std::ofstream	outfile(this->fileName.c_str());
	std::vector<std::string>::iterator it;
	std::string	sav;
	std::string line;

	for (it = this->buffer.begin(); it != buffer.end(); it++)
	{
		line = *it;
		size_t	pos = line.npos;

		while ((pos = line.find('\r', pos + 1)) != line.npos)
			line.erase(pos, 1);
		sav += line;
	}
	if (outfile.good())
	{
		outfile << sav;
		outfile.close();
	}
}

void	file::printBuf ()
{
	std::vector<std::string>::iterator it;

	for (it = this->buffer.begin(); it != buffer.end(); it++)
		std::cout << *it;
}

std::vector<std::string>	&file::rtnBuffer ()
{
	return (this->buffer);
}
