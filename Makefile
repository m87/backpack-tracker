CC=g++
CFLAGS=-g
LFLAGS=`pkg-config --cflags --libs opencv`
SRC=$(wildcard ./src/*.cpp)
OBJS=$(patsubst %.cpp, %.o, $(SRC))
I=-I./src


tracker: $(OBJS)
		$(CC) $(CFLAGS)  $(I) $^ -o $@ $(LFLAGS)

$(OBJS): %.o: %.cpp
		$(CC)  $(CFLAGS) $(I) -c  $< -o $@ $(LFLAGS) 

clean:
		rm -f tracker $(OBJS) ./src/*.gch
