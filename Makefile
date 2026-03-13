CXX = g++
CXXFLAGS = -std=c++11 -Wall

TARGET = vm
OBJS = SistemaPrincipal.o ComponentesVM.o ValidadorLexico.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

SistemaPrincipal.o: SistemaPrincipal.cpp ComponentesVM.hpp ValidadorLexico.hpp
	$(CXX) $(CXXFLAGS) -c SistemaPrincipal.cpp

ComponentesVM.o: ComponentesVM.cpp ComponentesVM.hpp ValidadorLexico.hpp
	$(CXX) $(CXXFLAGS) -c ComponentesVM.cpp

ValidadorLexico.o: ValidadorLexico.cpp ValidadorLexico.hpp
	$(CXX) $(CXXFLAGS) -c ValidadorLexico.cpp

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)