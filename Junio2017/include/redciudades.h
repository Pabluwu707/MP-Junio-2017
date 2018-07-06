#ifndef __REDCIUDADES_H__
#define __REDCIUDADES_H__

#include <iostream>

using namespace std;


struct  InfoCiudad {
   char *  nombre; // Nombre
   int poblacion;  // Num. habs.
};

class RedCiudades {
private:
    int num_ciudades;
    InfoCiudad * info;
    double ** distancia;

    void reservar(int n);
    void copiar(const RedCiudades & otro);
    void liberar();

    int ConexionesCiudad(int i) const;
public:
    int NumCiudades() const;
    double Distancia(int i, int j) const;
    char* NombreCiudad(int i) const;
    int PoblacionCiudad(int i) const;

    RedCiudades();
    RedCiudades(const RedCiudades& red);
    RedCiudades(const char* nombre);
    ~RedCiudades();
    RedCiudades& operator=(const RedCiudades& red);

    int CiudadMejorConectada() const;
    int MejorEscalaEntre(int i, int j) const;

    void EscribirRedCiudades(const char * nombre, const char* comentario=0) const;
    void LeerRedCiudades(const char * nombre);

friend istream& operator>>(istream& is, RedCiudades& red);
};

ostream& operator<<(ostream& os, const RedCiudades& red);
istream& operator>>(istream& is, RedCiudades& red);

#endif