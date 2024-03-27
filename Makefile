# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/27 11:12:33 by melshafi          #+#    #+#              #
#    Updated: 2024/03/27 12:50:15 by melshafi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ./philo/main.c\
		./philo/ft_atoi.c\
		./philo/create_destroy.c\
		./philo/threads.c\
		./philo/time_management.c\
		./philo/philo_tasks.c
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
