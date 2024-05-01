NAME:= compare_files
CC:= cc
CFLAGS:= -Wall -Wextra -Werror
INCLUDES_DIR:= ../
SRC_DIR:= ./
LIBFT:= libft.a

MANDATORY_NAMES:= compare_files
SRCS := ${addprefix ${SRC_DIR}, $(addsuffix .c, $(MANDATORY_NAMES))}
OBJS:= $(SRCS:.c=.o)

all: $(NAME)
	./run_tests.sh

$(NAME): $(OBJS) | $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -I $(INCLUDES_DIR) -L ../libft -lft -o $@

$(LIBFT):
	@echo "Compiling libft..."
	@make -C ../libft all

$(OBJS): %.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INCLUDES_DIR) -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME) && make -C ../libft fclean

re: fclean all

PHONY: all libft clean fclean re