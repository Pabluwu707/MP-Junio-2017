#include <iostream>
#include <cstdlib> // exit

#include <redciudades.h>

using namespace std;

int main(int argc, char* argv[]) {

    if(argc != 2) {
        cerr << "Nº argumentos incorrecto" << endl;
        exit(1);
    }

    RedCiudades red(argv[1]);
    for(int i = 0; i < red.NumCiudades(); i++) {
        for(int j = i+1; j < red.NumCiudades(); j++) {
            if(red.Distancia(i, j) != 0) {
                cout << i << "-" << j << " = " << red.MejorEscalaEntre(i, j) << endl;
            }
        }
    }

    // Ejemplo comentario opcional
    // ---------------------------
    // red.EscribirRedCiudades("datos.txt", "Realizado por Vicente");
    // red.EscribirRedCiudades("datos.txt");
}
