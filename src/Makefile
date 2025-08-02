CC = cc

CFLAGS = -Wall -Wextra -Werror -g

# MLX_LINK =  -L/usr/include/minilibx-linux -lmlx -lXext -lX11 -lm

# -------------------------------- iammar -------------------------------- #

SRC = 	main.c parsing/helpers.c parsing/ft_split.c parsing/helpers2.c parsing/parse.c parsing/camera.c


# -------------------------------------------------------------------------- #

OBJ = ${SRC:%.c=%.o}

EXEC_OBJ = ${EXEC_SRC:%.c=%.o}

RM = rm -f

NAME = minirt

all: ${NAME}

%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@ 

${NAME}: ${OBJ}
	${CC} ${CFLAGS} ${OBJ} -o $@

clean:
	${RM} ${OBJ}  

fclean: clean
	${RM} ${NAME}

re: fclean all

bonus: all

.PHONY: all clean fclean re

.SECONDARY: ${OBJ} 