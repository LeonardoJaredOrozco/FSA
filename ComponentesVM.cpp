#include "ComponentesVM.hpp"
#include <iomanip>
#include <algorithm>

ProcesadorVirtual::ProcesadorVirtual(const std::vector<std::string>& programa) : memoria(programa) {
    inicializarInstructionSet();
}

void ProcesadorVirtual::inicializarInstructionSet() {
    // Definir el Instruction Set según especificaciones [cite: 57, 61, 68]
    instructionSet["START"] = {"START", {}, 0, "Inicio del programa"};
    instructionSet["STOP"] = {"STOP", {}, 0, "Fin del programa"};
    instructionSet["MOVE"] = {"MOVE", {"reg", "valor"}, 2, "Mover valores a un registro desde un direccionamiento"};
    instructionSet["ADD"] = {"ADD", {"reg1", "reg2"}, 2, "Sumar valores contenidos en registros"};
    instructionSet["SUB"] = {"SUB", {"reg1", "reg2"}, 2, "Restar valores contenidos en registros"};
    instructionSet["MULT"] = {"MULT", {"reg1", "reg2"}, 2, "Multiplicar valores contenidos en registros"};
    instructionSet["DIV"] = {"DIV", {"reg1", "reg2"}, 2, "Dividir valores contenidos en registros"};
    instructionSet["STO"] = {"STO", {"addr"}, 1, "Almacenar resultado en dirección de memoria"};
}

bool ProcesadorVirtual::esRegistroValido(const std::string& token) {
    // Validar nombres de registros [cite: 88]
    std::vector<std::string> registrosValidos = {"AL", "AH", "BL", "BH", "ACC", "PC", "MAR", "MBR"};
    return std::find(registrosValidos.begin(), registrosValidos.end(), token) != registrosValidos.end();
}

InstruccionDecodificada ProcesadorVirtual::decodificarInstruccion(const std::string& linea) {
    InstruccionDecodificada inst;
    std::istringstream iss(linea);
    std::string token;
    std::vector<std::string> tokens;
    
    // Separar por espacios [cite: 76]
    while (iss >> token) {
        tokens.push_back(token);
    }
    
    if (tokens.empty()) {
        inst.nombre = "INVALIDA";
        return inst;
    }
    
    std::string nombreInst = tokens[0];
    
    // Buscar en el instruction set
    auto it = instructionSet.find(nombreInst);
    if (it != instructionSet.end()) {
        inst = it->second;
        // Copiar argumentos (omitir el nombre de la instrucción)
        for (size_t i = 1; i < tokens.size(); i++) {
            inst.argumentos.push_back(tokens[i]);
        }
    } else {
        inst.nombre = "INVALIDA";
    }
    
    return inst;
}

void ProcesadorVirtual::mostrarEstado(std::string etapa) {
    std::cout << "\n========================================" << std::endl;
    std::cout << "--- ETAPA: " << etapa << " ---" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "PC: " << reg.PC << " | IR: " << reg.IR << std::endl;
    std::cout << "ACC: " << reg.ACC << " (int) | FLOAT_ACC: " << reg.FLOAT_ACC << " (float)" << std::endl;
    std::cout << "AL: " << reg.AL << " | AH: " << reg.AH << " | BL: " << reg.BL << " | BH: " << reg.BH << std::endl;
    std::cout << "MAR: " << reg.MAR << " | MBR: " << reg.MBR << std::endl;
}

int obtenerValorRegistro(Registros& reg, const std::string& nombreReg) {
    if (nombreReg == "AL") return reg.AL;
    if (nombreReg == "AH") return reg.AH;
    if (nombreReg == "BL") return reg.BL;
    if (nombreReg == "BH") return reg.BH;
    if (nombreReg == "ACC") return reg.ACC;
    if (nombreReg == "PC") return reg.PC;
    if (nombreReg == "MAR") return reg.MAR;
    if (nombreReg == "MBR") return reg.MBR;
    return 0;
}

void asignarValorRegistro(Registros& reg, const std::string& nombreReg, int valor) {
    if (nombreReg == "AL") reg.AL = valor;
    else if (nombreReg == "AH") reg.AH = valor;
    else if (nombreReg == "BL") reg.BL = valor;
    else if (nombreReg == "BH") reg.BH = valor;
    else if (nombreReg == "ACC") reg.ACC = valor;
    else if (nombreReg == "PC") reg.PC = valor;
    else if (nombreReg == "MAR") reg.MAR = valor;
    else if (nombreReg == "MBR") reg.MBR = valor;
}

void ProcesadorVirtual::ejecutarCicloCompleto() {
    std::cout << "\n*** INICIANDO CICLO MAQUINA ***" << std::endl;
    std::cout << "Programa cargado en memoria (" << memoria.size() << " instrucciones)" << std::endl;
    
    while (reg.PC < memoria.size()) {
        // 1. FETCH [cite: 84]
        reg.IR = memoria[reg.PC];
        reg.MAR = reg.PC;
        mostrarEstado("FETCH");
        
        // 2. DECODE (Usar analizador léxico para validar) [cite: 76, 85]
        InstruccionDecodificada inst = decodificarInstruccion(reg.IR);
        mostrarEstado("DECODE");
        
        // 3. EXECUTE [cite: 86]
        if (inst.nombre == "START") {
            std::cout << ">> Ejecutando: START - Inicio de programa" << std::endl;
        }
        else if (inst.nombre == "STOP") {
            std::cout << ">> Ejecutando: STOP - Fin de programa" << std::endl;
            mostrarEstado("EXECUTE");
            break;
        }
        else if (inst.nombre == "MOVE" && inst.argumentos.size() >= 2) {
            std::string registro = inst.argumentos[0];
            std::string valorStr = inst.argumentos[1];
            
            // USAR EL VALIDADOR LEXICO PARA VERIFICAR SI ES NÚMERO VÁLIDO
            if (validador.esNumeroValido(valorStr)) {
                // Convertir a número (manejar enteros y decimales)
                if (valorStr.find('.') != std::string::npos) {
                    // Es decimal
                    float valorFloat = std::stof(valorStr);
                    reg.FLOAT_ACC = valorFloat;
                    reg.MBR = static_cast<int>(valorFloat); // Truncar para MBR entero
                    std::cout << ">> MOVE " << registro << ", " << valorStr << " (decimal)" << std::endl;
                } else {
                    // Es entero
                    int valorInt = std::stoi(valorStr);
                    reg.MBR = valorInt;
                    reg.FLOAT_ACC = static_cast<float>(valorInt);
                    std::cout << ">> MOVE " << registro << ", " << valorStr << " (entero)" << std::endl;
                }
                
                // Asignar al registro correspondiente
                asignarValorRegistro(reg, registro, reg.MBR);
            } else {
                std::cout << ">> ERROR: El valor '" << valorStr << "' no es un número válido" << std::endl;
            }
        }
        else if (inst.nombre == "ADD" && inst.argumentos.size() >= 2) {
            std::string reg1 = inst.argumentos[0];
            std::string reg2 = inst.argumentos[1];
            int val1 = obtenerValorRegistro(reg, reg1);
            int val2 = obtenerValorRegistro(reg, reg2);
            reg.ACC = val1 + val2;
            reg.FLOAT_ACC = static_cast<float>(val1) + static_cast<float>(val2);
            std::cout << ">> ADD " << reg1 << ", " << reg2 << " = " << val1 << " + " << val2 << " = " << reg.ACC << std::endl;
        }
        else if (inst.nombre == "INVALIDA") {
            std::cout << ">> ERROR: Instrucción no válida: " << reg.IR << std::endl;
        }
        else {
            std::cout << ">> Instrucción no implementada: " << inst.nombre << std::endl;
        }
        
        reg.PC++;
        mostrarEstado("EXECUTE");
    }
    
    std::cout << "\n*** PROGRAMA FINALIZADO ***" << std::endl;
    std::cout << "Resultado final en ACC: " << reg.ACC << std::endl;
    std::cout << "Resultado final en FLOAT_ACC: " << reg.FLOAT_ACC << std::endl;
}