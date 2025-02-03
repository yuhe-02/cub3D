CC = cc
AR = ar rc
CFLAGS = -Wall -Wextra -Werror

SRCDIR = .
INCDIR = .

SRCS = $(SRCDIR)/ft_isalpha.c \
	$(SRCDIR)/ft_isdigit.c \
	$(SRCDIR)/ft_isalnum.c \
	$(SRCDIR)/ft_isascii.c \
	$(SRCDIR)/ft_isprint.c \
	$(SRCDIR)/ft_strlen.c \
	$(SRCDIR)/ft_memset.c \
	$(SRCDIR)/ft_bzero.c \
	$(SRCDIR)/ft_memcpy.c \
	$(SRCDIR)/ft_memmove.c \
	$(SRCDIR)/ft_memchr.c \
	$(SRCDIR)/ft_memcmp.c \
	$(SRCDIR)/ft_strnstr.c \
	$(SRCDIR)/ft_strlcpy.c \
	$(SRCDIR)/ft_strlcat.c \
	$(SRCDIR)/ft_toupper.c \
	$(SRCDIR)/ft_tolower.c \
	$(SRCDIR)/ft_strchr.c \
	$(SRCDIR)/ft_strrchr.c \
	$(SRCDIR)/ft_strncmp.c \
	$(SRCDIR)/ft_atoi.c \
	$(SRCDIR)/ft_calloc.c \
	$(SRCDIR)/ft_strdup.c \
	$(SRCDIR)/ft_substr.c \
	$(SRCDIR)/ft_strjoin.c \
	$(SRCDIR)/ft_strtrim.c \
	$(SRCDIR)/ft_split.c \
	$(SRCDIR)/ft_itoa.c \
	$(SRCDIR)/ft_strmapi.c \
	$(SRCDIR)/ft_striteri.c \
	$(SRCDIR)/ft_putchar_fd.c \
	$(SRCDIR)/ft_putstr_fd.c \
	$(SRCDIR)/ft_putendl_fd.c \
	$(SRCDIR)/ft_putnbr_fd.c

OBJDIR = objs
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

BONUS_SRCS = $(SRCDIR)/ft_lstnew.c \
	$(SRCDIR)/ft_lstadd_front.c \
	$(SRCDIR)/ft_lstsize.c \
	$(SRCDIR)/ft_lstlast.c \
	$(SRCDIR)/ft_lstadd_back.c \
	$(SRCDIR)/ft_lstdelone.c \
	$(SRCDIR)/ft_lstclear.c \
	$(SRCDIR)/ft_lstiter.c \
	$(SRCDIR)/ft_lstmap.c

BONUS_OBJS = $(BONUS_SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

ifdef WITH_BONUS
	SRCS += $(BONUS_SRCS)
	OBJS += $(BONUS_OBJS)
endif

NAME = libft.a

all: $(NAME)

$(NAME): $(OBJS)
	@$(AR) $@ $^

bonus:
	@make WITH_BONUS=1

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@$(CC) $(CCFLAGS) -o $@ -c $<

clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
