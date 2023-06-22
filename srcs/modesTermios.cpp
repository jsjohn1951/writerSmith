/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modesTermios.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 16:25:34 by wismith           #+#    #+#             */
/*   Updated: 2023/06/19 17:59:22 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/modesTermios.hpp"

using namespace wil;

modesTermios::modesTermios () : setting() {}

modesTermios::~modesTermios ()
{ this->disableRaw(); }

void	modesTermios::enableRaw ()
{
	struct termios	raw;

	tcgetattr(STDIN_FILENO, &this->setting);
	raw = this->setting;
	raw.c_lflag	&= ~( ECHO | ICANON );
	raw.c_oflag &= ~( OPOST );
	raw.c_cc[VMIN] = 0;
	raw.c_cc[VTIME] = 1;
	tcsetattr( STDIN_FILENO, TCSAFLUSH, &raw );
}

void	modesTermios::disableRaw ()
{ tcsetattr( STDIN_FILENO, TCSAFLUSH, &this->setting ); }
