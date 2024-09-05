CC = gcc
CFLAGS = -g -c -Wall -Wextra -Werror
NAME = minishell 
SRC_DIR = src
OBJ_DIR = obj
RM = rm -rf
SRC =  src/utils.c  src/ft_strtok.c src/utils_for_nodes.c src/tree.c src/execute_command.c src/filter_input.c src/replace_str.c  src/handle.c src/env.c src/unset.c  src/exit.c \
	src/initializer.c src/pipe.c src/marks.c src/lexer.c src/parser.c src/location.c src/direction.c src/directions2.c src/environment.c src/builtins.c src/utils_str.c src/allocations_free.c \
	src/builtins2.c src/control.c src/fd_for_process.c src/run_command.c src/utils_for_nodes2.c src/utils_str2.c src/utils_for_nodes3.c src/utils4.c

OBJ =$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.c
	@mkdir -p obj
	$(CC) $(CFLAGS) $<  -o $@

all: $(NAME)

$(NAME): $(OBJ) 
	gcc $(OBJ) -g -o $(NAME) -lreadline #-fsanitize=thread
clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all 

.PHONY: all fclean clean re

