#MCFLAGS=`mysql_config --cflags`
CFLAGS=-Wall -std=c99 -g -DDEBUG -I/usr/local/include
#MLIBS=`mysql_config --libs`
LIBS=-L/usr/local/lib -lcurl -loauth -ljson

all: usbot

usbot: usbot.o curl.o json.o
	gcc ${LIBS} -o usbot usbot.o curl.o json.o
	
clean:
	rm *.o; rm -rf usbot; rm core*
