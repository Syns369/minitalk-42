NAME = minitalk

LIBFT_DIR = libft-42/

LIBFT_FILE = libft.a

LIBFT = $(LIBFT_DIR)$(LIBFT_FILE)

SRC_DIR = srcs/

OBJ_DIR = objs/

CC = gcc

CFLAGS = -Wall -Werror -Wextra

RM = rm -rf

SRC_FILES = main\

SRCS = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJS = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

all: $(NAME)

$(LIBFT):
	@make all -C $(LIBFT_DIR)

$(NAME):	$(OBJS) $(LIBFT)
			$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) -lm

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c minitalk.h | $(OBJ_DIR)
				$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
			mkdir -p $(OBJ_DIR)

clean:
	make clean -C $(LIBFT_DIR)
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re