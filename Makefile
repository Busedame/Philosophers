# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/21 14:08:18 by nholbroo          #+#    #+#              #
#    Updated: 2024/09/30 17:08:42 by nholbroo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=cc
CFLAGS=-Wall -Wextra -Werror
SRC=src/init/init_args.c \
src/init/inits.c \
src/simulation/monitor.c \
src/simulation/philo_routine.c \
src/simulation/philo_utils.c \
src/simulation/simulation.c \
src/simulation_utils/get_and_set.c \
src/simulation_utils/mutex_action.c \
src/simulation_utils/print.c \
src/simulation_utils/time.c \
src/utils/errors.c \
src/utils/free.c \
src/utils/standard_functions.c \
src/main.c

OBJ=$(patsubst src/%, build/%, $(SRC:.c=.o))
NAME=philo

all:	$(NAME)

# Compiling the object files and making an executable.
$(NAME):	$(OBJ)
			@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

# Making a build directory to store the object files if the build directory
# doesn't exist.
build:	
		@if [ ! -d "build" ]; \
			then mkdir -p "build"; \
		fi

# Making the subdirectories in the build-directory, and compiling the source files,
# making them object files.
build/%.o: src/%.c
		@mkdir -p $(dir $@)
		@echo "Compiling \e[1;32m$(notdir $<)\e[0m"
		@$(CC) $(CFLAGS) -Iinc -c $< -o $@;

# Cleans up all the object files, but not the build-directory or the 
# subdirectories inside.
clean:
	@rm -f build/*.o
	@rm -f build/*/*.o
	@echo "\e[1;32mAll object files removed\e[0m"

# Cleans up all object files and the build-directory, and removes the executable.
fclean:
	@rm -rf build
	@rm -f $(NAME)
	@echo "\e[1;32mBuild directory and executable removed\e[0m"

# Cleans up everything and compiles everything again.
re: fclean all

.PHONY: all clean fclean re
