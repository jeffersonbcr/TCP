CXX = g++
CXXFLAGS = -Wall -std=c++11 -pthread -Iinclude -Iprivate
LDFLAGS =

SRCS = src/main.cpp src/client.cpp src/logger.cpp src/client_states.cpp
OBJS = $(patsubst src/%.cpp, build/%.o, $(SRCS))
TARGET = build/cliente_tcp

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

# Regra para compilar os arquivos .cpp em .o dentro de build/
build/%.o: src/%.cpp | build
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regra para criar o diretório build se ele não existir
build:
	mkdir -p build

clean:
	rm -rf build $(TARGET)
