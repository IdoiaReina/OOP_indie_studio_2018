##
## EPITECH PROJECT, 2017
## Makfile
## File description:
## Thomaskas06
##


SRC_DIR=../src

TEST_DIR=.

SRC=		$(SRC_DIR)/MapGenerator/MapGenerator.cpp		\
			$(TEST_DIR)/test_MapGenerator.cpp				\
			

OBJ=		$(SRC:.cpp=.o)

NAME=		tests

CFLAGS=		-Wextra -W -Wall

CXXFLAGS+=	-g

LDFLAGS=	-lcriterion -lgcov -lpthread

all:		$(NAME)
			./tests

$(NAME):	$(OBJ)
		@echo "OBJ files created"
		@$(CXX) -o $(NAME) $(OBJ) $(LDFLAGS) 
		@echo "$(NAME) compiled"
clean:
		@rm -f $(OBJ)
		@echo "OBJ files removed"

fclean:		clean
		@rm -f $(NAME)
		@echo "Binary file removed"

re:		fclean all

.PHONY:		$(NAME), clean, fclean, re
