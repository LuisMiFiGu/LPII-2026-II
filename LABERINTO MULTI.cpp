#include <conio.h>
#include <windows.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <cstdio>

using namespace std;

enum TipoEvento {
    EVENTO_NINGUNO = 0,
    EVENTO_SIN_PAREDES,
    EVENTO_COLORES_INVERTIDOS,
    EVENTO_CONTROLES_INVERTIDOS
};

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

// Evalua probabilidades independientes:
// 1) Sin paredes: 1/12
// 2) Colores invertidos: 1/8
// 3) Controles invertidos: 1/8
TipoEvento sortearEventoNivel() {
    if ((rand() % 12) == 0) {
        return EVENTO_SIN_PAREDES;
    }
    if ((rand() % 8) == 0) {
        return EVENTO_COLORES_INVERTIDOS;
    }
    if ((rand() % 8) == 0) {
        return EVENTO_CONTROLES_INVERTIDOS;
    }
    return EVENTO_NINGUNO;
}

const char* nombreEvento(TipoEvento evento) {
    switch (evento) {
        case EVENTO_SIN_PAREDES:
            return "SIN PAREDES (Prob. 1/12) - Campo libre de barreras";
        case EVENTO_COLORES_INVERTIDOS:
            return "COLORES INVERTIDOS (Prob. 1/8) - Colores intercambiados";
        case EVENTO_CONTROLES_INVERTIDOS:
            return "CONTROLES INVERTIDOS (Prob. 1/8) - Arriba/Abajo e Izq/Der invertidos";
        default:
            return "Ninguno (Nivel normal)";
    }
}

int mostrarMenuPrincipal(char j1Char, char j2Char, int colorJ1, int colorJ2) {
    const int numOpciones = 6;
    const char* opciones[numOpciones] = {
        "1. Modo 1 Jugador (5 Niveles)",
        "2. Modo 2 Jugadores (5 Niveles)",
        "3. Modo Sin Fin (Hasta 12 Enemigos)",
        "4. Elegir personaje",
        "5. Instrucciones",
        "6. Salir"
    };
    int seleccion = 0;

    while (true) {
        system("cls");
        dibujarCuadroMarco(58, 23, BACKGROUND_BLUE | BACKGROUND_INTENSITY);

        setColor(11);
        gotoxy(18, 3);
        cout << "=== LABERINTO DUO ===";

        gotoxy(11, 4);
        setColor(7);
        cout << "Actuales -> ";
        setColor(colorJ1);
        cout << "J1: [" << j1Char << "] ";
        setColor(7);
        cout << " | ";
        setColor(colorJ2);
        cout << "J2: [" << j2Char << "]";
        setColor(7);

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
        gotoxy(7, 19);
        cout << "Usa Flechas Arriba/Abajo y ENTER (o 1-6)";
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
        } else if (tecla >= '1' && tecla <= '6') {
            return tecla - '0';
        }
    }
}

int elegirJugadoresParaSinFin() {
    const int numOpciones = 2;
    const char* opciones[numOpciones] = {
        "1. Sin Fin - 1 Jugador",
        "2. Sin Fin - 2 Jugadores"
    };
    int seleccion = 0;

    while (true) {
        system("cls");
        dibujarCuadroMarco(52, 16, BACKGROUND_BLUE | BACKGROUND_INTENSITY);

        setColor(11);
        gotoxy(13, 3);
        cout << "=== MODO SIN FIN ===";

        setColor(14);
        gotoxy(8, 5);
        cout << "Enemigos suben hasta un maximo de 12.";

        for (int i = 0; i < numOpciones; i++) {
            gotoxy(11, 8 + i * 2);
            if (i == seleccion) {
                setColor(BACKGROUND_BLUE | BACKGROUND_GREEN | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                cout << " > " << opciones[i] << " ";
            } else {
                setColor(7);
                cout << "   " << opciones[i] << " ";
            }
        }

        setColor(8);
        gotoxy(6, 13);
        cout << "Usa Flechas Arriba/Abajo y ENTER (o 1-2)";
        setColor(7);

        int tecla = _getch();
        if (tecla == 0 || tecla == 224) {
            tecla = _getch();
            if (tecla == 72 || tecla == 80) {
                seleccion = (seleccion == 0) ? 1 : 0;
            }
        } else if (tecla == 13) {
            return seleccion + 1;
        } else if (tecla == '1' || tecla == '2') {
            return tecla - '0';
        }
    }
}

void elegirColores(int& colorJ1, int& colorJ2, char j1Char, char j2Char, int colorMeta, int colorObstaculo) {
    const int codigosColor[] = { 10, 11, 13, 15, 9, 2, 3 };
    const char* nombresColor[] = {
        "Verde brillante",
        "Cian brillante",
        "Magenta brillante",
        "Blanco brillante",
        "Azul brillante",
        "Verde oscuro",
        "Cian oscuro"
    };
    const int totalColores = sizeof(codigosColor) / sizeof(codigosColor[0]);

    for (int jugador = 1; jugador <= 2; jugador++) {
        int colorActual = (jugador == 1) ? colorJ1 : colorJ2;
        char simboloActual = (jugador == 1) ? j1Char : j2Char;
        int seleccion = 0;

        for (int i = 0; i < totalColores; i++) {
            if (codigosColor[i] == colorActual) {
                seleccion = i;
                break;
            }
        }

        while (true) {
            system("cls");
            dibujarCuadroMarco(56, 21, BACKGROUND_BLUE | BACKGROUND_INTENSITY);

            setColor(11);
            gotoxy(15, 2);
            cout << "=== ELEGIR COLOR J" << jugador << " ===";

            setColor(7);
            gotoxy(6, 4);
            cout << "Vista previa: ";
            setColor(codigosColor[seleccion]);
            cout << simboloActual << "  (" << nombresColor[seleccion] << ")";
            setColor(7);

            for (int i = 0; i < totalColores; i++) {
                gotoxy(10, 6 + i);
                setColor(codigosColor[i]);
                if (i == seleccion) {
                    cout << " > " << (i + 1) << ". " << nombresColor[i] << " [" << simboloActual << "]";
                } else {
                    cout << "   " << (i + 1) << ". " << nombresColor[i] << " [" << simboloActual << "]";
                }
            }

            setColor(8);
            gotoxy(6, 15);
            cout << "Reservados: Meta (amarillo) y Enemigos (rojo)";
            gotoxy(6, 17);
            cout << "Usa Flechas Arriba/Abajo y ENTER (o 1-7)";
            setColor(7);

            int tecla = _getch();
            int candidatoIdx = -1;

            if (tecla == 0 || tecla == 224) {
                tecla = _getch();
                if (tecla == 72) {
                    seleccion = (seleccion - 1 + totalColores) % totalColores;
                } else if (tecla == 80) {
                    seleccion = (seleccion + 1) % totalColores;
                }
            } else if (tecla == 13) {
                candidatoIdx = seleccion;
            } else if (tecla >= '1' && tecla < '1' + totalColores) {
                candidatoIdx = tecla - '1';
                seleccion = candidatoIdx;
            }

            if (candidatoIdx != -1) {
                int elegido = codigosColor[candidatoIdx];
                int otroColor = (jugador == 1) ? colorJ2 : colorJ1;

                if (elegido == colorMeta || elegido == colorObstaculo || elegido == otroColor) {
                    setColor(12);
                    gotoxy(6, 16);
                    cout << "Color no disponible (repetido o reservado). Elige otro.";
                    setColor(7);
                    Sleep(900);
                    continue;
                }

                if (jugador == 1) {
                    colorJ1 = elegido;
                } else {
                    colorJ2 = elegido;
                }
                break;
            }
        }
    }
}

void elegirPersonajes(char& jugador1Char, char& jugador2Char, int& colorJ1, int& colorJ2,
                      char metaChar, char obstaculoChar, int colorMeta, int colorObstaculo) {
    const char sugeridos[] = { '@', '#', '*', '+', 'O', 'P', '&', '%' };
    const int totalSugeridos = sizeof(sugeridos) / sizeof(sugeridos[0]);

    for (int jugador = 1; jugador <= 2; jugador++) {
        while (true) {
            system("cls");
            dibujarCuadroMarco(56, 20, BACKGROUND_BLUE | BACKGROUND_INTENSITY);

            setColor(11);
            gotoxy(14, 2);
            cout << "=== ELEGIR PERSONAJE J" << jugador << " ===";

            setColor(7);
            gotoxy(5, 5);
            cout << "Caracter actual de J" << jugador << ": ";
            setColor(jugador == 1 ? colorJ1 : colorJ2);
            cout << (jugador == 1 ? jugador1Char : jugador2Char);

            setColor(7);
            gotoxy(5, 7);
            cout << "Sugeridos (pulsa 1-" << totalSugeridos << "):";
            for (int i = 0; i < totalSugeridos; i++) {
                gotoxy(5 + i * 5, 9);
                setColor(14);
                cout << (i + 1) << ":" << sugeridos[i];
            }

            setColor(7);
            gotoxy(5, 12);
            cout << "O escribe cualquier caracter visible en teclado.";

            setColor(8);
            gotoxy(5, 14);
            cout << "Reservados: Meta (" << metaChar << "), Enemigo (" << obstaculoChar << ") y J"
                 << (jugador == 1 ? "2 (" + string(1, jugador2Char) + ")" : "1 (" + string(1, jugador1Char) + ")");

            setColor(10);
            gotoxy(5, 17);
            cout << "Presiona una tecla para elegir...";
            setColor(7);

            int tecla = _getch();
            if (tecla == 0 || tecla == 224) {
                _getch();
                continue;
            }

            char elegido = 0;
            if (tecla >= '1' && tecla < '1' + totalSugeridos) {
                elegido = sugeridos[tecla - '1'];
            } else if (tecla >= 33 && tecla <= 126) {
                elegido = static_cast<char>(tecla);
            } else {
                continue;
            }

            char otroJugador = (jugador == 1) ? jugador2Char : jugador1Char;
            if (elegido == metaChar || elegido == obstaculoChar || elegido == otroJugador) {
                setColor(12);
                gotoxy(5, 15);
                cout << "Ese simbolo ('" << elegido << "') no esta disponible. Prueba otro.";
                setColor(7);
                Sleep(900);
                continue;
            }

            if (jugador == 1) {
                jugador1Char = elegido;
            } else {
                jugador2Char = elegido;
            }
            break;
        }
    }

    elegirColores(colorJ1, colorJ2, jugador1Char, jugador2Char, colorMeta, colorObstaculo);
}

void mostrarInstrucciones(char j1Char, char j2Char, int colorJ1, int colorJ2, char metaChar, char obstaculoChar) {
    system("cls");
    dibujarCuadroMarco(64, 24, BACKGROUND_BLUE | BACKGROUND_INTENSITY);

    setColor(14);
    gotoxy(22, 2);
    cout << "=== INSTRUCCIONES ===";

    setColor(colorJ1);
    gotoxy(4, 5);
    cout << "Jugador 1 (" << j1Char << "): ";
    setColor(7);
    cout << "Se mueve con W, A, S, D";

    setColor(colorJ2);
    gotoxy(4, 7);
    cout << "Jugador 2 (" << j2Char << "): ";
    setColor(7);
    cout << "Se mueve con las Flechas (en 2 Jugadores)";

    setColor(14);
    gotoxy(4, 9);
    cout << "Meta (" << metaChar << "):      ";
    setColor(7);
    cout << "Cambia de posicion en cada partida y nivel";

    setColor(12);
    gotoxy(4, 11);
    cout << "Enemigos (" << obstaculoChar << "):  ";
    setColor(7);
    cout << "Minimo 3; suben por nivel (max. 12 en Sin Fin)";

    setColor(11);
    gotoxy(4, 13);
    cout << "Eventos aleatorios por nivel:";
    setColor(7);
    gotoxy(6, 14);
    cout << "- Sin paredes (1/12): elimina barreras internas";
    gotoxy(6, 15);
    cout << "- Colores invertidos (1/8): intercambia colores";
    gotoxy(6, 16);
    cout << "- Controles invertidos (1/8): invierte direcciones";

    setColor(8);
    gotoxy(11, 20);
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
        dibujarCuadroMarco(56, 18, BACKGROUND_BLUE | BACKGROUND_INTENSITY);

        setColor(colorTitulo);
        gotoxy(12, 3);
        cout << titulo;

        setColor(7);
        gotoxy(5, 5);
        cout << detalle;

        for (int i = 0; i < numOpciones; i++) {
            gotoxy(16, 8 + i * 2);
            if (i == seleccion) {
                setColor(BACKGROUND_BLUE | BACKGROUND_GREEN | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                cout << " > " << opciones[i] << " ";
            } else {
                setColor(7);
                cout << "   " << opciones[i] << " ";
            }
        }

        setColor(8);
        gotoxy(8, 15);
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
    const int TOTAL_NIVELES_CAMPANA = 5;
    const int OBSTACULOS_INICIALES = 3;
    const int MAX_OBSTACULOS_SIN_FIN = 12;
    const int MAX_PAREDES = 140;

    char jugador1Char = '@';
    char jugador2Char = '&';
    const char metaChar = '$';
    const char obstaculoChar = 'X';

    const int COLOR_NORMAL = 7;
    const int COLOR_BORDE_AZUL = BACKGROUND_BLUE | BACKGROUND_INTENSITY;
    const int COLOR_PARED_CUADRO = BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_INTENSITY;
    int colorJugador1Base = 10; // Verde brillante
    int colorJugador2Base = 11; // Cian brillante
    const int COLOR_OBSTACULO_BASE = 12; // Rojo
    const int COLOR_META_BASE = 14;      // Amarillo

    srand(static_cast<unsigned int>(time(0)));
    ocultarCursor();

    bool ejecutandoPrograma = true;

    while (ejecutandoPrograma) {
        int opcionMenu = mostrarMenuPrincipal(jugador1Char, jugador2Char, colorJugador1Base, colorJugador2Base);

        if (opcionMenu == 4) {
            elegirPersonajes(jugador1Char, jugador2Char, colorJugador1Base, colorJugador2Base,
                             metaChar, obstaculoChar, COLOR_META_BASE, COLOR_OBSTACULO_BASE);
            continue;
        } else if (opcionMenu == 5) {
            mostrarInstrucciones(jugador1Char, jugador2Char, colorJugador1Base, colorJugador2Base,
                                 metaChar, obstaculoChar);
            continue;
        } else if (opcionMenu == 6) {
            break;
        }

        bool modoSinFin = (opcionMenu == 3);
        int modoJugadores = modoSinFin ? elegirJugadoresParaSinFin() : opcionMenu; // 1 = 1 Jugador, 2 = 2 Jugadores
        bool volverAJugar = true;

        while (volverAJugar) {
            int nivel = 1;
            bool ganoTodosLosNiveles = true;
            bool salioConEsc = false;
            int nivelFallo = 1;

            while (modoSinFin || nivel <= TOTAL_NIVELES_CAMPANA) {
                system("cls");
                setColor(COLOR_NORMAL);

                TipoEvento eventoActual = sortearEventoNivel();
                bool sinParedes = (eventoActual == EVENTO_SIN_PAREDES);
                bool coloresInvertidos = (eventoActual == EVENTO_COLORES_INVERTIDOS);
                bool controlesInvertidos = (eventoActual == EVENTO_CONTROLES_INVERTIDOS);

                int colorJ1Nivel = colorJugador1Base;
                int colorJ2Nivel = colorJugador2Base;
                int colorObsNivel = COLOR_OBSTACULO_BASE;
                int colorMetaNivel = COLOR_META_BASE;

                if (coloresInvertidos) {
                    if (modoJugadores == 2) {
                        int temp = colorJ1Nivel;
                        colorJ1Nivel = colorJ2Nivel;
                        colorJ2Nivel = temp;
                    }
                    colorObsNivel = COLOR_META_BASE;
                    colorMetaNivel = COLOR_OBSTACULO_BASE;
                }

                int numObstaculos = OBSTACULOS_INICIALES + (nivel - 1);
                if (modoSinFin && numObstaculos > MAX_OBSTACULOS_SIN_FIN) {
                    numObstaculos = MAX_OBSTACULOS_SIN_FIN;
                }

                int segmentosEfectivos = (nivel <= 8) ? nivel : 8;
                int numSegmentos = sinParedes ? 0 : (4 + (segmentosEfectivos * 2));

                int x1 = (modoJugadores == 1) ? (Ancho / 2) : ((Ancho / 2) - 3);
                int y1 = Alto / 2;
                int x2 = (Ancho / 2) + 3;
                int y2 = Alto / 2;

                int tecla = 0;
                bool nivelTerminado = false;
                bool ganoNivel = false;

                // Meta aleatoria
                int metaX, metaY;
                do {
                    metaX = 2 + rand() % (Ancho - 4);
                    metaY = 2 + rand() % (Alto - 4);
                } while ((abs(metaX - x1) <= 2 && abs(metaY - y1) <= 2) ||
                         (modoJugadores == 2 && abs(metaX - x2) <= 2 && abs(metaY - y2) <= 2));

                // Generar barreras tipo laberinto (omitidas si hay evento SIN PAREDES)
                int paredX[MAX_PAREDES], paredY[MAX_PAREDES];
                int numParedes = 0;

                if (!sinParedes) {
                    for (int s = 0; s < numSegmentos; s++) {
                        bool horizontal = (rand() % 2 == 0);
                        int longitud = 3 + rand() % 5;
                        int baseX = 2 + rand() % (Ancho - 4);
                        int baseY = 2 + rand() % (Alto - 4);

                        for (int step = 0; step < longitud && numParedes < MAX_PAREDES; step++) {
                            int cx = horizontal ? (baseX + step) : baseX;
                            int cy = horizontal ? baseY : (baseY + step);

                            if (cx <= 1 || cx >= Ancho - 2 || cy <= 1 || cy >= Alto - 2) {
                                break;
                            }

                            bool cercaInicio1 = (abs(cx - x1) <= 2 && abs(cy - y1) <= 2);
                            bool cercaInicio2 = (modoJugadores == 2 && abs(cx - x2) <= 2 && abs(cy - y2) <= 2);
                            bool cercaMeta = (abs(cx - metaX) <= 1 && abs(cy - metaY) <= 1);

                            if (!cercaInicio1 && !cercaInicio2 && !cercaMeta &&
                                !esPared(cx, cy, paredX, paredY, numParedes)) {
                                paredX[numParedes] = cx;
                                paredY[numParedes] = cy;
                                numParedes++;
                            }
                        }
                    }
                }

                // Obstaculos moviles
                int obsX[MAX_OBSTACULOS_SIN_FIN], obsY[MAX_OBSTACULOS_SIN_FIN];
                int obsDx[MAX_OBSTACULOS_SIN_FIN], obsDy[MAX_OBSTACULOS_SIN_FIN];

                for (int k = 0; k < numObstaculos; k++) {
                    bool valido;
                    do {
                        valido = true;
                        obsX[k] = 1 + rand() % (Ancho - 2);
                        obsY[k] = 1 + rand() % (Alto - 2);

                        if ((abs(obsX[k] - x1) <= 2 && abs(obsY[k] - y1) <= 2) ||
                            (modoJugadores == 2 && abs(obsX[k] - x2) <= 2 && abs(obsY[k] - y2) <= 2) ||
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
                setColor(colorMetaNivel);
                gotoxy(metaX, metaY);
                cout << metaChar;

                // Dibujar enemigos moviles
                setColor(colorObsNivel);
                for (int k = 0; k < numObstaculos; k++) {
                    gotoxy(obsX[k], obsY[k]);
                    cout << obstaculoChar;
                }

                // Dibujar Jugador 1 (y Jugador 2 solo en modo 2 jugadores)
                setColor(colorJ1Nivel);
                gotoxy(x1, y1);
                cout << jugador1Char;

                if (modoJugadores == 2) {
                    setColor(colorJ2Nivel);
                    gotoxy(x2, y2);
                    cout << jugador2Char;
                }

                // Informacion inferior y evento activo
                setColor(COLOR_NORMAL);
                gotoxy(0, Alto + 1);
                if (modoSinFin) {
                    cout << "Modo: Sin Fin (" << modoJugadores << "J) | Nivel: " << nivel
                         << " | Enemigos: " << numObstaculos << "/" << MAX_OBSTACULOS_SIN_FIN
                         << " | Meta: " << metaChar;
                } else {
                    cout << "Modo: " << (modoJugadores == 1 ? "1 Jugador" : "2 Jugadores")
                         << " | Nivel: " << nivel << "/" << TOTAL_NIVELES_CAMPANA
                         << " | Enemigos: " << numObstaculos
                         << " | Meta: " << metaChar;
                }

                gotoxy(0, Alto + 2);
                if (eventoActual != EVENTO_NINGUNO) {
                    setColor(14);
                    cout << "EVENTO ACTIVO: " << nombreEvento(eventoActual);
                    setColor(COLOR_NORMAL);
                } else {
                    setColor(8);
                    cout << "EVENTO ACTIVO: " << nombreEvento(eventoActual);
                    setColor(COLOR_NORMAL);
                }

                gotoxy(0, Alto + 3);
                if (modoJugadores == 1) {
                    cout << "J1 (" << jugador1Char << "): WASD | Menu/Salir: ESC";
                } else {
                    cout << "J1 (" << jugador1Char << "): WASD | J2 (" << jugador2Char << "): Flechas | Menu/Salir: ESC";
                }

                // Anuncio destacado al iniciar el nivel si hubo un evento
                if (eventoActual != EVENTO_NINGUNO) {
                    setColor(13);
                    gotoxy(0, Alto + 5);
                    cout << ">>> OCURRIO EL EVENTO: " << nombreEvento(eventoActual) << " <<<";
                    setColor(COLOR_NORMAL);
                    Sleep(1300);
                    gotoxy(0, Alto + 5);
                    cout << "                                                                                ";
                }

                int ticksObstaculos = 0;

                while (!nivelTerminado) {
                    if (_kbhit()) {
                        tecla = _getch();

                        int jugadorActivo = 0;
                        int nx = 0, ny = 0;

                        if (tecla == 0 || tecla == 224) {
                            tecla = _getch();
                            if (modoJugadores == 2) {
                                jugadorActivo = 2;
                                nx = x2;
                                ny = y2;
                                int dy = 0, dx = 0;
                                if (tecla == 72) dy = -1;
                                else if (tecla == 80) dy = 1;
                                else if (tecla == 75) dx = -1;
                                else if (tecla == 77) dx = 1;
                                else jugadorActivo = 0;

                                if (jugadorActivo == 2) {
                                    if (controlesInvertidos) {
                                        dx = -dx;
                                        dy = -dy;
                                    }
                                    nx += dx;
                                    ny += dy;
                                }
                            }
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
                                int dy = 0, dx = 0;
                                if (c == 'w') dy = -1;
                                else if (c == 's') dy = 1;
                                else if (c == 'a') dx = -1;
                                else if (c == 'd') dx = 1;

                                if (controlesInvertidos) {
                                    dx = -dx;
                                    dy = -dy;
                                }
                                nx += dx;
                                ny += dy;
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
                                if (modoJugadores == 1 || !(nx == x2 && ny == y2)) {
                                    gotoxy(x1, y1);
                                    cout << " ";
                                    x1 = nx;
                                    y1 = ny;
                                    setColor(colorJ1Nivel);
                                    gotoxy(x1, y1);
                                    cout << jugador1Char;
                                }
                            } else {
                                if (!(nx == x1 && ny == y1)) {
                                    gotoxy(x2, y2);
                                    cout << " ";
                                    x2 = nx;
                                    y2 = ny;
                                    setColor(colorJ2Nivel);
                                    gotoxy(x2, y2);
                                    cout << jugador2Char;
                                }
                            }
                            setColor(COLOR_NORMAL);

                            bool llegoMeta1 = (x1 == metaX && y1 == metaY);
                            bool llegoMeta2 = (modoJugadores == 2 && x2 == metaX && y2 == metaY);
                            if (llegoMeta1 || llegoMeta2) {
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

                                setColor(colorObsNivel);
                                gotoxy(obsX[k], obsY[k]);
                                cout << obstaculoChar;
                                setColor(COLOR_NORMAL);
                            }

                            bool chocoCon1 = (obsX[k] == x1 && obsY[k] == y1);
                            bool chocoCon2 = (modoJugadores == 2 && obsX[k] == x2 && obsY[k] == y2);
                            if (chocoCon1 || chocoCon2) {
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
                    if (modoSinFin || nivel < TOTAL_NIVELES_CAMPANA) {
                        setColor(10);
                        gotoxy(0, Alto + 5);
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
                char msgEsc[75];
                if (modoSinFin) {
                    sprintf(msgEsc, "Saliste en el nivel %d del Modo Sin Fin.", nivelFallo);
                } else {
                    sprintf(msgEsc, "Saliste de la partida actual.");
                }
                opcionFin = mostrarMenuFinPartida("=== PARTIDA PAUSADA / SALIDA ===", 14, msgEsc);
            } else if (!modoSinFin && ganoTodosLosNiveles) {
                const char* msgGanar = (modoJugadores == 1)
                    ? "Completaste los 5 niveles con exito."
                    : "Completaron los 5 niveles con exito.";
                opcionFin = mostrarMenuFinPartida("=== FELICIDADES, GANASTE! ===", 10, msgGanar);
            } else {
                char mensajeDetalle[85];
                if (modoSinFin) {
                    sprintf(mensajeDetalle, "Caiste en el nivel %d (Sin Fin) al chocar.", nivelFallo);
                } else if (modoJugadores == 1) {
                    sprintf(mensajeDetalle, "Perdiste en el nivel %d al chocar.", nivelFallo);
                } else {
                    sprintf(mensajeDetalle, "Perdieron en el nivel %d al chocar.", nivelFallo);
                }
                opcionFin = mostrarMenuFinPartida("=== GAME OVER - PERDISTE ===", 12, mensajeDetalle);
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