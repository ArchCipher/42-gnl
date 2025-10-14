# library and project names
NAME        = test.out
LEAKTEST    = leak.out

# compiler and flags
CC          = cc
FLAGS       = -Wall -Werror -Wextra
SFLAG      = -fsanitize=address
DFLAG		= -g

# headers
HEADERS     = get_next_line.h

# source files
SRCS = get_next_line.c get_next_line_utils.c main.c

all:
	@echo "Compiling with BUFFER_SIZE=64"
	$(CC) $(FLAGS) $(DFLAG) $(SRCS) -o $(NAME)
	./$(NAME)

.PHONY: all clean fclean re

# Explicitly handle Makefile to prevent it from being treated as a buffer size
Makefile:
	@echo "Invalid target: Makefile"
	@echo "Usage: make <BUFFER_SIZE> or make leak <BUFFER_SIZE>"
	@exit 1

%: $(SRCS)
	@echo "Compiling with BUFFER_SIZE=$@"
	$(CC) $(FLAGS) $(DFLAG) -D BUFFER_SIZE=$@ $(SRCS) -o $(NAME)
	./$(NAME)

# 	$(CC) $(FLAGS) $(DFLAG) -D BUFFER_SIZE=$@ $(SRCS) -o $(NAME)
#	$(CC) $(FLAGS) $(SFLAG) -D BUFFER_SIZE=$@ $(SRCS) -o $(NAME)

leak: $(SRCS)
	@echo "Compiling with BUFFER_SIZE=64"
	$(CC) $(FLAGS) $(SRCS) -o $(LEAKTEST)
	leaks --atExit -- ./$(LEAKTEST)

leak%: $(SRCS)
	@echo "Compiling with BUFFER_SIZE=$* for leak test"
	$(CC) $(FLAGS) -D BUFFER_SIZE=$* $(SRCS) -o $(LEAKTEST)
	leaks --atExit -- ./$(LEAKTEST)

fclean:
	rm -f $(NAME) $(LEAKTEST)

re: fclean all
