CC := cc
# CFLAGS := -Wall -Werror -Wextra
# CFLAGS := -fsanitize=address

LIBFT_DIR := ./libft
LIBFT := $(LIBFT_DIR)/libft.a

# SRCS
SRCDIR := ./srcs
SRCS += $(SRCDIR)/main.c
SRCS += $(SRCDIR)/error.c

# ADD GNL
GNL_DIR := ${SRCDIR}/gnl
SRCS += $(GNL_DIR)/get_next_line.c
SRCS += $(GNL_DIR)/get_next_line_utils.c

# ADD MLX
MLXS_DIR := ${SRCDIR}/mlx
SRCS += $(MLXS_DIR)/key_hooks.c
SRCS += $(MLXS_DIR)/close_window.c
SRCS += $(MLXS_DIR)/put_pixel.c
SRCS += $(MLXS_DIR)/set_event.c
SRCS += $(MLXS_DIR)/draw_vertical.c

# ADD INIT
INITS_DIR := ${SRCDIR}/init
SRCS += $(INITS_DIR)/init_params.c
SRCS += $(INITS_DIR)/init_data.c
SRCS += $(INITS_DIR)/init_player.c

# ADD UPDATES
UPDATES_DIR := ${SRCDIR}/update
SRCS += $(UPDATES_DIR)/update_player.c
SRCS += $(UPDATES_DIR)/update_vector.c
SRCS += $(UPDATES_DIR)/update_ivec.c
SRCS += $(UPDATES_DIR)/update_ray.c
SRCS += $(UPDATES_DIR)/update_wall.c

# ADD MATH
MATHS_DIR := ${SRCDIR}/math
SRCS += $(MATHS_DIR)/convert_angle.c
SRCS += $(MATHS_DIR)/raycast.c

# ADD PARSER
PARSERS_DIR := ${SRCDIR}/parser
SRCS += $(PARSERS_DIR)/parse_map_settings.c
SRCS += $(PARSERS_DIR)/parse_color.c
SRCS += $(PARSERS_DIR)/parse_map_data.c
SRCS += $(PARSERS_DIR)/parse_map_interface.c
SRCS += $(PARSERS_DIR)/parse.c
SRCS += $(PARSERS_DIR)/check_valid_map.c
SRCS += $(PARSERS_DIR)/fill_space.c

# OBJS
OBJDIR := objs
OBJS := $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# complie option
INCDIR := ./includes
INCLUDES := -I$(INCDIR) -I$(LIBFT_DIR)

# Minilibx
MINILIBX_DIR := ./minilibx-linux
MINILIBX := $(MINILIBX_DIR)/libmlx_Linux.a

PJT := Cub3D
NAME = $(PJT)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MINILIBX)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LIBFT) $(MINILIBX) -lXext -lX11 -lm

$(LIBFT):
	make -C $(LIBFT_DIR) all

$(MINILIBX):
	make -sC $(MINILIBX_DIR)

# OBJDIR 作成 (サブディレクトリ含む)
$(OBJDIR):
	@mkdir -p $(OBJDIR)
	@mkdir -p $(OBJDIR)/mlx
	@mkdir -p $(OBJDIR)/init
	@mkdir -p $(OBJDIR)/update
	@mkdir -p $(OBJDIR)/math
	@mkdir -p $(OBJDIR)/gnl
	@mkdir -p $(OBJDIR)/parser

# ソースファイルをオブジェクトファイルに変換
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

# クリーン
clean:
	make -C $(LIBFT_DIR) clean
	rm -rf $(OBJDIR)
	make -C $(MINILIBX_DIR) clean

fclean: clean
	rm -f $(PJT)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
