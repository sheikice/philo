# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jwuille <jwuille@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/14 18:44:28 by jwuille           #+#    #+#              #
#    Updated: 2025/08/20 16:36:11 by jwuille          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR = src
OBJ_DIR = obj


SRC =	quit_error.c \
		start_simulation.c \
		ft_atoi.c \
		check_params.c \
		thread_run.c \
		free_memory.c \
		routine.c \
		print_time.c \
		main.c


CC = cc -MD
# ASAN = 

# I = -Iincludes/mandatory
CFLAGS = -Wall -Werror -Wextra -g3
NAME = philo

OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

# ================== SRC =============================
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJB_DIR): 
	@mkdir -p $(OBJB_DIR)

clean_obj:
	@rm -rf $(OBJ_DIR)

clean_objb:
	@rm -rf $(OBJB_DIR)

clean:
	rm -f $(OBJ) $(OBJB)
	@rm -rf $(OBJ_DIR)
	@rm -rf $(OBJB_DIR)

fclean: clean
	rm -f $(NAME)
	@rm -rf .cache
	@rm -f compile_commands.json
 
re: fclean all

-include $(OBJ_DIR)/*.d
-include $(OBJB_DIR)/*.d

.PHONY: all clean fclean re bonus 
