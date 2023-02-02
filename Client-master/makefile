LDFLAGS:=-lboost_system -pthread -lboost_thread
SRCS = $(wildcard ./src/*.cpp)
OBJS = $(patsubst ./src/%.cpp,./bin/%.o, $(SRCS))
DEPS := $(patsubst %.o,%.d, $(OBJS))
all: SPL3new

SPL3new: bin/bidiClient.o bin/bidiProtocol.o bin/connectionHandler.o bin/encoderDecoder.o bin/Task.o
		@echo 'Linking files'
		g++ -o bin/bidiClient bin/bidiClient.o bin/bidiProtocol.o bin/connectionHandler.o bin/encoderDecoder.o bin/Task.o $(LDFLAGS)

bin/bidiClient.o: src/bidiClient.cpp
		g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -Iboost_1_61_0 -o bin/bidiClient.o src/bidiClient.cpp

bin/bidiProtocol.o: src/bidiProtocol.cpp
		g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -Iboost_1_61_0 -o bin/bidiProtocol.o src/bidiProtocol.cpp

bin/connectionHandler.o: src/connectionHandler.cpp
		g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -Iboost_1_61_0 -o bin/connectionHandler.o src/connectionHandler.cpp

bin/encoderDecoder.o: src/encoderDecoder.cpp
		g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -Iboost_1_61_0 -o bin/encoderDecoder.o src/encoderDecoder.cpp

bin/Task.o: src/Task.cpp
		g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -Iboost_1_61_0 -o bin/Task.o src/Task.cpp

clean:
		@echo 'Cleaning'
		rm -f bin/*