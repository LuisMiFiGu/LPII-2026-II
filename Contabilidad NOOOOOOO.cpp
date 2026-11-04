/*En contabilidad cada asiento debe contar con partida doble, la suma del debe es igual a la suma del haber.
Escriba un programa que registre los movimientos de un asiento (codigo de cuenta de 1 a 9999), debe o haber y monto mayor que 0.
Hasta que se esciba el codigo 0. Al terminar muestre el total del debe, el del haber y si el haciento cuadra;
Sino cuadra indique cuanto falta y en que lado. Un haciento necesita almenos movimientos*/
#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>

using namespace std;

// Definicion de colores ANSI para la consola
#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define CYAN    "\033[36m"
#define GREEN   "\033[32m"
#define RED     "\033[31m"
#define YELLOW  "\033[33m"

int main() {
    cout << CYAN << BOLD << "--- REGISTRO DE ASIENTO CONTABLE ---\n" << RESET;
    cout << "Ingrese el codigo de cuenta (1 a 9999). Escriba 0 para terminar.\n\n";

    double total_debe = 0.0;
    double total_haber = 0.0;
    int movimientos_count = 0;

    while (true) {
        int codigo;
        cout << "Movimiento #" << (movimientos_count + 1) << " - Codigo de cuenta (1-9999 | 0 para salir): ";
        
        // Validar entrada numerica para el codigo
        if (!(cin >> codigo)) {
            cout << RED << "Error: Por favor, ingrese un valor numerico valido.\n\n" << RESET;
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        // Condicion de salida
        if (codigo == 0) {
            break;
        }

        // Validar rango del codigo de cuenta
        if (codigo < 1 || codigo > 9999) {
            cout << RED << "Error: El codigo de cuenta debe estar entre 1 y 9999. Intente de nuevo.\n\n" << RESET;
            continue;
        }

        char tipo;
        cout << "Tipo de movimiento ('d' para Debe, 'h' para Haber): ";
        cin >> tipo;
        tipo = tolower(tipo); // Convertir a minuscula por si acaso

        if (tipo != 'd' && tipo != 'h') {
            cout << RED << "Error: Tipo invalido. Debe escribir 'd' (Debe) o 'h' (Haber).\n\n" << RESET;
            continue;
        }

        double monto;
        cout << "Ingrese el monto (> 0 y < 9999999): ";
        if (!(cin >> monto)) {
            cout << RED << "Error: Por favor, ingrese un monto valido.\n\n" << RESET;
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        // Validar monto mayor a 0
        if (monto <= 0 || monto >=999999) {
            cout << RED << "Error Intente de nuevo.\n\n" << RESET;
            continue;
        }

        // Acumular valores
        if (tipo == 'd') {
            total_debe += monto;
        } else {
            total_haber += monto;
        }

        movimientos_count++;
        cout << GREEN << "Movimiento registrado con exito.\n\n" << RESET;
    }

    // Resumen final del asiento
    cout << "\n" << CYAN << string(40, '=') << "\n";
    cout << "       RESUMEN DEL ASIENTO CONTABLE\n";
    cout << string(40, '=') << "\n" << RESET;

    // Validacion de que al menos exista un movimiento
    if (movimientos_count == 0) {
        cout << YELLOW << "No se registro ningun movimiento en el asiento.\n" << RESET;
        cout << CYAN << string(40, '=') << "\n" << RESET;
        return 0;
    }

    // Configurar la salida de numeros decimales a 2 posiciones (estandard contable)
    cout << fixed << setprecision(2);

    cout << "Total Movimientos Registrados: " << movimientos_count << "\n";
    cout << "Total Debe:  $ " << total_debe << "\n";
    cout << "Total Haber: $ " << total_haber << "\n";
    cout << string(40, '-') << "\n";

    // Calcular diferencia redondeando a dos decimales
    double diferencia = round(abs(total_debe - total_haber) * 100.0) / 100.0;

    if (diferencia == 0.0) {
        cout << GREEN << BOLD << "El asiento CUADRA perfectamente! (Debe = Haber)\n" << RESET;
    } else {
        cout << RED << BOLD << "El asiento NO cuadra.\n" << RESET;
        if (total_debe > total_haber) {
            cout << RED << "Faltan $ " << diferencia << " en el lado del HABER.\n" << RESET;
        } else {
            cout << RED << "Faltan $ " << diferencia << " en el lado del DEBE.\n" << RESET;
        }
    }
    cout << CYAN << string(40, '=') << "\n" << RESET;

    return 0;
}
