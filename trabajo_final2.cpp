#include <iomanip>
#include <iostream>

using namespace std;

double leerPhDia(int dia) {
    double ph;
    do {
        cout << "Ingrese el pH del Dia " << dia << " (0.0 - 14.0): ";
        cin >> ph;
        if (ph < 0.0 || ph > 14.0) {
            cout << "Error: El pH debe estar entre 0.0 y 14.0.\n";
        }
    } while (ph < 0.0 || ph > 14.0);
    return ph;
}

int main() {
    const int DIAS = 7;
    double lecturas[DIAS];
    double suma = 0.0;
    int fueraDeRango = 0;

    cout << "=== MONITOR DE PH HIDROPONICO SEMANAL ===\n";

    // Registro de datos en el arreglo
    for (int i = 0; i < DIAS; i++) {
        lecturas[i] = leerPhDia(i + 1);
        suma += lecturas[i];
    }

    // Procesamiento de resultados
    double phMenor = lecturas[0];
    int diaMasAcido = 1;

    for (int i = 0; i < DIAS; i++) {
        if (lecturas[i] < 5.5 || lecturas[i] > 6.5) {
            fueraDeRango++;
        }
        if (lecturas[i] < phMenor) {
            phMenor = lecturas[i];
            diaMasAcido = i + 1;
        }
    }

    double promedio = suma / DIAS;

    cout << fixed << setprecision(2);
    cout << "\n--- RESUMEN SEMANAL ---\n";
    cout << "Promedio de pH: " << promedio << "\n";
    cout << "Dias fuera de rango optimo (5.5 - 6.5): " << fueraDeRango << " dia(s)\n";
    cout << "Mayor acidez registrada: " << phMenor << " (Dia " << diaMasAcido << ")\n";

    return 0;
}
