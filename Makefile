NAME = philo
CC = gcc
FLAGS = -Wall -Werror -Wextra -pthread
RM = rm -rf

SRCS_FILE = main.c exit.c init.c parsing.c \
			philosopher.c supervisor.c time.c

SRCS_FOLD = srcs/

SRCS = $(addprefix $(SRCS_FOLD), $(SRCS_FILE))
OBJS = $(SRCS:.c=.o)

all : $(NAME)

%.o : %.c
	$(CC) $(FLAGS) -c $< -o $@

$(NAME) : $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $@

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re
