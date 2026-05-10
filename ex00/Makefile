CC = c++

FLAGS = -Wall -Werror -Wextra -std=c++98

NAME = btc

SRC = main.cpp BitcoinExchange.cpp

OBJ = $(SRC:.cpp=.o)

all: $(NAME)

%.o: %.cpp BitcoinExchange.hpp
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclaen all