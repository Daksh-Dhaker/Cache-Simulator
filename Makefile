CC = gcc
CXXFLAGS = -Wall -Wextra --pedantic

SRCS = lru.cpp lru_cache.cpp fifo_cache.cpp main.cpp 
OBJS = $(SRCS:.cpp=.o)
EXEC = cacheSim

.PHONY: all clean

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CXXFLAGS) $(OBJS) -o $(EXEC) -lstdc++

%.o: %.cpp
	$(CC) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)

