NAME = philo

SRC_PATH = sources/
OBJ_PATH = obj/

SRC_NAME = 	philo.c			\
			time.c			\
			entry.c			\
			init_end.c		\
			security.c		\
			core.c			\
			utils.c			\
			mutex.c			\

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
INC = -I includes

CC = gcc
FLAGS = -Wall -Wextra -Werror -g
LIBS = -lpthread
RM = @rm -rf

all: $(NAME)

$(NAME): $(OBJ)
		@echo "Build $(NAME)"
		@$(CC) $(FLAGS) $(INC) $(OBJ) -o $(NAME) $(LIBS)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
		mkdir -p $(@D)
		$(CC) $(FLAGS) $(INC) -o $@ -c $<

skiperror: $(OBJS)
			$(CC) -o $(NAME) $(SRCS) -lpthread

fsa:	$(OBJS)
		$(CC) -fsanitize=address $(FLAGS) -o $@ $(SRCS)

clean:
		$(RM) $(OBJ_PATH)

fclean:	clean
		$(RM) $(NAME)

re:	fclean
	make all

.PHONY: all clean fclean re
