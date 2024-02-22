SRC =  main.c map_operations.c loop.c key_press.c raycasting.c sprites.c map_zones.c helpers.c \
		draw_line.c mini_map.c hud.c enemy.c map_operations_helpers.c parse_map_elements.c parse_infos.c\
		raycasting_utils.c shoot_rays.c draw_ceiling_floor.c linked_list.c sprites_utils.c \
		sprites_utils2.c music.c read_map.c enemy_helper.c

SRC_DIR = src/
OBJ_DIR = obj/

OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))


NAME = cub3D
CFLAGS= -O3 -Ofast -flto   -Wall -Wextra -Werror

ifeq ($(shell uname), Linux)
	MLX_FLAGS = -lm MLX/Linux_MLX.a -Iinclude -ldl -lglfw
else ifeq ($(shell uname), Darwin)
	BREW_PREFIX = $(shell brew --prefix)
	MLX_FLAGS = -lm MLX/MacOS_MLX.a -Iinclude -lglfw -L"$(BREW_PREFIX)/lib/"
endif

INCLUDE = -I libft -I includes

RED = \033[1;31m
GREEN = \033[1;32m
BLUE = \033[1;34m
YELLOW = \033[1;33m
BLINK = \033[5m
RESET = \033[0m
all : $(NAME)

$(NAME) : ascci_art $(OBJ)
	@make -C libft > /dev/null
	@$(CC) $(OBJ) $(CFLAGS) $(MLX_FLAGS) $(INCLUDE) libft/libft.a -o $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c includes/cub3d.h
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@


clean:
	@make -C libft clean > /dev/null
	@rm -rf $(OBJ_DIR)

fclean:
	@make -C libft fclean > /dev/null
	@rm -rf $(OBJ_DIR) $(NAME)

re: fclean all

ascci_art:
	@clear
	@printf "$(GREEN)                                                                                               \n\
                                      bbbbbbbb                                           dddddddd \n\
        CCCCCCCCCCCCC                 b::::::b             333333333333333               d::::::d \n\
     CCC::::::::::::C                 b::::::b            3:::::::::::::::33             d::::::d \n\
   CC:::::::::::::::C                 b::::::b            3::::::33333::::::3            d::::::d \n\
  C:::::CCCCCCCC::::C                  b:::::b            3333333     3:::::3            d:::::d  \n\
 C:::::C       CCCCCCuuuuuu    uuuuuu  b:::::bbbbbbbbb                3:::::3    ddddddddd:::::d  \n\
C:::::C              u::::u    u::::u  b::::::::::::::bb              3:::::3  dd::::::::::::::d  \n\
C:::::C              u::::u    u::::u  b::::::::::::::::b     33333333:::::3  d::::::::::::::::d  \n\
C:::::C              u::::u    u::::u  b:::::bbbbb:::::::b    3:::::::::::3  d:::::::ddddd:::::d  \n\
C:::::C              u::::u    u::::u  b:::::b    b::::::b    33333333:::::3 d::::::d    d:::::d  \n\
C:::::C              u::::u    u::::u  b:::::b     b:::::b            3:::::3d:::::d     d:::::d  \n\
C:::::C              u::::u    u::::u  b:::::b     b:::::b            3:::::3d:::::d     d:::::d  \n\
 C:::::C       CCCCCCu:::::uuuu:::::u  b:::::b     b:::::b            3:::::3d:::::d     d:::::d  \n\
  C:::::CCCCCCCC::::Cu:::::::::::::::uub:::::bbbbbb::::::b3333333     3:::::3d::::::ddddd::::::dd \n\
   CC:::::::::::::::C u:::::::::::::::ub::::::::::::::::b 3::::::33333::::::3 d:::::::::::::::::d \n\
     CCC::::::::::::C  uu::::::::uu:::ub:::::::::::::::b  3:::::::::::::::33   d:::::::::ddd::::d \n\
        CCCCCCCCCCCCC    uuuuuuuu  uuuubbbbbbbbbbbbbbbb    333333333333333      ddddddddd   ddddd \n\
                                                                                                  \n\
                                                                          $(RED)by: abouabra && ykhayri \n\
                                                                                                  \n$(RESET)"

.PHONY: all clean fclean re bonus