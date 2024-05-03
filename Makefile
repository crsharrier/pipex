NAME:= pipex
CC:= cc
CFLAGS:= -Wall -Wextra -Werror
INCLUDES_DIR:= ./includes
SRC_DIR:= ./
LIBFT:= libft.a

TEST_SRC:= ./test/test.c
TEST_BONUS_SRC:= ./test/test_bonus.c

MANDATORY_NAMES:= pipex px_utils
SRCS := ${addprefix ${SRC_DIR}, $(addsuffix .c, $(MANDATORY_NAMES))}
OBJS:= $(SRCS:.c=.o)

all: $(NAME)

test: all 
	@make -C ./test all

$(NAME): $(OBJS) | $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -I $(INCLUDES_DIR) -L ./libft -lft -o $@

$(LIBFT):
	@echo "Compiling libft..."
	@make -C ./libft all

$(OBJS): %.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INCLUDES_DIR) -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME) && make -C ./libft fclean

re: fclean all

PHONY: all libft clean fclean re test