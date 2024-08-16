CXX = g++
CXXFLAGS = -Wall -std=c++11 -pthread -Iinclude -Iprivate
LDFLAGS =

SRCS = src/main.cpp src/server.cpp src/thread_handler.cpp src/logger.cpp src/server_states.cpp
OBJS = $(patsubst src/%.cpp, build/%.o, $(SRCS))
TARGET = build/servidor_multithread

all: $(TARGET)

# Regra para criar o diretório build se não existir
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

# Regra genérica para compilar os arquivos .cpp em .o dentro de build/
build/%.o: src/%.cpp | build
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regra para criar o diretório build se ele não existir
build:
	mkdir -p build

clean:
	rm -rf build $(TARGET)
