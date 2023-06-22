/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 17:31:02 by wismith           #+#    #+#             */
/*   Updated: 2023/06/22 12:27:52 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef EDITOR_HPP
# define EDITOR_HPP

#include "modesTermios.hpp"

#include <ctype.h>
#include <signal.h>
#include <fcntl.h>
#include <poll.h>
#include <iostream>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string>
#include <cstdio>
#include <vector>

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

namespace wil
{
	class editor
	{
		private :
			struct pollfd				pfd;
			wil::modesTermios			modes;
			std::string					buffer;
			char						buf[32];

			int							termRow, termCol;
			int							cx, cy;

			std::vector<std::string>	&file;

		public :
										editor ( std::vector<std::string> &File );
										~editor ();
			
			void						run();
			void						keyProcess();
			void						clear( char c );

			void						drawRows();
			int							getWindowSize( int *rows, int *cols );
			void						mvCursor( char key );
			void						cursor();
			void						editFile(char c);
	};

	void								catchSignal();
	void								handlr( int sig );
}

#endif
