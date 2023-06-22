/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 17:33:31 by wismith           #+#    #+#             */
/*   Updated: 2023/06/22 15:38:07 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.hpp"

using namespace wil;

bool runtime = true;

editor::editor ( std::vector<std::string> &File ) :
	modes(), buffer(), buf(), termRow(0), termCol(0), cx(0), cy(0), file(File)
{
	catchSignal();
	this->pfd.fd = STDIN_FILENO;
	this->pfd.events = POLLIN | POLLOUT;
	this->pfd.revents = 0;
	this->buf[0] = '\0';
	modes.enableRaw();
	fcntl ( STDIN_FILENO, F_SETFL, O_NONBLOCK );
	this->getWindowSize(&this->termRow, &this->termCol);
}

editor::~editor ()
{
	std::cout << "\x1b[2J\r\n \x1b[?25h\r\n";
}

void	editor::run ()
{
	this->clear (' ');
	while ( runtime )
	{
		poll(&this->pfd, 1, -1);

		if (this->pfd.revents & POLLIN)
		{
			std::cout << "\033[2J" << std::endl;
			this->keyProcess();
		}

		if (this->pfd.revents & POLLOUT && this->buffer.size())
			std::cout << this->buffer;

		this->buffer.clear();
	}
}

void	editor::keyProcess()
{
	ssize_t	bytes = 0;
	char	c;

	bytes = read(STDIN_FILENO, &c, 1);
	if (bytes > 0)
	{
		if (c == '\x1b')
			this->cursor();
		else
			this->editFile(c);

		snprintf( this->buf,
				sizeof( this->buf ),
				"\x1b[%d;%dH",
				this->cy + 1,
				this->cx + 1 );

		this->clear(c);
	}
}

void	editor::clear(char c)
{

	this->buffer += "\x1b[?25l";
	this->buffer += "\x1b[H";

	this->getWindowSize(&this->termRow, &this->termCol);
	this->drawRows();

	if (c != '\x1b')
	{
		char	str[2] = { c, '\0' };
		this->buffer += "value of c: "
			+ std::string( str );
	}
	this->buffer += std::string(this->buf);

	this->buffer += "\x1b[?25h";
	this->buffer += KGRN;
	this->buffer += std::string( "ↆ" );
	this->buffer += std::string("\r\n");
	this->buffer += KNRM;
}

void	editor::drawRows()
{
	std::string	padding;
	std::string welcome;
	std::vector<std::string>::iterator	it;

	it = this->file.begin();
	welcome = "Welcome To Writer Smith Text Editor!";
	padding.assign((this->termCol - welcome.size()) / 2, ' ');
	for (int i = 0; i < this->termRow - 1; i++)
	{
		if (i && it != this->file.end())
		{
			this->buffer += *it;
			it++;
			if (it == this->file.end())
				this->buffer += "\n\r";
		}
		else
			this->buffer += "~\x1b[K\r\n";
		if (!this->file.size() && i == this->termRow / 3)
		{
			this->buffer += padding + welcome + "\r\n";
			this->buffer += padding + "version 1.0";
		}
	}
}

int		editor::getWindowSize(int *rows, int *cols)
{
	struct winsize ws;

	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0)
		return (-1);
	*cols = ws.ws_col;
	*rows = ws.ws_row;
	return (0);
}

void	editor::mvCursor(char key)
{
	switch (key)
	{
		case 'a':
			if (this->cx)
				this->cx--;
			break ;
		case 'd':
			if (this->cx < this->termCol - 1
				&& (size_t) this->cy < this->file.size()
				&& (size_t) this->cx < this->file[this->cy].size() - 2)
				this->cx++;
			break ;
		case 'w':
			if (this->cy)
			{
				this->cy--;
				if ((size_t) this->cx >= this->file[this->cy].size() - 2)
					this->cx = this->file[this->cy].size() - 2;
			}
			break ;
		case 's':
			if (this->cy < this->termRow - 2
				&& (size_t) this->cy < this->file.size() )
			{
				this->cy++;
				if ( (size_t) this->cy != this->file.size() &&
					(size_t) this->cx >= this->file[this->cy].size() - 2)
					this->cx = this->file[this->cy].size() - 2;
				else if ( (size_t) this->cy == this->file.size())
					this->cx = 0;
			}
			break;
	}
}

void	editor::cursor()
{
	char	seq[3];
	ssize_t	bytes = 0;

	poll(&this->pfd, 1, -1);

	if (this->pfd.revents & POLLIN)
		bytes = read(STDIN_FILENO, seq, 2);
	if (bytes >= 2 && seq[0] == '[')
	{
		if (seq[2] == '~' && isdigit(seq[1]))
			;
		else 
			this->mvCursor(
				(seq[1] == 'A' ? 'w' :
				seq[1] == 'B' ? 's' :
				seq[1] == 'C' ? 'd' :
				seq[1] == 'D' ? 'a' :
				'x')
		);
	}
}

void	editor::editFile(char c)
{
	if (c == 10)
	{
		if (!this->file.size())
				this->file.push_back("\r\n");
		if ((size_t)this->cy < this->file.size())
		{
			this->file.insert( this->file.begin() + (this->cy + 1), 
				this->file[this->cy].substr(this->cx, (this->file[this->cy].size() - this->cx)));
			this->file[this->cy].erase( this->file[this->cy].begin()
							+ this->cx,
							this->file[this->cy].begin() 
							+ this->file[this->cy].size()
							- 2 );
		}
		else
			this->file.push_back("");
		this->cy++;
		this->cx = 0;
	}
	else if (c != 127)
	{
		if (!this->file.size() || (size_t) this->cy == this->file.size() )
				this->file.push_back("\r\n");
		if ((size_t) this->cx <= this->file[this->cy].size() - 2)
			this->file[this->cy].insert((this->file[this->cy].begin() + this->cx), c);
		this->cx++;
	}
	else if (this->cx > 0)
	{
		if ((size_t) this->cx < this->file[this->cy].size() - 2)
			this->file[this->cy].erase(this->file[this->cy].begin()
										+ this->cx - 1);
		this->cx--;
	}
}

//? signal handlers
void	wil::handlr(int sig)
{
	(void) sig;
	runtime = false;
}

void	wil::catchSignal()
{
	signal(SIGINT, wil::handlr);
	signal(SIGQUIT, wil::handlr);
}
