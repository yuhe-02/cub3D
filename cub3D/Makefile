CC := cc
CFLAGS := -Wall -Werror -Wextra
# CFLAGS := -fsanitize=address

LIBFT_DIR := ./libft
LIBFT := $(LIBFT_DIR)/libft.a

FTPRINTF_DIR := ./ft_printf
FTPRINTF := $(FTPRINTF_DIR)/libftprintf.a

# SRCS
SRCDIR := ./srcs
SRCS := $(wildcard $(SRCDIR)/*.c)

# ADD GNL
GNL_DIR := $(SRCDIR)/gnl
SRCS += $(wildcard $(GNL_DIR)/*.c)

# ADD MLX
MLXS_DIR := $(SRCDIR)/mlx
SRCS += $(wildcard $(MLXS_DIR)/*.c)

# ADD INIT
INITS_DIR := $(SRCDIR)/init
SRCS += $(wildcard $(INITS_DIR)/*.c)

# ADD UPDATES
UPDATES_DIR := $(SRCDIR)/update
SRCS += $(wildcard $(UPDATES_DIR)/*.c)

# ADD MATH
MATHS_DIR := $(SRCDIR)/math
SRCS += $(wildcard $(MATHS_DIR)/*.c)

# ADD PARSER
PARSERS_DIR := $(SRCDIR)/parser
SRCS += $(wildcard $(PARSERS_DIR)/*.c)

# OBJS
OBJDIR := objs
OBJS := $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# complie option
INCDIR := ./includes
INCLUDES := -I$(INCDIR) -I$(LIBFT_DIR) -I$(FTPRINTF_DIR)

# Minilibx
MINILIBX_DIR := ./minilibx-linux
MINILIBX := $(MINILIBX_DIR)/libmlx_Linux.a

PJT := cub3D
NAME = $(PJT)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(FTPRINTF) $(MINILIBX)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LIBFT) $(FTPRINTF) $(MINILIBX) -lXext -lX11 -lm

$(LIBFT):
	make -C $(LIBFT_DIR) all

$(FTPRINTF):
	make -C $(FTPRINTF_DIR) all

$(MINILIBX):
	make -sC $(MINILIBX_DIR)

# OBJDIR (including sub directory)
$(OBJDIR):
	@mkdir -p $(OBJDIR)
	@mkdir -p $(OBJDIR)/mlx
	@mkdir -p $(OBJDIR)/init
	@mkdir -p $(OBJDIR)/update
	@mkdir -p $(OBJDIR)/math
	@mkdir -p $(OBJDIR)/gnl
	@mkdir -p $(OBJDIR)/parser

# convert source file into object file
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

# クリーン
clean:
	make -C $(LIBFT_DIR) clean
	make -C $(FTPRINTF_DIR) clean
	rm -rf $(OBJDIR)
	make -C $(MINILIBX_DIR) clean

fclean: clean
	rm -f $(PJT)
	make -C $(LIBFT_DIR) fclean
	make -C $(FTPRINTF_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
