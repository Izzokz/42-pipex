NAME = pipex

MAINDIR = 000_PIPEX/000_MAIN/
UTILDIR = 000_PIPEX/100_UTILS/
MAINDIRBONUS = 001_PIPEX_BONUS/000_MAIN/
UTILDIRBONUS = 001_PIPEX_BONUS/100_UTILS/

MAINSRC = $(MAINDIR)ft_process.c \
	$(MAINDIR)ft_parser.c \
	$(MAINDIR)main.c
UTILSSRC = $(UTILDIR)ft_err.c \
	$(UTILDIR)ft_realloc.c \
	$(UTILDIR)ft_path.c \
	$(UTILDIR)ft_free_all.c

MAINSRCBONUS = $(MAINDIRBONUS)ft_process_bonus.c \
	$(MAINDIRBONUS)ft_parser_bonus.c \
	$(MAINDIRBONUS)main_bonus.c
UTILSSRCBONUS = $(UTILDIRBONUS)ft_err_bonus.c \
	$(UTILDIRBONUS)ft_realloc_bonus.c \
	$(UTILDIRBONUS)ft_path_bonus.c \
	$(UTILDIRBONUS)ft_free_all_bonus.c

LIB = 010_FT_PRINTF/libftprintf.a 020_LIBFT/libft.a

OBJDIR = 666_OBJ/
OBJ = $(patsubst %.c,$(OBJDIR)%.o,$(notdir $(MAINSRC) $(UTILSSRC)))
OBJBONUS = $(patsubst %.c,$(OBJDIR)%.o,$(notdir $(MAINSRCBONUS) $(UTILSSRCBONUS)))

CCA = cc -Wall -Werror -Wextra -g3

all: $(NAME)


bonus: $(OBJDIR) $(OBJBONUS)
	$(MAKE) -C 010_FT_PRINTF/
	$(MAKE) -C 020_LIBFT/
	$(CCA) -o $(NAME) $(OBJBONUS) $(LIB)

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

$(OBJDIR)%.o: $(MAINDIRBONUS)%.c | $(OBJDIR) $(GNLXIO)
	$(CCA) -o $@ -c $<

$(OBJDIR)%.o: $(UTILDIRBONUS)%.c | $(OBJDIR)
	$(CCA) -o $@ -c $<

clean:
	$(MAKE) clean -C 010_FT_PRINTF/
	$(MAKE) clean -C 020_LIBFT/
	rm -f $(OBJ) $(OBJBONUS)

fclean: clean
	$(MAKE) fclean -C 010_FT_PRINTF/
	$(MAKE) fclean -C 020_LIBFT/
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
