/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 20:57:12 by wismith           #+#    #+#             */
/*   Updated: 2023/06/22 14:35:17 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.hpp"
#include "../includes/file.hpp"

int	main(int argc, char **argv)
{
	std::cout << "\033[2J" << std::endl;
	if (argc >= 2)
	{
		wil::file	file(argv[1]);
		file.read();

		{
			wil::editor	editor(file.rtnBuffer());
			editor.run();
		}
		
		file.write();
		std::cout << "\033[2J \033[H" << std::endl;
	}
	else
	{
		std::cout << KRED;
		std::cerr << "writerSmith : Err ❌ : No file specified!\n" << std::endl;
		std::cout << KNRM;
		std::cout << "Should be: \t./writerSmith <";
		std::cout << KGRN;
		std::cout << "FILE";
		std::cout << KNRM;
		std::cout << ">" << std::endl;
		return (1);
	}
	return (0);
}
