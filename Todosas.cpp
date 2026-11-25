/*Partiendo de este codigo completelo para crear un minijuegocon un personaje que puede ser un caracter de su eleccion
que se mueva dentro del marco entregado y que si choca con los bordes u obstaculos se muestre en pantalla perdiste.
O del contrario si llegue a la meta ganaste, la meta debe estar randomizada, es decir en cada intento debe estar en una posicion
diferente y debe haber como minimo 3 obstaculos*/
#include <conio.h>
#include <windows.h>
#include <iostream>
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <cstdio>

using namespace std;

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = static_cast<SHORT>(x);
    coord.Y = static_cast<SHORT>(y);
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<WORD>(color));
}

void ocultarCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

bool esPared(int px, int py, const int paredX[], const int paredY[], int numParedes) {
    for (int i = 0; i < numParedes; i++) {
        if (px == paredX[i] && py == paredY[i]) {
            return true;
        }
    }
    return false;
}

void dibujarCuadroMarco(int ancho, int alto, int colorBorde) {
    setColor(colorBorde);
    for (int i = 0; i < ancho; i++) {
        gotoxy(i, 0);
        cout << " ";
        gotoxy(i, alto - 1);
        cout << " ";
    }
    for (int i = 1; i < alto - 1; i++) {
        gotoxy(0, i);
        cout << " ";
        gotoxy(ancho - 1, i);
        cout << " ";
    }
    setColor(7);
}

int mostrarMenuPrincipal() {
    const int numOpciones = 3;
    const char* opciones[numOpciones] = {
        "1. Jugar (2 Jugadores - 5 Niveles)",
        "2. Instrucciones",
        "3. Salir"
    };
    int seleccion = 0;

    while (true) {
        system("cls");
        dibujarCuadroMarco(50, 18, BACKGROUND_BLUE | BACKGROUND_INTENSITY);

        setColor(11);
        gotoxy(14, 3);
        cout << "=== LABERINTO DUO ===";

        for (int i = 0; i < numOpciones; i++) {
            gotoxy(8, 6 + i * 2);
            if (i == seleccion) {
                setColor(BACKGROUND_BLUE | BACKGROUND_GREEN | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                cout << " > " << opciones[i] << " ";
            } else {
                setColor(7);
                cout << "   " << opciones[i] << " ";
            }
        }

        setColor(8);
        gotoxy(5, 14);
        cout << "Usa Flechas Arriba/Abajo y ENTER (o 1-3)";
        setColor(7);

        int tecla = _getch();
        if (tecla == 0 || tecla == 224) {
            tecla = _getch();
            if (tecla == 72) {
                seleccion = (seleccion - 1 + numOpciones) % numOpciones;
            } else if (tecla == 80) {
                seleccion = (seleccion + 1) % numOpciones;
            }
        } else if (tecla == 13) {
            return seleccion + 1;
        } else if (tecla >= '1' && tecla <= '3') {
            return tecla - '0';
        }
    }
}

void mostrarInstrucciones() {
    system("cls");
    dibujarCuadroMarco(56, 20, BACKGROUND_BLUE | BACKGROUND_INTENSITY);

    setColor(14);
    gotoxy(18, 2);
    cout << "=== INSTRUCCIONES ===";

    setColor(10);
    gotoxy(4, 5);
    cout << "Jugador 1 (@): ";
    setColor(7);
    cout << "Se mueve con W, A, S, D";

    setColor(11);
    gotoxy(4, 7);
    cout << "Jugador 2 (&): ";
    setColor(7);
    cout << "Se mueve con las Flechas";

    setColor(14);
    gotoxy(4, 9);
    cout << "Meta ($):      ";
    setColor(7);
    cout << "Cualquiera que llegue pasa de nivel";

    setColor(12);
    gotoxy(4, 11);
    cout << "Enemigos (X):  ";
    setColor(7);
    cout << "Se mueven y aumentan en cada nivel";

    setColor(BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
    gotoxy(4, 13);
    cout << " ";
    setColor(7);
    cout << " Laberinto:   Barreras fijas mortales al tocarlas";

    setColor(8);
    gotoxy(8, 17);
    cout << "Presiona cualquier tecla para volver...";
    setColor(7);
    _getch();
}

int mostrarMenuFinPartida(const char* titulo, int colorTitulo, const char* detalle) {
    const int numOpciones = 3;
    const char* opciones[numOpciones] = {
        "1. Volver a jugar",
        "2. Menu principal",
        "3. Salir"
    };
    int seleccion = 0;

    while (true) {
        system("cls");
        dibujarCuadroMarco(52, 18, BACKGROUND_BLUE | BACKGROUND_INTENSITY);

        setColor(colorTitulo);
        gotoxy(12, 3);
        cout << titulo;

        setColor(7);
        gotoxy(6, 5);
        cout << detalle;

        for (int i = 0; i < numOpciones; i++) {
            gotoxy(14, 8 + i * 2);
            if (i == seleccion) {
                setColor(BACKGROUND_BLUE | BACKGROUND_GREEN | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                cout << " > " << opciones[i] << " ";
            } else {
                setColor(7);
                cout << "   " << opciones[i] << " ";
            }
        }

        setColor(8);
        gotoxy(6, 15);
        cout << "Usa Flechas Arriba/Abajo y ENTER (o 1-3)";
        setColor(7);

        int tecla = _getch();
        if (tecla == 0 || tecla == 224) {
            tecla = _getch();
            if (tecla == 72) {
                seleccion = (seleccion - 1 + numOpciones) % numOpciones;
            } else if (tecla == 80) {
                seleccion = (seleccion + 1) % numOpciones;
            }
        } else if (tecla == 13) {
            return seleccion + 1;
        } else if (tecla >= '1' && tecla <= '3') {
            return tecla - '0';
        }
    }
}

int main() {
    const int Ancho = 50, Alto = 25;
    const int Esc = 27;
    const int TOTAL_NIVELES = 5;
    const int OBSTACULOS_INICIALES = 3;
    const int MAX_OBSTACULOS = OBSTACULOS_INICIALES + TOTAL_NIVELES - 1; // 7
    const int MAX_PAREDES = 140;

    const char jugador1Char = '@';
    const char jugador2Char = '&';
    const char metaChar = '$';
    const char obstaculoChar = 'X';

    const int COLOR_NORMAL = 7;
    const int COLOR_BORDE_AZUL = BACKGROUND_BLUE | BACKGROUND_INTENSITY;
    const int COLOR_PARED_CUADRO = BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_INTENSITY;
    const int COLOR_JUGADOR1 = 10; // Verde
    const int COLOR_JUGADOR2 = 11; // Cian
    const int COLOR_OBSTACULO = 12; // Rojo
    const int COLOR_META = 14;      // Amarillo

    srand(static_cast<unsigned int>(time(0)));
    ocultarCursor();

    bool ejecutandoPrograma = true;

    while (ejecutandoPrograma) {
        int opcionMenu = mostrarMenuPrincipal();

        if (opcionMenu == 2) {
            mostrarInstrucciones();
            continue;
        } else if (opcionMenu == 3) {
            break;
        }

        bool volverAJugar = true;

        while (volverAJugar) {
            int nivel = 1;
            bool ganoTodosLosNiveles = true;
            bool salioConEsc = false;
            int nivelFallo = 1;

            while (nivel <= TOTAL_NIVELES) {
                system("cls");
                setColor(COLOR_NORMAL);

                int numObstaculos = OBSTACULOS_INICIALES + (nivel - 1);
                int numSegmentos = 4 + (nivel * 2); // Barreras tipo laberinto que crecen por nivel

                int x1 = (Ancho / 2) - 3, y1 = Alto / 2;
                int x2 = (Ancho / 2) + 3, y2 = Alto / 2;

                int tecla = 0;
                bool nivelTerminado = false;
                bool ganoNivel = false;

                // Meta aleatoria
                int metaX, metaY;
                do {
                    metaX = 2 + rand() % (Ancho - 4);
                    metaY = 2 + rand() % (Alto - 4);
                } while ((abs(metaX - x1) <= 2 && abs(metaY - y1) <= 2) ||
                         (abs(metaX - x2) <= 2 && abs(metaY - y2) <= 2));

                // Generar barreras tipo laberinto (segmentos horizontales y verticales)
                int paredX[MAX_PAREDES], paredY[MAX_PAREDES];
                int numParedes = 0;

                for (int s = 0; s < numSegmentos; s++) {
                    bool horizontal = (rand() % 2 == 0);
                    int longitud = 3 + rand() % 5; // Tramos de 3 a 7 cuadros
                    int baseX = 2 + rand() % (Ancho - 4);
                    int baseY = 2 + rand() % (Alto - 4);

                    for (int step = 0; step < longitud && numParedes < MAX_PAREDES; step++) {
                        int cx = horizontal ? (baseX + step) : baseX;
                        int cy = horizontal ? baseY : (baseY + step);

                        if (cx <= 1 || cx >= Ancho - 2 || cy <= 1 || cy >= Alto - 2) {
                            break;
                        }

                        // Proteger zonas de inicio de ambos jugadores y de la meta
                        bool cercaInicio1 = (abs(cx - x1) <= 2 && abs(cy - y1) <= 2);
                        bool cercaInicio2 = (abs(cx - x2) <= 2 && abs(cy - y2) <= 2);
                        bool cercaMeta = (abs(cx - metaX) <= 1 && abs(cy - metaY) <= 1);

                        if (!cercaInicio1 && !cercaInicio2 && !cercaMeta &&
                            !esPared(cx, cy, paredX, paredY, numParedes)) {
                            paredX[numParedes] = cx;
                            paredY[numParedes] = cy;
                            numParedes++;
                        }
                    }
                }

                // Obstaculos moviles
                int obsX[MAX_OBSTACULOS], obsY[MAX_OBSTACULOS];
                int obsDx[MAX_OBSTACULOS], obsDy[MAX_OBSTACULOS];

                for (int k = 0; k < numObstaculos; k++) {
                    bool valido;
                    do {
                        valido = true;
                        obsX[k] = 1 + rand() % (Ancho - 2);
                        obsY[k] = 1 + rand() % (Alto - 2);

                        if ((abs(obsX[k] - x1) <= 2 && abs(obsY[k] - y1) <= 2) ||
                            (abs(obsX[k] - x2) <= 2 && abs(obsY[k] - y2) <= 2) ||
                            (obsX[k] == metaX && obsY[k] == metaY) ||
                            esPared(obsX[k], obsY[k], paredX, paredY, numParedes)) {
                            valido = false;
                        }
                        for (int prev = 0; prev < k; prev++) {
                            if (obsX[k] == obsX[prev] && obsY[k] == obsY[prev]) {
                                valido = false;
                            }
                        }
                    } while (!valido);

                    do {
                        obsDx[k] = (rand() % 3) - 1;
                        obsDy[k] = (rand() % 3) - 1;
                    } while (obsDx[k] == 0 && obsDy[k] == 0);
                }

                // Dibujar borde azul como cuadros solidos
                dibujarCuadroMarco(Ancho, Alto, COLOR_BORDE_AZUL);

                // Dibujar barreras de laberinto como cuadros solidos
                setColor(COLOR_PARED_CUADRO);
                for (int p = 0; p < numParedes; p++) {
                    gotoxy(paredX[p], paredY[p]);
                    cout << " ";
                }

                // Dibujar meta
                setColor(COLOR_META);
                gotoxy(metaX, metaY);
                cout << metaChar;

                // Dibujar enemigos moviles
                setColor(COLOR_OBSTACULO);
                for (int k = 0; k < numObstaculos; k++) {
                    gotoxy(obsX[k], obsY[k]);
                    cout << obstaculoChar;
                }

                // Dibujar Jugador 1 y Jugador 2
                setColor(COLOR_JUGADOR1);
                gotoxy(x1, y1);
                cout << jugador1Char;

                setColor(COLOR_JUGADOR2);
                gotoxy(x2, y2);
                cout << jugador2Char;

                // Informacion inferior
                setColor(COLOR_NORMAL);
                gotoxy(0, Alto + 1);
                cout << "Nivel: " << nivel << "/" << TOTAL_NIVELES
                     << " | Moviles: " << numObstaculos
                     << " | Barreras: " << numSegmentos
                     << " | Meta: " << metaChar;
                gotoxy(0, Alto + 2);
                cout << "J1 (" << jugador1Char << "): WASD | J2 (" << jugador2Char << "): Flechas | Menu/Salir: ESC";

                int ticksObstaculos = 0;

                while (!nivelTerminado) {
                    if (_kbhit()) {
                        tecla = _getch();

                        int jugadorActivo = 0;
                        int nx = 0, ny = 0;

                        if (tecla == 0 || tecla == 224) {
                            tecla = _getch();
                            jugadorActivo = 2;
                            nx = x2;
                            ny = y2;
                            if (tecla == 72) ny--;
                            else if (tecla == 80) ny++;
                            else if (tecla == 75) nx--;
                            else if (tecla == 77) nx++;
                            else jugadorActivo = 0;
                        } else if (tecla == Esc) {
                            nivelTerminado = true;
                            salioConEsc = true;
                            break;
                        } else {
                            char c = static_cast<char>(tolower(tecla));
                            if (c == 'w' || c == 's' || c == 'a' || c == 'd') {
                                jugadorActivo = 1;
                                nx = x1;
                                ny = y1;
                                if (c == 'w') ny--;
                                else if (c == 's') ny++;
                                else if (c == 'a') nx--;
                                else if (c == 'd') nx++;
                            }
                        }

                        if (jugadorActivo != 0) {
                            // Colision con bordes
                            if (nx <= 0 || nx >= Ancho - 1 || ny <= 0 || ny >= Alto - 1) {
                                nivelTerminado = true;
                                ganoNivel = false;
                                break;
                            }

                            // Colision con barreras del laberinto
                            if (esPared(nx, ny, paredX, paredY, numParedes)) {
                                nivelTerminado = true;
                                ganoNivel = false;
                                break;
                            }

                            // Colision con enemigos moviles
                            for (int k = 0; k < numObstaculos; k++) {
                                if (nx == obsX[k] && ny == obsY[k]) {
                                    nivelTerminado = true;
                                    ganoNivel = false;
                                    break;
                                }
                            }
                            if (nivelTerminado) break;

                            if (jugadorActivo == 1) {
                                if (!(nx == x2 && ny == y2)) {
                                    gotoxy(x1, y1);
                                    cout << " ";
                                    x1 = nx;
                                    y1 = ny;
                                    setColor(COLOR_JUGADOR1);
                                    gotoxy(x1, y1);
                                    cout << jugador1Char;
                                }
                            } else {
                                if (!(nx == x1 && ny == y1)) {
                                    gotoxy(x2, y2);
                                    cout << " ";
                                    x2 = nx;
                                    y2 = ny;
                                    setColor(COLOR_JUGADOR2);
                                    gotoxy(x2, y2);
                                    cout << jugador2Char;
                                }
                            }
                            setColor(COLOR_NORMAL);

                            if ((x1 == metaX && y1 == metaY) || (x2 == metaX && y2 == metaY)) {
                                nivelTerminado = true;
                                ganoNivel = true;
                                break;
                            }
                        }
                    }

                    // Movimiento de obstaculos
                    ticksObstaculos++;
                    if (ticksObstaculos >= 7) {
                        ticksObstaculos = 0;

                        for (int k = 0; k < numObstaculos; k++) {
                            int nextObsX = obsX[k] + obsDx[k];
                            int nextObsY = obsY[k] + obsDy[k];

                            if (nextObsX <= 1 || nextObsX >= Ancho - 2) {
                                obsDx[k] = -obsDx[k];
                                nextObsX = obsX[k] + obsDx[k];
                            }
                            if (nextObsY <= 1 || nextObsY >= Alto - 2) {
                                obsDy[k] = -obsDy[k];
                                nextObsY = obsY[k] + obsDy[k];
                            }

                            if (esPared(nextObsX, nextObsY, paredX, paredY, numParedes) ||
                                (nextObsX == metaX && nextObsY == metaY)) {
                                obsDx[k] = -obsDx[k];
                                obsDy[k] = -obsDy[k];
                                nextObsX = obsX[k] + obsDx[k];
                                nextObsY = obsY[k] + obsDy[k];

                                if (nextObsX <= 0 || nextObsX >= Ancho - 1 ||
                                    nextObsY <= 0 || nextObsY >= Alto - 1 ||
                                    esPared(nextObsX, nextObsY, paredX, paredY, numParedes) ||
                                    (nextObsX == metaX && nextObsY == metaY)) {
                                    nextObsX = obsX[k];
                                    nextObsY = obsY[k];
                                }
                            }

                            if (nextObsX != obsX[k] || nextObsY != obsY[k]) {
                                gotoxy(obsX[k], obsY[k]);
                                cout << " ";

                                obsX[k] = nextObsX;
                                obsY[k] = nextObsY;

                                setColor(COLOR_OBSTACULO);
                                gotoxy(obsX[k], obsY[k]);
                                cout << obstaculoChar;
                                setColor(COLOR_NORMAL);
                            }

                            if ((obsX[k] == x1 && obsY[k] == y1) ||
                                (obsX[k] == x2 && obsY[k] == y2)) {
                                nivelTerminado = true;
                                ganoNivel = false;
                                break;
                            }
                        }
                    }

                    Sleep(25);
                }

                if (salioConEsc) {
                    ganoTodosLosNiveles = false;
                    nivelFallo = nivel;
                    break;
                } else if (ganoNivel) {
                    if (nivel < TOTAL_NIVELES) {
                        setColor(10);
                        gotoxy(0, Alto + 4);
                        cout << "NIVEL " << nivel << " SUPERADO! Cargando nivel " << (nivel + 1) << "...";
                        setColor(COLOR_NORMAL);
                        Sleep(1200);
                        nivel++;
                    } else {
                        break;
                    }
                } else {
                    ganoTodosLosNiveles = false;
                    nivelFallo = nivel;
                    break;
                }
            }

            int opcionFin = 0;
            if (salioConEsc) {
                opcionFin = mostrarMenuFinPartida("=== PARTIDA PAUSADA / SALIDA ===", 14, "Saliste de la partida actual.");
            } else if (ganoTodosLosNiveles) {
                opcionFin = mostrarMenuFinPartida("=== FELICIDADES, GANARON! ===", 10, "Completaron los 5 niveles con exito.");
            } else {
                char mensajeDetalle[60];
                sprintf(mensajeDetalle, "Perdieron en el nivel %d al chocar.", nivelFallo);
                opcionFin = mostrarMenuFinPartida("=== GAME OVER - PERDIERON ===", 12, mensajeDetalle);
            }

            if (opcionFin == 1) {
                volverAJugar = true;
            } else if (opcionFin == 2) {
                volverAJugar = false;
            } else {
                volverAJugar = false;
                ejecutandoPrograma = false;
            }
        }
    }

    system("cls");
    setColor(COLOR_NORMAL);
    cout << "Gracias por jugar!" << endl;
    return 0;
}
