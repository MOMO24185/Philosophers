SRCS = ./philo/main.c
CFLAGS = -Wall -Wextra -Werror
INCLUDES = ./philo/
NAME = Philosophers
PROGRAM = philo
CC = cc
OBJECTS = ${SRCS:.c=.o}

${NAME}: ${SRCS}
	echo "Compiling program"
	${CC} ${CFLAGS} -fsanitize=address -g3 ${SRCS} -I ${INCLUDES} -o ${PROGRAM}

all:
	${NAME}

clean:
	echo "Cleaning files"
	rm -f ${OBJECTS} ${NAME}

fclean:	clean
	echo "Cleaning files and removing archives and program"
	rm -f ${PROGRAM}

re:	fclean all

.PHONY:	all clean fclean re
