NAMECL = client
NAMESV = server

LIBFT_DIR = libft-42/

LIBFT_FILE = libft.a

LIBFT = $(LIBFT_DIR)$(LIBFT_FILE)

SRC_DIR = srcs/

OBJ_DIR = objs/

CC = gcc

CFLAGS = -Wall -Werror -Wextra -g

RM = rm -rf

SRC_CLIENT_FILES = client
SRC_SERVER_FILES = server

SRC_CLIENT_FILES_BONUS = client_bonus
SRC_SERVER_FILES_BONUS = server_bonus

SRCS_CLIENT = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_CLIENT_FILES)))
OBJS_CLIENT = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_CLIENT_FILES)))

SRCS_SERVER = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_SERVER_FILES)))
OBJS_SERVER = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_SERVER_FILES)))

SRCS_CLIENT_BONUS = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_CLIENT_FILES_BONUS)))
OBJS_CLIENT_BONUS = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_CLIENT_FILES_BONUS)))

SRCS_SERVER_BONUS = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_SERVER_FILES_BONUS)))
OBJS_SERVER_BONUS = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_SERVER_FILES_BONUS)))

OBJS = $(OBJS_CLIENT) $(OBJS_SERVER)

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

bonus: $(OBJS_CLIENT_BONUS) $(OBJS_SERVER_BONUS) $(LIBFT)
		$(CC) $(CFLAGS) -o $(NAMECL) $(OBJS_CLIENT_BONUS) $(LIBFT)
		$(CC) $(CFLAGS) -o $(NAMESV) $(OBJS_SERVER_BONUS) $(LIBFT)

clean:
	make clean -C $(LIBFT_DIR)
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAMECL) $(NAMESV)
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re