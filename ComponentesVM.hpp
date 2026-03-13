#ifndef COMPONENTES_VM_HPP
#define COMPONENTES_VM_HPP

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <sstream>
#include <cctype>
#include "ValidadorLexico.hpp"  // Incluir el validador léxico

// Registros solicitados en la presentación [cite: 88]
struct Registros {
    int PC = 0, ACC = 0, MAR = 0, MBR = 0;
    int AL = 0, AH = 0, BL = 0, BH = 0;
    std::string IR = "";
    float FLOAT_ACC = 0.0;  // Añadido para manejar números decimales
};

// Estructura para instrucción decodificada
struct InstruccionDecodificada {
    std::string nombre;
    std::vector<std::string> argumentos;
    int longitud;
    std::string interpretacion;
};

class ProcesadorVirtual {
private:
    Registros reg;
    std::vector<std::string> memoria;
    ValidadorLexico validador;  // Usar el validador léxico correcto
    std::map<std::string, InstruccionDecodificada> instructionSet;
    
    // Métodos auxiliares
    InstruccionDecodificada decodificarInstruccion(const std::string& linea);
    bool esRegistroValido(const std::string& token);
    void inicializarInstructionSet();

public:
    ProcesadorVirtual(const std::vector<std::string>& programa);
    void ejecutarCicloCompleto(); // Ciclo Máquina: Fetch, Decode, Execute 
    void mostrarEstado(std::string etapa);
};

#endif