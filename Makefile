CXX      = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic -g -Iinclude
SRC      = src/Sensor.cpp src/SensorTemperatura.cpp src/SensorPresion.cpp \
           src/SensorCaudal.cpp src/ServidorSockets.cpp src/main.cpp

all: smti cliente

smti: $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o smti

cliente: pruebas/cliente.cpp
	$(CXX) $(CXXFLAGS) pruebas/cliente.cpp -o cliente

clean:
	rm -f smti cliente
