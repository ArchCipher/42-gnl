# library and project names
NAME        = test.out
BONUS		= bonus.out
LEAKTEST    = leak.out

# compiler and flags
CC          = cc
FLAGS       = -Wall -Werror -Wextra
SFLAG      = -fsanitize=address
DFLAG		= -g

# headers
HEADERS     = get_next_line.h

# source files
MAIN	= main.c
SRCS	= get_next_line get_next_line_utils
MSRCS	= $(addsuffix .c, $(SRCS)) $(MAIN)
BSRCS	= $(addsuffix _bonus.c, $(SRCS)) $(MAIN)

all:
	@echo "Compiling with BUFFER_SIZE=255"
	$(CC) $(FLAGS) $(DFLAG) $(MSRCS) -o $(NAME)
	./$(NAME)

.PHONY: all clean fclean re

# Explicitly handle Makefile to prevent it from being treated as a buffer size
Makefile:
	@echo "Invalid target: Makefile"
	@echo "Usage: make <BUFFER_SIZE> or make leak <BUFFER_SIZE>"
	@exit 1

%: $(MSRCS) $(MAIN)
	@echo "Compiling with BUFFER_SIZE=$@"
	$(CC) $(FLAGS) $(DFLAG) -D BUFFER_SIZE=$@ $(MSRCS) -o $(NAME)
	./$(NAME)

# 	$(CC) $(FLAGS) $(DFLAG) -D BUFFER_SIZE=$@ $(SRCS) -o $(NAME)
#	$(CC) $(FLAGS) $(SFLAG) -D BUFFER_SIZE=$@ $(SRCS) -o $(NAME)

bonus: $(BSRCS)
	@echo "Compiling with BUFFER_SIZE=255 for bonus"
	$(CC) $(FLAGS) $(DFLAG) $(BSRCS) -o $(BONUS)
	./$(BONUS)

bonus%: $(BSRCS)
	@echo "Compiling with BUFFER_SIZE=$* for bonus"
	$(CC) $(FLAGS) $(DFLAG) -D BUFFER_SIZE=$* $(BSRCS) -o $(BONUS)
	./$(BONUS)

leak: $(MSRCS)
	@echo "Compiling with BUFFER_SIZE=255 for leak test"
	$(CC) $(FLAGS) $(MSRCS) -o $(LEAKTEST)
	leaks --atExit -- ./$(LEAKTEST)

leak%: $(MSRCS)
	@echo "Compiling with BUFFER_SIZE=$* for leak test"
	$(CC) $(FLAGS) -D BUFFER_SIZE=$* $(MSRCS) -o $(LEAKTEST)
	leaks --atExit -- ./$(LEAKTEST)

clean:
	rm -f $(NAME) $(BONUS) $(LEAKTEST)

fclean: clean

re: fclean all
