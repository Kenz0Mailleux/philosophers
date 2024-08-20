NAME = philo
CHECK = checker

SRCS =  main.c \
		ft_atoi.c \
		
		
OBJS = ${SRCS:.c=.o}

CC = cc
CFLAGS = -Wall

RM = rm -rf

all: ${NAME}
${NAME}: ${OBJS}
	@${CC} ${OBJS} -o ${NAME}

clean: 
	@${MAKE} -C
	@${RM} ${OBJS}

fclean: clean
	@${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re