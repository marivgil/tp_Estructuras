#include "Cliente.h"

Cliente crearCliente(string cuit, string nombre, string plan) {
    ClienteSt* c = new ClienteSt;
    c->cuit = cuit;
    c->nombre = nombre;
    c->cantidadPrendas = 0;
    c->plan = plan;
    return c;
}

string getCuit(Cliente c) {
    return c->cuit;
}

string getNombre(Cliente c) {
    return c->nombre;
}

void destroyCliente(Cliente& c) {
    delete c;
    c = NULL;
}

void printCliente(Cliente c) {
    cout << "Cliente {" << endl;
    cout << "  cuit: " << c->cuit << endl;
    cout << "  nombre: " << c->nombre << endl;
    cout << "  cantidad: " << c->cantidadPrendas << endl;
    cout << "  plan: " << c->plan << endl;
    cout << "}" << endl;
}

/**
  INTERFAZ EXTENDIDA
**/

// Prop.: devuelve la cantidad de prendas de un cliente
int  getCantidadPrendas(Cliente c) {
    return c->cantidadPrendas;
}

// Prop.: aumenta la cantidad de prendas de un cliente
void aumentarPrendas(Cliente& c, int cantidad)  {
    c->cantidadPrendas += cantidad;
}

// Prop.: disminuye la cantidad de prendas de un cliente
void disminuirPrendas(Cliente& c, int cantidad) {
    c->cantidadPrendas -= cantidad;
}

// Prop.: devuelve el plan de un cliente
string getPlan(Cliente& c) {
    return c->plan;
}

// Prop.: asigna un plan a un cliente
void setPlan(Cliente& c, string plan) {
    c->plan = plan;
}
