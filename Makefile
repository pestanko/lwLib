CC=gcc
CFLAGS= -Werror -Wall -Wextra -std=c99 -pedantic
TARGET=test

OBJS=build/lwstring.o \
	 build/lwArray.o \
	 build/lwbase64.o \
	 build/lwcrypt.c\
	 build/config/iniparser.o\
	 build/config/config.o\
	 main.c


SRC= lwstring.c \
	 lwArray.c \
	 lwbase64.c\
	 lwcrypt.c \
	 config/iniparser.c\
	 config/config.c\
	 main.c



all: debug

debug: CFLAGS+= -g -DDEBUG
debug: build

release: CFLAGS+= -O2
release: build

build: test

$(OBJS): $(SRC)
	$(CC) $(CFLAGS) $? -o $@

test: $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)





clean:
	rm -rf *.o
	rm $(TARGET)
	
