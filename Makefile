LIBFT_SRC= \
		./ft_atoi.c					./ft_strdup.c			\
		./ft_bzero.c					./ft_strjoin.c			\
		./ft_calloc.c					./ft_strlcat.c			\
		./ft_isalnum.c					./ft_strlcpy.c			\
		./ft_isalpha.c					./ft_strlen.c			\
		./ft_isascii.c					./ft_strmapi.c			\
		./ft_isdigit.c					./ft_strncmp.c			\
		./ft_islower.c					./ft_strncpy.c			\
		./ft_isprint.c					./ft_strnstr.c			\
		./ft_isspace.c					./ft_strrchr.c			\
		./ft_isupper.c					./ft_strtrim.c			\
		./ft_itoa.c					./ft_strdel.c			\
		./ft_memccpy.c					./ft_substr.c			\
		./ft_memchr.c					./ft_tolower.c			\
		./ft_memcmp.c					./ft_toupper.c			\
		./ft_memcmp.c					./ft_lstsize.c			\
		./ft_memcpy.c					./ft_lstnew.c			\
		./ft_memmove.c					./ft_lstlast.c			\
		./ft_memset.c					./ft_lstiter.c			\
		./ft_putchar_fd.c				./ft_lstdelone.c		\
		./ft_putendl_fd.c				./ft_lstclear.c			\
		./ft_putnbr_fd.c				./ft_lstadd_front.c		\
		./ft_putstr_fd.c				./ft_lstadd_back.c		\
		./ft_split.c					./ft_strequ.c			\
		./ft_strchr.c					./ft_ssplit.c			\
		./ft_strcpy.c					./ft_atof.c			\
		./ft_str_c_count.c				./ft_putchar.c			\
		./ft_putstr.c					./ft_putnbr.c			\
		./ft_error_exit.c				./ft_split_clear.c		\

LIBFT_SRC := $(addprefix libft/, $(LIBFT_SRC))
LIBFT = libft.a

HEADER_DIR = ./includes

HEADERS = includes/minitalk.h	\

NAME = minitalk

SERVER = server
SERVER_SRC = srcs/server.c
SERVER_OBJ = $(SERVER_SRC:.c=.o)

CLIENT = client
CLIENT_SRC = srcs/client.c
CLIENT_OBJ = $(CLIENT_SRC:.c=.o)

FTFLAGS= -Llibft -lft

GCC = clang

RM = rm -f

CFLAGS = -Wall -Werror -Wextra

all : $(NAME) 

$(LIBFT): $(LIBFT_SRC)
	make -C ./libft

$(SERVER_OBJ): %.o: %.c $(HEADERS) Makefile
	$(GCC) $(CFLAGS) -c $< -I $(HEADER_DIR) -o $@

$(CLIENT_OBJ): %.o: %.c $(HEADERS) Makefile
	$(GCC) $(CFLAGS) -c $< -I $(HEADER_DIR) -o $@

$(NAME) : $(SERVER) $(CLIENT)

$(SERVER) : $(SERVER_OBJ) $(LIBFT)
	$(GCC) $(SERVER_OBJ) $(CFLAGS) $(FTFLAGS) -o $(SERVER) 
	
$(CLIENT) : $(CLIENT_OBJ) $(LIBFT)
	$(GCC) $(CLIENT_OBJ) $(CFLAGS) $(FTFLAGS) -o $(CLIENT) 

clean : 
	$(RM) $(CLIENT_OBJ)
	$(RM) $(SERVER_OBJ)
	make clean -C ./libft

fclean: clean
	$(RM) $(SERVER)
	$(RM) $(CLIENT)
	make fclean -C ./libft

norm:
	norminette $(SERVER_SRC) $(CLIENT_SRC)

re: fclean all

.PHONY: all clean fclean re