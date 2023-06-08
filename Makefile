SRCS		= main.c \
		  path.c \
		  recursive.c \
		  register.c

OBJS		= ${SRCS:.c=.o}

LFT			= ./libft/libft.a

HEAD		= spider.h

NAME		= minishell

CC			= gcc

CFLAGS		= -g -Wall -Wextra -Werror

.c.o:		
			${CC} ${CFLAGS} -I-${HEAD} -Ilibft -c $< -o ${<:.c=.o} 

${NAME}:	${LFT} ${OBJS}
			${CC} ${CFLAGS} ${OBJS} -L ./libft -o ${NAME}

${LFT}:
			make -s -C libft

all:		${NAME}

bonus:		all

clean:
			${RM} ${OBJS} ${OBJS_BONUS}
			make clean -C libft

fclean:		clean
			${RM} ${NAME}
			make fclean -C libft

re:			fclean all

.PHONY:		all clean fclean re
