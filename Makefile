# DEFINITIONS:
# $@ = Rule object $(NAME)
# $^ = Dependencies $(HDRS) and $(OBJS)
# $<: First dependency in the rule (.c source file being compiled)
# -o $(<:.c=.o): Object file name after compilation
# -C: Change directory
# -c: Compile the source file and generate the object, without performing the link stage

# Declaration of variables:
# \---------------------------------------------------/
# Program name
NAME = philo

# Source code files
SRC = data_checker.c \
	utils.c \
	msg.c \
	main.c \
	struct_init.c \
	thread_routine.c \
	thread_utils.c \
	monitor.c

# Object code files
OBJS = $(SRC:.c=.o)

# Compilation flags
CFLAGS = -g -Wall -Werror -Wextra

# Compilation flag FSANITIZE
# CFLAGS = -fsanitize=thread -g -Wall -Werror -Wextra

# Compilation flag POSIX
EXTRA = -pthread

# Compile command
CC = gcc

# Remove if exists
RM = rm -f
# \----------------------------------------------------/

# Rules:
# \---------------------------------------------------/
# Rule that generates SRC OBJS
.c.o:
	@echo "Compiling..."
	$(CC) -c $(CFLAGS) $< -o $@

# Rule that compiles the main program and generates the binary (executable) object
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(EXTRA) -o $@
	@echo "$@ has been generated!"


# Run with the make command and compile the main file
all: $(NAME)

# Delete all .o files if any (-f)
clean:
	$(RM) *.o
	@echo "Deleted OBJS files"

# Delete all files and program
fclean: clean
	$(RM) $(NAME)
#	rm -rf *.dSYM
	@echo "$(NAME) deleted"

# Perform a re-make (delete and do make)
re: fclean all

# Indicates that these names are not files but actions
.PHONY: all clean fclean re
# \----------------------------------------------------/
