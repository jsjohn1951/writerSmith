/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:13:29 by wismith           #+#    #+#             */
/*   Updated: 2023/06/21 19:55:49 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef FILE_HPP
# define FILE_HPP

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

namespace wil
{
	class file
	{
		private :
			std::string					fileName;
			std::vector<std::string>	buffer;

		public :
										file (const std::string &name);
										~file ();

			void						read ();
			void						write ();
			void						printBuf ();
			std::vector<std::string>	&rtnBuffer ();
	};
}

#endif
