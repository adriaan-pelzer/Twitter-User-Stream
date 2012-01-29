MCFLAGS=`mysql_config --cflags`
CFLAGS=-Wall -I/usr/local/include ${MCFLAGS}
MLIBS=`mysql_config --libs`
LIBS=-L/usr/local/lib -lcurl -loauth -ljson ${MLIBS}

all: usbot

usbot: usbot.o curl.o json.o db.o
	gcc ${LIBS} -o usbot usbot.o curl.o json.o db.o
	
clean:
	rm *.o; rm -rf usbot; rm core*
