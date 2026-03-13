#include "ValidadorLexico.hpp"
#include <cctype>

// Representamos el diagrama de transiciones como una tabla
// -1 indica una transición inválida (estado muerto)
// FILA = Estado actual | COLUMNAS = [DIGITO, PUNTO, EXP, SIGNO, OTRO]
const int TABLA_TRANSICIONES[7][VALIDADOR_LEXICO_HPP::TOTAL_TIPOS] = {
    /* 0 (Inicial) */     { 1,  2, -1, -1, -1 },
    /* 1 (Digito entero)*/{ 1,  3,  4, -1, -1 },  // Estado ACEPTACIÓN
    /* 2 (Punto) */       { 3, -1, -1, -1, -1 },
    /* 3 (Decimal) */     { 3, -1,  4, -1, -1 },  // Estado ACEPTACIÓN
    /* 4 (Exponente) */   { 6, -1, -1,  5, -1 },
    /* 5 (Signo exp) */   { 6, -1, -1, -1, -1 },
    /* 6 (Digito exp) */  { 6, -1, -1, -1, -1 }   // Estado ACEPTACIÓN
};

ValidadorLexico::TipoEntrada ValidadorLexico::categorizarCaracter(char c) const {
    if (isdigit(c)) return DIGITO;
    if (c == '.')   return PUNTO;
    if (c == 'e' || c == 'E') return EXPONENTE;
    if (c == '+' || c == '-') return SIGNO;
    return OTRO;
}

bool ValidadorLexico::esNumeroValido(const std::string& cadena) {
    // Caso especial: cadena vacía no es válida
    if (cadena.empty()) return false;
    
    int estadoActual = 0;  // Estado inicial
    
    for (char c : cadena) {
        TipoEntrada entrada = categorizarCaracter(c);
        
        // Si el caracter no es válido para el alfabeto, rechazar inmediatamente
        if (entrada == OTRO) return false;
        
        int siguienteEstado = TABLA_TRANSICIONES[estadoActual][entrada];
        
        // Si no hay transición definida, la cadena no es válida
        if (siguienteEstado == -1) return false;
        
        estadoActual = siguienteEstado;
    }
    
    // Al final de la cadena, verificamos si el estado actual es de aceptación
    // Estados de aceptación: 1 (enteros), 3 (decimales), 6 (notación científica)
    return (estadoActual == 1 || estadoActual == 3 || estadoActual == 6);
}