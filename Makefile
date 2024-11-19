NAME = pipex

MAINDIR = 000_MAIN/
UTILDIR = 100_UTILS/

SRC = main.c ft_parser.c ft_free_all.c ft_path.c ft_realloc.c ft_process.c ft_err.c

MAINSRC = $(MAINDIR)ft_process.c \
	$(MAINDIR)ft_parser.c \
	$(MAINDIR)main.c
UTILSSRC = $(UTILDIR)ft_err.c \
	$(UTILDIR)ft_realloc.c \
	$(UTILDIR)ft_path.c \
	$(UTILDIR)ft_free_all.c

LIB = 010_FT_PRINTF/libftprintf.a 020_LIBFT/libft.a

OBJDIR = 666_OBJ/
OBJ = $(patsubst %.c,$(OBJDIR)%.o,$(notdir $(MAINSRC) $(UTILSSRC)))

CCA = cc -Wall -Werror -Wextra -g3

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C 010_FT_PRINTF/
	$(MAKE) -C 020_LIBFT/
	$(CCA) -o $(NAME) $(OBJ) $(LIB)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)%.o: $(MAINDIR)%.c | $(OBJDIR) $(GNLXIO)
	$(CCA) -o $@ -c $<

$(OBJDIR)%.o: $(UTILDIR)%.c | $(OBJDIR)
	$(CCA) -o $@ -c $<

clean:
	$(MAKE) clean -C 010_FT_PRINTF/
	$(MAKE) clean -C 020_LIBFT/
	rm -f $(OBJ)

fclean: clean
	$(MAKE) fclean -C 010_FT_PRINTF/
	$(MAKE) fclean -C 020_LIBFT/
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
