#include <cctype>
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

const int TAM = 4;

// 1. Inicializa la matriz con espacios vacios (Paso por valor de la matriz)
void inicializarTablero(char tablero[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tablero[i][j] = ' ';
        }
    }
}

// 2. Muestra el tablero 4x4 con los numeros del 1 al 16 o las fichas X / O
void mostrarTablero(char tablero[TAM][TAM]) {
    int numeroCasilla = 1;
    cout << "\n+----+----+----+----+\n";
    for (int i = 0; i < TAM; i++) {
        cout << "|";
        for (int j = 0; j < TAM; j++) {
            if (tablero[i][j] == ' ') {
                if (numeroCasilla < 10) {
                    cout << "  " << numeroCasilla << " |";
                } else {
                    cout << " " << numeroCasilla << " |";
                }
            } else {
                cout << "  " << tablero[i][j] << " |";
            }
            numeroCasilla++;
        }
        cout << "\n+----+----+----+----+\n";
    }
}

// 3. Configura las fichas del jugador y la computadora (Parametros por referencia)
void configurarFichas(char &fichaJugador, char &fichaCpu) {
    char eleccion;
    do {
        cout << "\nElija su ficha (X / O): ";
        cin >> eleccion;
        eleccion = toupper(eleccion);

        if (eleccion != 'X' && eleccion != 'O') {
            cout << "Error: Solo puede elegir la letra X o la letra O.\n";
        }
    } while (eleccion != 'X' && eleccion != 'O');

    fichaJugador = eleccion;
    fichaCpu = (fichaJugador == 'X') ? 'O' : 'X';

    cout << "Configuracion guardada -> Jugador: [" << fichaJugador
         << "] | Computadora: [" << fichaCpu << "]\n";
}

// 4. Convierte una posicion (1-16) en coordenadas de fila y columna (Parametros por referencia)
void convertirPosicion(int posicion, int &fila, int &columna) {
    fila = (posicion - 1) / TAM;
    columna = (posicion - 1) % TAM;
}

// 5. Verifica si la casilla elegida esta libre (Parametros por valor)
bool esCasillaValida(char tablero[TAM][TAM], int posicion) {
    if (posicion < 1 || posicion > 16) {
        return false;
    }
    int fila, columna;
    convertirPosicion(posicion, fila, columna);
    return (tablero[fila][columna] == ' ');
}

// 6. Verifica si una ficha logro 4 en raya horizontal o vertical (Parametros por valor)
bool verificarGanador(char tablero[TAM][TAM], char ficha) {
    // Verificar filas (horizontal)
    for (int i = 0; i < TAM; i++) {
        if (tablero[i][0] == ficha && tablero[i][1] == ficha &&
            tablero[i][2] == ficha && tablero[i][3] == ficha) {
            return true;
        }
    }

    // Verificar columnas (vertical)
    for (int j = 0; j < TAM; j++) {
        if (tablero[0][j] == ficha && tablero[1][j] == ficha &&
            tablero[2][j] == ficha && tablero[3][j] == ficha) {
            return true;
        }
    }

    return false;
}

// 7. Controla toda la partida entre el Jugador 1 y la Computadora
void jugarPartida(char fichaJugador, char fichaCpu) {
    char tablero[TAM][TAM];
    inicializarTablero(tablero);

    int movimientos = 0;
    const int MAX_MOVIMIENTOS = 16;
    bool hayGanador = false;

    cout << "\n=== INICIA EL JUEGO (Jugador: " << fichaJugador
         << " vs CPU: " << fichaCpu << ") ===\n";

    while (movimientos < MAX_MOVIMIENTOS && !hayGanador) {
        mostrarTablero(tablero);

        // --- TURNO DEL JUGADOR 1 ---
        int posJugador;
        do {
            cout << "Turno Jugador (" << fichaJugador << "). Elija una posicion (1 - 16): ";
            cin >> posJugador;
            if (!esCasillaValida(tablero, posJugador)) {
                cout << "Error: Posicion invalida o casilla ya ocupada. Intente de nuevo.\n";
            }
        } while (!esCasillaValida(tablero, posJugador));

        int fila, col;
        convertirPosicion(posJugador, fila, col);
        tablero[fila][col] = fichaJugador;
        movimientos++;

        if (verificarGanador(tablero, fichaJugador)) {
            mostrarTablero(tablero);
            cout << "\nFELICIDADES! El Jugador 1 (" << fichaJugador << ") ha ganado con 4 en raya!\n";
            hayGanador = true;
            break;
        }

        if (movimientos == MAX_MOVIMIENTOS) {
            break;
        }

        // --- TURNO DE LA COMPUTADORA ---
        int posCpu;
        do {
            posCpu = (rand() % 16) + 1;
        } while (!esCasillaValida(tablero, posCpu));

        convertirPosicion(posCpu, fila, col);
        tablero[fila][col] = fichaCpu;
        movimientos++;

        cout << "La computadora (" << fichaCpu << ") eligio la posicion: " << posCpu << "\n";

        if (verificarGanador(tablero, fichaCpu)) {
            mostrarTablero(tablero);
            cout << "\nFIN DEL JUEGO! La Computadora (" << fichaCpu << ") ha ganado con 4 en raya!\n";
            hayGanador = true;
            break;
        }
    }

    if (!hayGanador) {
        mostrarTablero(tablero);
        cout << "\nEMPATE! Se llenaron las 16 casillas sin que nadie hiciera 4 en linea.\n";
    }
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    char fichaJugador = 'X'; // Configuracion por defecto
    char fichaCpu = 'O';
    int opcion;

    do {
        cout << "\n====================================\n";
        cout << "      JUEGO 4 EN RAYA (4 x 4)       \n";
        cout << "====================================\n";
        cout << "Ficha actual -> Jugador: [" << fichaJugador << "] | CPU: [" << fichaCpu << "]\n";
        cout << "1. Configurar (Elegir X u O)\n";
        cout << "2. Jugar\n";
        cout << "3. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                configurarFichas(fichaJugador, fichaCpu);
                break;
            case 2:
                jugarPartida(fichaJugador, fichaCpu);
                break;
            case 3:
                cout << "Saliendo del programa. Hasta luego\n";
                break;
            default:
                cout << "Error: Opcion no valida. Elija entre 1 y 3.\n";
        }
    } while (opcion != 3);

    return 0;
}
