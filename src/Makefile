CC = cc

CFLAGS = -Wall -Wextra -Werror -g

MLX_PATH = ../minilibx-linux
MLX_LINK = -L$(MLX_PATH) -lmlx -lXext -lX11 -lm


SRC = 	main.c parsing/helpers.c parsing/ft_split.c parsing/helpers2.c \
		parsing/parse.c parsing/camera.c parsing/light.c parsing/scene_elements.c\
		parsing/garbage_collector.c render/vec_math.c render/put_camera.c render/raytracer.c \
		render/render.c parsing/helpers3.c

OBJ = $(SRC:.c=.o)

RM = rm -f

NAME = miniRT

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(MLX_LINK) -o $(NAME)

clean:
	$(RM) $(OBJ)  

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
