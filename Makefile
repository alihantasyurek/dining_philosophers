NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

SRCS = 	data_init.c\
		dinner.c\
		main.c\
		monitor.c\
		mutex_funcs.c\
		print.c\
		syntax_check.c\
		utils.c 

$(NAME) :
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

all : $(NAME)

clean :
	$(RM) $(NAME)

fclean : 
	$(RM) $(NAME)

re : fclean all

.PHONY: all clean fclean re
