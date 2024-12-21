CC := cc
CFLAGS := -Wall -Werror -Wextra
CFLAGS :=

LIBFT_DIR := libft
LIBFT := $(LIBFT_DIR)/libft.a

# SRCS
SRCDIR := srcs
SRCS += $(SRCDIR)/main.c

# OBJS
OBJDIR := objs
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%$(SUFFIX).o)

# コンパイルオプション
INCDIR := includes
INCLUDES := -I$(INCDIR) -I$(LIBFT_DIR)

# Minilibx
MINILIBX_DIR := ./minilibx-linux
MINILIBX := $(MINILIBX_DIR)/libmlx_Linux.a

# プロジェクト名
PJT := cub3D

# SUFFIX一覧
SUFFIXES := _both _ryomori _yyamasak

# デバッグの場合分け
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

# 出力名
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
