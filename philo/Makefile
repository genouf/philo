
SRCS = 	sources/philo.c			\
		sources/time.c			\
		sources/entry.c			\
		sources/init_philo.c	\
		sources/security.c		\
		sources/core.c			\
		sources/utils.c			\

OBJS = ${SRCS:.c=.o}

INC = includes/philo.h

NAME = philo

RM = rm -f

CC = gcc
FLAGS = -Wall -Wextra -Werror

all: ${NAME}

${NAME}: ${OBJS}
			${CC} ${FLAGS} -o $@ ${SRCS} -lpthread

/%.o: %.c
			${CC} ${FLAGS} -c $@ $<

skiperror: ${OBJS}
			${CC} -o ${NAME} ${SRCS} -lpthread

fsa:	${OBJS}
		${CC} -fsanitize=address ${FLAGS} -o $@ ${SRCS}

clean:
		${RM} ./${OBJS}

fclean:	clean
		${RM} ${NAME}

re:	fclean
	make all
