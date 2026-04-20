NAME = cub

CC = cc
CFLAGS = -g -Wall -Wextra
RM = rm -rf

OBJ_DIR = objects
INCLUDES_DIR = includes

SRCS = \
	srcs/main.c \
	srcs/parsing/parsing.c \
	srcs/parsing/get_file.c \
	srcs/parsing/free_def.c \
	srcs/parsing/print_defs.c \
	srcs/parsing/utils.c \
	srcs/parsing/check_section.c \
	srcs/parsing/check_id.c \
	srcs/parsing/get_tex.c \
	srcs/parsing/validate_map.c \
	srcs/parsing/init_mlx.c \
	srcs/parsing/print_tex_lib.c \
	srcs/system/utils.c	\
	srcs/blob/build_blob.c \
	srcs/blob/build_hdr.c	

OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

MLX_DIR = mlx
MLX = $(MLX_DIR)/libmlx.a

INCLUDES = -I$(INCLUDES_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz

all: $(MLX) $(LIBFT_LIB) $(NAME)

$(NAME): $(OBJS) $(LIBFT_LIB) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_LIB) $(MLX_FLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	printf "INC=/usr/include\n" > $(MLX_DIR)/Makefile.gen
	grep -v '%%%%' $(MLX_DIR)/Makefile.mk >> $(MLX_DIR)/Makefile.gen
	$(MAKE) -C $(MLX_DIR) -f Makefile.gen CC=gcc CFLAGS="-O3 -std=gnu17 -I/usr/include"

clean:
	$(RM) $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(MLX_DIR) -f Makefile.gen clean || true

re: fclean all

debug: $(NAME)
	gdb -x debug.gdb ./$(NAME)

norminette:
	norminette $(INCLUDES_DIR) srcs

.PHONY: all clean fclean re debug norminette