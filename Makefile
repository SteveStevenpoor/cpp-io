BIN_NAME	= io_bin

SRCS		= main.cpp\
			  src/io.cpp\
			  src/io_test.cpp

HEADERS		= include/io.h

OBJ			= $(SRCS:.cpp=.o)

CC			= g++ -fsanitize=address

CFLAGS		= -Iinclude

LDFLAGS		= -fsanitize=address -lgtest -pthread

all: $(BIN_NAME) clean

clean:
	@rm -rf *.o src/*.o

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_NAME): $(OBJ)
	$(CC) $(LDFLAGS) $(OBJ) -o $@