NAMECL = client
NAMESV = server

LIBFT_DIR = libft-42/

LIBFT_FILE = libft.a

LIBFT = $(LIBFT_DIR)$(LIBFT_FILE)

SRC_DIR = srcs/

OBJ_DIR = objs/

CC = gcc

CFLAGS = -Wall -Werror -Wextra

RM = rm -rf

SRC_CLIENT_FILES = client
SRC_SERVER_FILES = server

SRCS_CLIENT = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_CLIENT_FILES)))
OBJS_CLIENT = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_CLIENT_FILES)))

SRCS_SERVER = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_SERVER_FILES)))
OBJS_SERVER = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_SERVER_FILES)))

all: $(NAMECL) $(NAMESV)

$(LIBFT):
	@make all -C $(LIBFT_DIR)

$(NAMECL):	$(OBJS_CLIENT) $(LIBFT)
			$(CC) $(CFLAGS) -o $(NAMECL) $(OBJS_CLIENT) $(LIBFT)

$(NAMESV):	$(OBJS_SERVER) $(LIBFT)
			$(CC) $(CFLAGS) -o $(NAMESV) $(OBJS_SERVER) $(LIBFT)

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c minitalk.h | $(OBJ_DIR)
				$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
			mkdir -p $(OBJ_DIR)

clean:
	make clean -C $(LIBFT_DIR)
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAMECL) $(NAMESV)
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re