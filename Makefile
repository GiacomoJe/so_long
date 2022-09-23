UNAME = $(shell uname)
NAME =  libmlx_$(UNAME).a
SRC_GNL = ./includes/gnl/
NAME_GNL = get_next_line.a
CC = cc
VALGRIND = g++ -g
FLAGS = -ldl -Iminilibx -Lminilibx -lminilibx -lm -lbsd -lXext -lX11 
FILES = 
OBJ_DIR = minilibx/

FILES_GNL = get_next_line.c get_next_line_utils.c
OBJ_GNL  = $(FILES_GNL:%.c=%.o)
OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

all: $(NAME) $(SRC_GNL)$(NAME_GNL)
	$(CC) -I /usr/X11/include -g -L /usr/X11/lib -l mlx -framework OpenGL -framework AppKit main.c map.c $(SRC_GNL)get_next_line.a $(NAME)

$(NAME): $(OBJ)
	ar -rc $(NAME) $(OBJ)

$(SRC_GNL)$(NAME_GNL): $(SRC_GNL)$(OBJ_GNL) ./includes/gnl/get_next_line.h
	ar -rc -l $(SRC_GNL)$(NAME_GNL) $(SRC_GNL)$(OBJ_GNL)

$(SRC_GNL)/%.o: $(SRC_GNL)$(FILES_GNL)
	$(CC) -Wall -Wextra -Werror -c $< -o $@

%.o: %.c
	$(CC) -Wall -Wextra -Werror -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean:
	rm -rf $(OBJ) $(NAME)

re: fclean	all

.PHONY: all clean fclean re
