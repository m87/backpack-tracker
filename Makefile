CXX=g++
CFLAGS=-g 
LFLAGS=`pkg-config --cflags --libs opencv`

SRC=$(wildcard ./src/*.cpp)
OBJS=$(patsubst %.cpp, %.o, $(SRC))
I=-I./src/


backpack: $(OBJS)
	$(CXX) $(CFLAGS) $(I) $^ -o $@ $(LFLAGS)

$(OBJS): %.o: %.cpp
	$(CXX) $(CFLAGS) $(I) -c $< -o $@ $(LFLAGS)

clean:
	rm -f src/*.o backpack
