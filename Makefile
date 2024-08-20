NAME = philo
CHECK = checker

SRCS =  main.c \
		ft_atoi.c \
		utils.c \
		
		
OBJS = ${SRCS:.c=.o}

CC = cc
CFLAGS = -Wall

RM = rm -rf

all: ${NAME}
${NAME}: ${OBJS}
	@${CC} ${OBJS} -o ${NAME}

clean: 
	@${RM} ${OBJS}

fclean: clean
	@${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re