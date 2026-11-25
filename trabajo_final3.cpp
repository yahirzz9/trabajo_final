#include <iostream>
#include <string>

using namespace std;

void mostrarInventario(string nombres[], int stock[], int total) {
    cout << "\n--- INVENTARIO DEL TALLER ---\n";
    for (int i = 0; i < total; i++) {
        cout << i + 1 << ". " << nombres[i] << ": " << stock[i] << " unidades";
        if (stock[i] < 5) {
            cout << " [ALERTA: STOCK BAJO]";
        }
        cout << "\n";
    }
}

int seleccionarComponente(string nombres[], int stock[], int total) {
    int indice;
    mostrarInventario(nombres, stock, total);
    do {
        cout << "Seleccione el numero del componente (1 - " << total << "): ";
        cin >> indice;
        if (indice < 1 || indice > total) {
            cout << "Error: Numero de componente no valido.\n";
        }
    } while (indice < 1 || indice > total);
    return indice - 1;
}

int pedirCantidadPositiva(string mensaje) {
    int cantidad;
    do {
        cout << mensaje;
        cin >> cantidad;
        if (cantidad <= 0) {
            cout << "Error: La cantidad debe ser mayor a cero.\n";
        }
    } while (cantidad <= 0);
    return cantidad;
}

int main() {
    const int TOTAL = 3;
    string nombres[TOTAL] = {"Servomotor", "Sensor Ultrasonico", "Placa Arduino"};
    int stock[TOTAL] = {12, 4, 8};
    int opcion;

    do {
        cout << "\n=== TALLER DE ROBOTICA ===\n";
        cout << "1. Ingresar unidades al stock\n";
        cout << "2. Retirar unidades para proyecto\n";
        cout << "3. Consultar inventario\n";
        cout << "4. Salir\n";
        cout << "Elija una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                int pos = seleccionarComponente(nombres, stock, TOTAL);
                int cant = pedirCantidadPositiva("Cantidad a ingresar: ");
                stock[pos] += cant;
                cout << "Stock actualizado correctamente.\n";
                break;
            }
            case 2: {
                int pos = seleccionarComponente(nombres, stock, TOTAL);
                int cant = pedirCantidadPositiva("Cantidad a retirar: ");
                if (cant > stock[pos]) {
                    cout << "Error: Stock insuficiente. Solo hay " << stock[pos] << " disponibles.\n";
                } else {
                    stock[pos] -= cant;
                    cout << "Retiro registrado con exito.\n";
                }
                break;
            }
            case 3:
                mostrarInventario(nombres, stock, TOTAL);
                break;
            case 4:
                cout << "Saliendo del sistema...\n";
                break;
            default:
                cout << "Error: Opcion no valida. Intente de nuevo.\n";
        }
    } while (opcion != 4);

    return 0;
}
