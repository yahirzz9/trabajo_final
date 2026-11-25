#include <iostream>
#include <string>

using namespace std;

string pedirCodigoNave() {
    string codigo;
    do {
        cout << "Ingrese el codigo de la nave (6 caracteres, Ej. ARC402): ";
        cin >> codigo;
        if (codigo.length() != 6) {
            cout << "Error: El codigo debe tener exactamente 6 caracteres.\n";
        }
    } while (codigo.length() != 6);
    return codigo;
}

double pedirCombustible() {
    double combustible;
    do {
        cout << "Ingrese nivel de combustible (0 - 100 %): ";
        cin >> combustible;
        if (combustible < 0 || combustible > 100) {
            cout << "Error: El combustible debe estar entre 0 y 100.\n";
        }
    } while (combustible < 0 || combustible > 100);
    return combustible;
}

double pedirVelocidad() {
    double velocidad;
    do {
        cout << "Ingrese velocidad de aproximacion (km/h): ";
        cin >> velocidad;
        if (velocidad <= 0) {
            cout << "Error: La velocidad debe ser mayor a 0.\n";
        }
    } while (velocidad <= 0);
    return velocidad;
}

void mostrarAutorizacion(string codigo, double combustible, double velocidad) {
    cout << "\n--- REPORTE NAVE " << codigo << " ---\n";
    if (combustible < 15.0) {
        cout << "EMERGENCIA PRIORITARIA: Aterrizaje inmediato en Pista 1.\n";
    } else if (velocidad <= 250.0) {
        cout << "AUTORIZADO: Proceda a aterrizaje estandar en Pista 2.\n";
    } else {
        cout << "ALERTA: Velocidad excesiva. Aborte descenso y entre en orbita.\n";
    }
}

int main() {
    cout << "=== SISTEMA DE CONTROL DE ATERRIZAJE ORBITAL ===\n";
    string codigo = pedirCodigoNave();
    double combustible = pedirCombustible();
    double velocidad = pedirVelocidad();

    mostrarAutorizacion(codigo, combustible, velocidad);
    return 0;
}
