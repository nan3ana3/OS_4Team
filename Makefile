CC = gcc
RM = rm -rf
TARGET = OSLINUX
CFLAG = -fcommon -w
SRC_DIR = source
INCS = include

SRCS = directory.c utility.c main.c permission.c stack.c user.c mkdir.c ls.c cd.c find.c pwd.c cat.c kill.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAG) -o $@ $^ -o $@ -I$(INCS) -lpthread

%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAG) -c $< -o $@ -I$(INCS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(TARGET)

re: fclean
	make all

.PHONY: all clean fclean re