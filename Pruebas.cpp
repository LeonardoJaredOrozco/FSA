#include <iostream>
#include <iomanip>
#include <string>
#include "ValidadorLexico.hpp"

void probarCaso(ValidadorLexico& validador, const std::string& caso, bool esperado) {
    bool resultado = validador.esNumeroValido(caso);
    std::cout << "Entrada: " << std::setw(12) << std::left << ("\"" + caso + "\"")
              << " | Resultado: " << std::setw(8) << (resultado ? "VALIDO" : "INVALIDO")
              << " | Esperado: " << (esperado ? "VALIDO" : "INVALIDO")
              << " | " << (resultado == esperado ? "CORRECTO" : "INCORRECTO")
              << std::endl;
}

int main() {
    ValidadorLexico validador;
    
    std::cout << "================================================" << std::endl;
    std::cout << "   VALIDADOR DE NUMEROS REALES (AUTOMATA FSA)   " << std::endl;
    std::cout << "================================================" << std::endl;
    std::cout << std::endl;
    
    // Casos de prueba con resultados esperados
    std::vector<std::pair<std::string, bool>> casos = {
        // Números válidos (deberían ser aceptados)
        {"123", true},           // Entero
        {"0", true},             // Cero
        {"45.67", true},         // Decimal
        {"0.99", true},          // Decimal con cero
        {".5", true},            // Decimal sin parte entera
        {"1.2E+10", true},       // Notación científica con signo +
        {"5e-3", true},          // Notación científica con signo -
        {"3E5", true},           // Notación científica sin signo
        {"123.456e-7", true},    // Combinación completa
        
        // Números inválidos (deberían ser rechazados)
        {"", false},             // Cadena vacía
        {"abc", false},          // Letras sin números
        {"1.2.3", false},        // Múltiples puntos
        {"45.", false},          // Punto sin decimales
        {".", false},            // Solo punto
        {"E10", false},          // Exponente sin parte entera/decimal
        {"1e", false},           // Exponente sin valor
        {"1e+", false},          // Exponente con signo sin número
        {"+123", false},         // Signo al inicio sin número antes
        {"-456", false},         // Signo negativo al inicio
        {"1.2E", false},         // Exponente vacío
        {" ", false}             // Solo espacio
    };
    
    std::cout << "--- PRUEBAS DE VALIDACION ---" << std::endl;
    std::cout << std::endl;
    
    for (const auto& caso : casos) {
        probarCaso(validador, caso.first, caso.second);
    }
    
    std::cout << std::endl;
    std::cout << "================================================" << std::endl;
    
    return 0;
}