CC = cc
AR = ar rc
CFLAGS = -Wall -Wextra -Werror

SRCDIR = .

SRCS = $(SRCDIR)/ft_printf.c \
	$(SRCDIR)/ft_convert_cs.c \
	$(SRCDIR)/ft_convert_d.c \
	$(SRCDIR)/ft_convert_u.c \
	$(SRCDIR)/ft_convert_p.c \
	$(SRCDIR)/ft_convert_xX.c

OBJDIR = objs
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

NAME = libftprintf.a

all: $(NAME)

$(NAME): $(OBJS)
	@$(AR) $@ $^

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@$(CC) $(CCFLAGS) -o $@ -c $<

clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
