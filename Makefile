NAME = philo

CC		= gcc

CFLAGS	= -Wall -Werror -Wextra -pthread -g3



SRCS		= main.c \
				thread.c \
				death.c	\
				message.c \
				initialize.c \
				functions.c \

OBJS		= $(SRCS:.c=.o)

RM 			:= rm -rf
MAKEFLAGS	+= --no-print-directory
all: $(NAME) 

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:

	$(RM) $(OBJS)	

fclean: clean
		$(RM) $(NAME)

re: 
		$(MAKE) fclean
		$(MAKE) all

.PHONY: all clean fclean re 
