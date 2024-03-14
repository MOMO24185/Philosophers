SRCS = ./philo/main.c\
		./philo/ft_atoi.c
CFLAGS = -Wall -Wextra -Werror -pthread -g3
INCLUDES = ./philo/
NAME = Philosophers
PROGRAM = ./philo/philo
CC = cc
OBJECTS = ${SRCS:.c=.o}

${NAME}: ${SRCS}
	echo "Compiling program"
	${CC} ${CFLAGS} ${SRCS} -I ${INCLUDES} -o ${PROGRAM}

all: ${NAME}

clean:
	echo "Cleaning files"
	rm -f ${OBJECTS}

fclean:	clean
	echo "Cleaning files and removing archives and program"
	rm -f ${PROGRAM}

re:	fclean all

.PHONY:	all clean fclean re
