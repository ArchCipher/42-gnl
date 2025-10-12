# library and project names
NAME        = test.out
LEAKTEST    = leak.out

# compiler and flags
CC          = cc
FLAGS       = -Wall -Werror -Wextra
SFLAGS      = -fsanitize=address
DFLAG		= -g

# headers
HEADERS     = get_next_line.h

# source files
SRCS = get_next_line.c get_next_line_utils.c

all:
	@echo "Usage: "
	@echo "make <BUFFER_SIZE>"
	@echo "make leak <BUFFER_SIZE>"

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

#	$(CC) $(FLAGS) $(SFLAGS) -D BUFFER_SIZE=$@ $(SRCS) -o $(NAME)

leak%: $(SRCS)
	@if ! echo "$*" | grep -q '^[0-9]\+$$'; then \
		echo "Invalid target: leak$*"; \
		echo "Usage: make <BUFFER_SIZE> or make leak <BUFFER_SIZE>"; \
		exit 1; \
	fi
	@echo "Compiling with BUFFER_SIZE=$* for leak test"
	$(CC) $(FLAGS) -D BUFFER_SIZE=$* $(SRCS) -o $(LEAKTEST)
	leaks --atExit -- ./$(LEAKTEST)

fclean:
	rm -f $(NAME) $(LEAKTEST)

re: fclean all
