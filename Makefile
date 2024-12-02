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
	$(UTILDIRBONUS)ft_free_all_bonus.c \
	$(UTILDIRBONUS)ft_env_var_bonus.c

LIB = 010_FT_PRINTF/libftprintf.a 020_LIBFT/libft.a

OBJDIR = 666_OBJ/
OBJ = $(patsubst %.c,$(OBJDIR)%.o,$(notdir $(MAINSRC) $(UTILSSRC)))
OBJBONUS = $(patsubst %.c,$(OBJDIR)%.o,$(notdir $(MAINSRCBONUS) $(UTILSSRCBONUS)))

TOTAL_FILES = $(words $(OBJ))
TOTAL_FILES_BONUS = $(words $(OBJBONUS))
PROGRESS = 0
TERM_WIDTH = $(shell tput cols)
BAR_WIDTH = $(shell echo $$(( ($(TERM_WIDTH) - 30) > 60 ? 50 : ($(TERM_WIDTH) - 19) - 10 )))
COLORS = "\033[4;30m\033[4;31m\033[4;37m\033[4;33m\033[4;34m\033[4;35m\033[4;36m\033[1;31m\033[1;37m\033[1;33m\033[1;34m\033[1;35m\033[1;36m\033[1;90m\033[1;91m\033[1;92m\033[1;93m\033[1;94m\033[1;95m\033[1;96m\033[1;97m"
CHARACTERS = "!?@0&:.%=+"
RESET_COLOR = "\033[0m"

PRINT_PROGRESS:=
define PRINT_PROGRESS
	$(eval PROGRESS := $(shell echo $$(( $(PROGRESS) + 1 ))))
	@BARS=$$(($(PROGRESS) * $(BAR_WIDTH) / $(TOTAL_FILES))); \
	EMPTY=$$(( $(BAR_WIDTH) - $$BARS )); \
	PERCENT=$$(($(PROGRESS) * 100 / $(TOTAL_FILES))); \
	printf "\033[1;32m\033[1mPipex: \033[37mCompiling: \033[1;32m[+ "; \
	for i in $$(seq 1 $$BARS); do \
		COLOR=$$(echo $(COLORS) | fold -w 7 | shuf -n 1); \
		CHAR=$$(echo $(CHARACTERS) | fold -w 1 | shuf -n 1); \
		echo -n "\033[0;42m"$$COLOR$$CHAR$(RESET_COLOR); \
	done; \
	for i in $$(seq 1 $$EMPTY); do \
		echo -n " "; \
	done; \
	printf "\033[1;32m +] \033[34m$$PERCENT%%\033[0m\r"
endef

PRINT_PROGRESS_BONUS:=
define PRINT_PROGRESS_BONUS
	$(eval PROGRESS := $(shell echo $$(( $(PROGRESS) + 1 ))))
	@BARS=$$(($(PROGRESS) * $(BAR_WIDTH) / $(TOTAL_FILES_BONUS))); \
	EMPTY=$$(( $(BAR_WIDTH) - $$BARS )); \
	PERCENT=$$(($(PROGRESS) * 100 / $(TOTAL_FILES_BONUS))); \
	printf "\033[1;32m\033[1mPipex: \033[37mCompiling: \033[1;32m[+ "; \
	for i in $$(seq 1 $$BARS); do \
		COLOR=$$(echo $(COLORS) | fold -w 7 | shuf -n 1); \
		CHAR=$$(echo $(CHARACTERS) | fold -w 1 | shuf -n 1); \
		echo -n "\033[0;42m"$$COLOR$$CHAR$(RESET_COLOR); \
	done; \
	for i in $$(seq 1 $$EMPTY); do \
		echo -n " "; \
	done; \
	printf "\033[1;32m +] \033[34m$$PERCENT%%\033[0m\r"
endef

CCA = cc -Wall -Werror -Wextra -g3

MAKEFLAGS += --no-print-directory

all: $(NAME)

bonus: $(LIB) $(OBJDIR) $(OBJBONUS)
	@$(CCA) -o $(NAME) $(OBJBONUS) $(LIB)
	@printf "\n\033[32m\033[1mPipex: \033[1;97mBuild Complete !\033[0m\n"

$(NAME): $(LIB) $(OBJ)
	@$(CCA) -o $(NAME) $(OBJ) $(LIB)
	@printf "\n\033[32m\033[1mPipex: \033[1;97mBuild Complete !\033[0m\n"

$(LIB):
	@$(MAKE) -C 010_FT_PRINTF/
	@$(MAKE) -C 020_LIBFT/

$(OBJDIR):
	@mkdir -p $(OBJDIR)
	@printf "\033[32m\033[1mPipex: \033[1;37m666_OBJ/ Generated !\033[0m\n"

$(OBJDIR)%.o: $(MAINDIR)%.c | $(OBJDIR)
	@$(CCA) -o $@ -c $<
	$(PRINT_PROGRESS)

$(OBJDIR)%.o: $(UTILDIR)%.c | $(OBJDIR)
	@$(CCA) -o $@ -c $<
	$(PRINT_PROGRESS)

$(OBJDIR)%.o: $(MAINDIRBONUS)%.c | $(OBJDIR)
	@$(CCA) -o $@ -c $<
	$(PRINT_PROGRESS_BONUS)

$(OBJDIR)%.o: $(UTILDIRBONUS)%.c | $(OBJDIR)
	@$(CCA) -o $@ -c $<
	$(PRINT_PROGRESS_BONUS)

clean:
	@$(MAKE) clean -C 010_FT_PRINTF/
	@$(MAKE) clean -C 020_LIBFT/
	@rm -f $(OBJ) $(OBJBONUS)
	@printf "\033[32m\033[1mPipex: \033[1;37m666_OBJ/ Cleaned !\033[0m\n"

fclean:
	@$(MAKE) fclean -C 010_FT_PRINTF/
	@$(MAKE) fclean -C 020_LIBFT/
	@rm -f $(OBJ) $(OBJBONUS) $(NAME)
	@printf "\033[32m\033[1mPipex: \033[1;37mCleaned !\033[0m\n"

re: fclean all

.PHONY: all bonus clean fclean re
