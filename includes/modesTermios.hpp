/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modesTermios.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 16:22:21 by wismith           #+#    #+#             */
/*   Updated: 2023/06/19 17:11:52 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef MODESTERMIOS_HPP
# define MODESTERMIOS_HPP

#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <poll.h>

namespace wil
{
	class	modesTermios
	{
		private :
			struct termios	setting;
		
		public :
			modesTermios ();
			~modesTermios ();
			
			void	enableRaw();
			void	disableRaw();
	};
}

#endif
