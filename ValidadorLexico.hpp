#ifndef VALIDADOR_LEXICO_HPP
#define VALIDADOR_LEXICO_HPP

#include <string>
#include <vector>

class ValidadorLexico {
public:
    // Enumeración para categorizar caracteres de entrada
    enum TipoEntrada { DIGITO, PUNTO, EXPONENTE, SIGNO, OTRO, TOTAL_TIPOS };

    ValidadorLexico() = default;

    // Método principal de validación
    bool esNumeroValido(const std::string& cadena);

private:
    // Convierte un char a su categoría correspondiente
    TipoEntrada categorizarCaracter(char c) const;
};

#endif