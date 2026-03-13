#include "ComponentesVM.hpp"
#include <iostream>

int main() {
    std::cout << "================================================" << std::endl;
    std::cout << "   MAQUINA VIRTUAL CON ANALIZADOR LEXICO        " << std::endl;
    std::cout << "================================================" << std::endl;
    std::cout << std::endl;
    
    // Definición de un programa basado en los requisitos [cite: 57, 61, 68]
    std::vector<std::string> programa = {
        "START",
        "MOVE AL 100",     // Mover 100 a AL (entero)
        "MOVE BL 3.14",    // Mover 3.14 a BL (decimal validado por el autómata)
        "ADD AL BL",       // Sumar AL + BL
        "STO 1000",        // Almacenar resultado en dirección 1000
        "STOP"
    };

    std::cout << "Cargando programa en la memoria de la VM..." << std::endl;
    std::cout << "Programa a ejecutar:" << std::endl;
    for (size_t i = 0; i < programa.size(); i++) {
        std::cout << "  [" << i << "] " << programa[i] << std::endl;
    }
    std::cout << std::endl;
    
    ProcesadorVirtual vm(programa);
    vm.ejecutarCicloCompleto();

    std::cout << "\n================================================" << std::endl;
    std::cout << "   PRUEBA ADICIONAL: VALIDADOR LEXICO SOLO      " << std::endl;
    std::cout << "================================================" << std::endl;
    
    // Demostrar que el validador funciona independientemente
    ValidadorLexico val;
    std::vector<std::string> pruebas = {"123", "45.67", "1.2E+10", "abc", "1.2.3"};
    
    for (const auto& p : pruebas) {
        std::cout << "¿'" << p << "' es número válido? " 
                  << (val.esNumeroValido(p) ? "SI" : "NO") << std::endl;
    }
    
    return 0;
}