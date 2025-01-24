CC := cc
# CFLAGS := -Wall -Werror -Wextra
# CFLAGS := -fsanitize=address

LIBFT_DIR := ../../libft
LIBFT := $(LIBFT_DIR)/libft.a

# SRCS
SRCDIR := ./
SRCS += $(SRCDIR)/main.c

# ADD GNL
GNL_DIL := ../../gnl
SRCS += $(GNL_DIL)/get_next_line.c
SRCS += $(GNL_DIL)/get_next_line_utils.c

# ADD MLX
MLXS_DIR := ../../srcs/mlx
SRCS += $(MLXS_DIR)/key_hooks.c
SRCS += $(MLXS_DIR)/close_window.c
SRCS += $(MLXS_DIR)/put_pixel.c
SRCS += $(MLXS_DIR)/set_event.c

# ADD INIT
INITS_DIR := ../../srcs/init
SRCS += $(INITS_DIR)/init_params.c
SRCS += $(INITS_DIR)/init_data.c
SRCS += $(INITS_DIR)/init_player.c

UPDATES_DIR := ../../srcs/update
SRCS += $(UPDATES_DIR)/update_player.c

# ADD MATH
MATHS_DIL := ../../srcs/math
SRCS += $(MATHS_DIL)/convert_angle.c
SRCS += $(MATHS_DIL)/raycast.c

# OBJS
OBJDIR := objs
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%$(SUFFIX).o)

# complie option
INCDIR := ../../includes
INCLUDES := -I$(INCDIR) -I$(LIBFT_DIR)

# Minilibx
MINILIBX_DIR := ../../minilibx-linux
MINILIBX := $(MINILIBX_DIR)/libmlx_Linux.a

# project name
PJT := cub3D

# SUFFIX oveview
SUFFIXES := _both _ryomori _yyamasak

# debug condition
ifdef BOTH_DEBUG
	DEFINES := -D RYOMORI_DEBUG -D YYAMASAK_DEBUG
	SUFFIX := $(word 1, $(SUFFIXES))
else ifdef RYOMORI_DEBUG
	DEFINES := -D RYOMORI_DEBUG
	SUFFIX := $(word 2, $(SUFFIXES))
else ifdef YYAMASAK_DEBUG
	DEFINES := -D YYAMASAK_DEBUG
	SUFFIX := $(word 3, $(SUFFIXES))
else
	DEFINES :=
	SUFFIX :=
endif

# output name
NAME = $(PJT)$(SUFFIX)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MINILIBX)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LIBFT) $(MINILIBX) -lXext -lX11 -lm

ryomori:
	make RYOMORI_DEBUG=1

yyamasak:
	make YYAMASAK_DEBUG=1

both:
	make BOTH_DEBUG=1

$(LIBFT):
	make -C $(LIBFT_DIR) all

$(MINILIBX):
	make -sC $(MINILIBX_DIR)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJDIR)/%$(SUFFIX).o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDES) $(DEFINES) -o $@ -c $<

clean:
	make -C $(LIBFT_DIR) clean
	rm -rf $(OBJDIR)
	make -C $(MINILIBX_DIR) clean

fclean: clean
	rm -f $(PJT)
	rm -f $(foreach SUFFIX,$(SUFFIXES),$(PJT)$(SUFFIX))
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all ryomori yyamasak both clean fclean re
