# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/14 20:52:25 by wismith           #+#    #+#              #
#    Updated: 2023/06/22 14:25:51 by wismith          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = writerSmith

CPPFLAGS = -Wall -Werror -Wextra -g3
#-pedantic

CXX = c++

SRCS = main \
	modesTermios \
	editor \
	file

OBJDIR = objects

OBJ = $(addprefix $(OBJDIR)/, $(addsuffix .o, $(SRCS)))

$(OBJDIR)/%.o : srcs/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CPPFLAGS) -c $< -o $@

all : $(NAME)

$(NAME) : $(OBJ)
	$(CXX) $(CPPFLAGS) $(OBJ) -o $(NAME)

clean :
	rm -rf $(OBJDIR)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re