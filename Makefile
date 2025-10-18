# Library and project names
NAME        = test.out
BONUS		= bonus.out
LEAKTEST    = leak.out

# Compiler and Flags
CC          = cc
FLAGS       = -Wall -Werror -Wextra
SFLAG      = -fsanitize=address
DFLAG		= -g

# headers
HEADERS     = get_next_line.h get_next_line_bonus.h

# source files
MAIN	= main.c
SRCS	= get_next_line get_next_line_utils
MSRCS	= $(addsuffix .c, $(SRCS)) $(MAIN)
BSRCS	= $(addsuffix _bonus.c, $(SRCS)) $(MAIN)

# No explicit BUFFER_SIZE
all:
	@echo "Compiling with BUFFER_SIZE=255"
	$(CC) $(FLAGS) $(DFLAG) $(MSRCS) -o $(NAME)
	./$(NAME)

# Explicitly handle Makefile to prevent it from being treated as a buffer size
Makefile:
	@echo "Invalid target: Makefile"
	@echo "Usage: make <BUFFER_SIZE> or make leak <BUFFER_SIZE>"
	@exit 1

# Handle explicit BUFFER_SIZE
%: $(MSRCS) $(MAIN)
	@echo "Compiling with BUFFER_SIZE=$@"
	$(CC) $(FLAGS) $(DFLAG) -D BUFFER_SIZE=$@ $(MSRCS) -o $(NAME)
	./$(NAME)

# 	$(CC) $(FLAGS) $(DFLAG) -D BUFFER_SIZE=$@ $(SRCS) -o $(NAME)
#	$(CC) $(FLAGS) $(SFLAG) -D BUFFER_SIZE=$@ $(SRCS) -o $(NAME)

# No explicit BUFFER_SIZE
bonus: $(BSRCS)
	@echo "Compiling with BUFFER_SIZE=255 for bonus"
	$(CC) $(FLAGS) $(DFLAG) $(BSRCS) -o $(BONUS)
	./$(BONUS)

# Handle explicit BUFFER_SIZE
bonus%: $(BSRCS)
	@echo "Compiling with BUFFER_SIZE=$* for bonus"
	$(CC) $(FLAGS) $(DFLAG) -D BUFFER_SIZE=$* $(BSRCS) -o $(BONUS)
	./$(BONUS)

# No explicit BUFFER_SIZE
leak: $(MSRCS)
	@echo "Compiling with BUFFER_SIZE=255 for leak test"
	$(CC) $(FLAGS) $(MSRCS) -o $(LEAKTEST)
	leaks --atExit -- ./$(LEAKTEST)

# Handle explicit BUFFER_SIZE
leak%: $(MSRCS)
	@echo "Compiling with BUFFER_SIZE=$* for leak test"
	$(CC) $(FLAGS) -D BUFFER_SIZE=$* $(MSRCS) -o $(LEAKTEST)
	leaks --atExit -- ./$(LEAKTEST)

clean:
	rm -f $(NAME) $(BONUS) $(LEAKTEST)

fclean: clean

re: fclean all

.PHONY: all clean fclean re