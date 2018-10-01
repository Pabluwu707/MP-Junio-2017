#include <redciudades.h>
#include <cstring>
#include <fstream>

using namespace std;

void RedCiudades::reservar(int n) {
    num_ciudades = n;
    if(num_ciudades > 0) {
        info = new InfoCiudad[n];
        distancia = new double*[n];
        for(int i = 0; i < n; i++)
            distancia[i] = new double[n];
    }
    else {
        info = 0;
        distancia = 0;
    }
}

void RedCiudades::copiar(const RedCiudades & otro) {
    reservar(otro.num_ciudades);
    for(int i = 0; i < num_ciudades; i++) {
        info[i] = otro.info[i];
        for(int j = 0; j < num_ciudades; j++) {
            distancia[i][j] = otro.distancia[i][j];
        }
    }
}

void RedCiudades::liberar() {
    delete[] info;
    for(int i = 0; i < num_ciudades; i++)
        delete[] distancia[i];
    delete[] distancia;

    distancia = 0;
    info = 0;
    num_ciudades = 0;
}

RedCiudades::RedCiudades() {
    distancia = 0;
    info = 0;
    num_ciudades = 0;
}

RedCiudades::RedCiudades(const RedCiudades& red) {
    copiar(red);
}

RedCiudades::RedCiudades(const char* nombre) {
    distancia = 0;
    info = 0;
    num_ciudades = 0;
    LeerRedCiudades(nombre);
}

RedCiudades::~RedCiudades() {
    liberar();
}

RedCiudades& RedCiudades::operator=(const RedCiudades& red) {
    if(this != &red) {
        liberar();
        copiar(red);
    }
    return *this;
}

int RedCiudades::ConexionesCiudad(int i) const {
    int num = 0;
    for(int j = 0; j < num_ciudades; j++) {
        if(distancia[i][j] != 0) {
            num++;
        }
    }
    return num;
}

int RedCiudades::CiudadMejorConectada() const {
    int posMejor = 0;
    int numMejor = 0;
    int numActual;
    for(int i = 0; i < num_ciudades; i++) {
        numActual = ConexionesCiudad(i);
        if(numActual > numMejor) {
            posMejor = i;
            numMejor = numActual;
        }
    }
    return posMejor;
}

int RedCiudades::MejorEscalaEntre(int i, int j) const {
    int z = -1;
    int minimoCoste, costeActual;
    // Valor infinito:
    // #include <limits>
    // minimoCoste = numeric_limits<int>::max();

    for(int k = 0; k < num_ciudades; k++) {
        if(distancia[i][k] != 0 && distancia[k][j] != 0) {
            costeActual = distancia[i][k] + distancia[k][j];
            if(z == -1 || minimoCoste > costeActual) {
                z = k;
                minimoCoste = costeActual;
            }
        }
    }
    return z;
}

void RedCiudades::LeerRedCiudades(const char * nombre) {
    ifstream fich(nombre);
    if(fich) {
        // Forma 1: Usando string
        string linea;
        getline(fich, linea); // For samu: lee una línea y lo guarda en? linea, claro
        if(linea != "RED") {
            cerr << "Error el fichero no tiene el formato correcto" << endl;
            exit(1);
        }
        // Forma 2: Cortijo
        char cadena[100];
        fich.getline(cadena, 100);
        if(strcmp(cadena, "RED")) { // strcmp devuelve 0 si son iguales
            cerr << "Error el fichero no tiene el formato correcto" << endl;
            exit(1);
        }
        // Comprobamos si hay comentario
        if(fich.peek() == '#') {
            while(fich.peek() != '\n')
                fich.ignore();
        }
        //
        fich >> *this;
    }
}

void RedCiudades::EscribirRedCiudades(const char * nombre, const char* comentario) const {
    ofstream fich(nombre);
    if(fich.is_open()) {
        fich << "RED" << endl;
        if(comentario != 0) {
            fich << "# " << comentario << endl;
        }
        fich << *this;
    }
}

int RedCiudades::NumCiudades() const {
    return num_ciudades;
}

double RedCiudades::Distancia(int i, int j) const {
    return distancia[i][j];
}

char* RedCiudades:: NombreCiudad(int i) const {
    return info->nombre;
}

int RedCiudades::PoblacionCiudad(int i) const {
    return info->poblacion;
}


ostream& operator<<(ostream& os, const RedCiudades& red) {
    os << red.NumCiudades() << endl;
    for(int i = 0; i < red.NumCiudades(); i++)
        os << i << " " << red.NombreCiudad(i) << " " << red.PoblacionCiudad(i) << endl;
    for(int i = 0; i < red.NumCiudades(); i++) {
        for(int j = i; j < red.NumCiudades(); j++) {
            os << i << " " << j << " " << red.Distancia(i, j) << endl;
        }
    }
    return os;
}

istream& operator>>(istream& is, RedCiudades& red) {
    int ciudad1, ciudad2;
    red.liberar();
    is >> red.num_ciudades;
    red.reservar(red.num_ciudades);
    for(int i = 0; i < red.num_ciudades; i++)
        is >> ciudad1 >> red.info[ciudad1].nombre >> red.info[ciudad1].poblacion;
    for(int i = 0; i < red.num_ciudades; i++) {
        for(int j = i; j < red.num_ciudades; j++) {
            is >> ciudad1 >> ciudad2 >> red.distancia[ciudad1][ciudad2];
            red.distancia[ciudad2][ciudad1] = red.distancia[ciudad1][ciudad2];
        }
    }
    return is;

}



