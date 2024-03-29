NAME = philo
CFLAGS = -Wall -Wextra -Werror
CC = gcc

LIBFT = libft.a
LIBFT_DIR = lib/libft
LIBFT_FILE = $(LIBFT_DIR)/$(LIBFT)
LIBFT_FLAGS = -L./$(LIBFT_DIR) -lft
CFLAGS += -I $(LIBFT_DIR)
CFLAGS += -I ./inc/

FILES = philo \
		philo_thread \
		wrapping_func \
		active \
		util1 \
		critical_util \
		print


SRCS = $(addprefix srcs/, $(addsuffix .c, $(FILES))) 

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	$(MAKE) -C ./lib/libft
	$(CC) $(CFLAGS) -g -o $(NAME) main.c $(SRCS) $(LIBFT_FLAGS) -lpthread
	
clean :
	$(MAKE) clean -C ./lib/libft
	rm -rf $(SURP)
	rm -f $(OBJS) $(C_OBJS)

fclean :
	$(MAKE) fclean -C ./lib/libft
	rm -f $(OBJS) $(C_OBJS) $(NAME)
	
re : fclean all

.PHONY: clean fclean all re bonus
