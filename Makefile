NAME=pipex

CC= Clang
CFLAGS = -Wall -Werror -Wextra -fsanitize=address -g3
RM= rm -rf
AR= ar rcs

FILES= pipex \
	   signal \
	   ft_split

SRC= $(addsuffix .c, $(FILES))
OBJ= $(addsuffix .o, $(FILES))

.c.o: $(SRC)
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJ)
	$(MAKE) -C Libft/
	mv Libft/libft.a .
	$(CC) $(CFLAGS) $(OBJ) libft.a -o $(NAME)

clean:
	$(RM) $(OBJ)
	$(MAKE) -C Libft/ clean
	$(RM) libft.a

fclean: clean
	$(RM) $(NAME)

re: fclean all

all: $(NAME)

bonu: all

.PHONY : all clean fclean bonus re
