NAME = philo
CHECK = checker

SRCS =  main.c \
		srcs/utils.c \
		srcs/thread.c \
		srcs/init.c \
		
OBJS = ${SRCS:.c=.o}

CC = cc
CFLAGS = -Wall -Werror -Wextra #-fsanitize=thread -g

RM = rm -rf

all: ${NAME}
${NAME}: ${OBJS}
	@${CC} ${CFLAGS} ${OBJS} -o ${NAME}

clean: 
	@${RM} ${OBJS}

fclean: clean
	@${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re