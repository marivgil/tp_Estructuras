#include <iostream>
#include "Lavadero.h"

using namespace std;

int main()
{
                            // cuit nombre plan
    Cliente c1 = crearCliente("1", "Dan", "inicial");
    Cliente c2 = crearCliente("2", "Facu", "inicial");
    Cliente c3 = crearCliente("3", "", "");
    Cliente c4 = crearCliente("4", "", "");
    Cliente c5 = crearCliente("5", "Hilda", "inicial");
    Cliente c6 = crearCliente("6", "", "");
    Cliente c7 = crearCliente("7", "", "");
    Cliente c8 = crearCliente("8", "", "");
    Cliente c9 = crearCliente("9", "", "");
    Cliente c10 = crearCliente("10", "", "");
    Cliente c11 = crearCliente("11", "", "");
    Cliente c12 = crearCliente("12", "", "");

    Lavadero lavadero = crearLavadero();

    cout << "TEST agregarCliente ---------------------------------------------------- " << endl;
    agregarCliente(lavadero, getCuit(c1), getNombre(c1));
    agregarCliente(lavadero, getCuit(c2), getNombre(c2));
    agregarCliente(lavadero, getCuit(c3), getNombre(c3));
    agregarCliente(lavadero, getCuit(c4), getNombre(c4));
    agregarCliente(lavadero, getCuit(c5), getNombre(c5));

    printLavadero(lavadero);


    cout << "TEST obtenerCliente ------------------------------------------------------ " << endl;
    Cliente dan = obtenerCliente(lavadero, "1");
    printCliente(dan);


    Cliente facu = obtenerCliente(lavadero, "2");
    printCliente(facu);


    cout << "TEST borrarCliente ------------------------------------------------------ " << endl;
    borrarCliente(lavadero, "3");
    printLavadero(lavadero);


    cout << "TEST cantidadTotalDeClientes --------------------------------------------- " << endl;
    int cant1 = cantidadTotalDeClientes(lavadero);
    cout << "CantidadTotalDeClientes: " << cant1 << endl;


    cout << "TEST planConMasClientes ------------------------------------------------------ " << endl;
    cout << endl;
    cout << endl;
    cout << "PlanConMasClientes: " << planConMasClientes(lavadero) << endl;
    cout << endl;
    cout << endl;

    agregarCliente(lavadero, getCuit(c6), getNombre(c6));
    agregarCliente(lavadero, getCuit(c7), getNombre(c7));
    agregarCliente(lavadero, getCuit(c8), getNombre(c8));
    agregarCliente(lavadero, getCuit(c9), getNombre(c9));

    cout << "TEST darPrendas ------------------------------------------------------ " << endl;
    //aumento las prendas del cliente
    darPrendas(lavadero, getCuit(c7), 1);
    darPrendas(lavadero, getCuit(c8), 1000);
    darPrendas(lavadero, getCuit(c9), 51);
    printLavadero(lavadero);
    cout << endl;
    cout << "Cantidad prendas  C7: " << getCantidadPrendas(obtenerCliente(lavadero, "7")) << "" <<endl;
    cout << "Cantidad prendas  C8: " << getCantidadPrendas(obtenerCliente(lavadero, "8")) << "" <<endl;
    cout << "Cantidad prendas  C9: " << getCantidadPrendas(obtenerCliente(lavadero, "9")) << "" <<endl;

    cout << "planConMasClientes -- " << planConMasClientes(lavadero) << endl;
    cout << endl;
    cout << endl;
    cout << endl;

    darPrendas(lavadero, getCuit(c1), 51);
    darPrendas(lavadero, getCuit(c2), 51);
    darPrendas(lavadero, getCuit(c4), 51);
    darPrendas(lavadero, getCuit(c5), 51);
    darPrendas(lavadero, getCuit(c6), 51);
    printLavadero(lavadero);
    cout << endl;
    cout << endl;
    cout << "PlanConMasClientes: " << planConMasClientes(lavadero) << endl;
    cout << endl;
    cout << endl;

    cout << "TEST cantidadTotalDeClientes ------------------------------------------------------ " << endl;
    int cant2 = cantidadTotalDeClientes(lavadero);
    cout << "CantidadTotalDeClientes: " << cant2 << endl;
    cout << endl;
    cout << endl;
    Cliente ma= obtenerCliente(lavadero, "9");
    cout << "Plan de C9: " << getPlan(ma) << ">_>_>_>_>_>_>_>_>_>_>_>_>_>_>_>_>_>_>_" <<endl;
    cout << endl;
    cout << endl;
    cout << "TEST recibirPrendas ------------------------------------------------------ " << endl;
    recibirPrendas(lavadero, getCuit(c9), 40);

    printLavadero(lavadero);
    cout << endl;
    cout << endl;
    cout << endl;
    cout << "Plan de C9: " << getPlan(ma) <<endl;
    cout << "Cantidad de prendas de C9: " << getCantidadPrendas(ma) <<endl;
    cout << endl;
    cout << endl;

    cout << "TEST destroy ------------------------------------------------------ " << endl;

    Cliente destroy_cli = obtenerCliente(lavadero, "1");
    printCliente(destroy_cli);
    //destroyLavadero(lavadero);
    //cout<< "ya destrui lavadero, ahora intento imprimir, deberia explotar" <<endl;
    //printLavadero(lavadero);
    //printCliente(destroy_cli);

    //prueba individual de elimino clientes para el set
    printLavadero(lavadero);
    cout << "------------------------------------------------------ " << endl;
    borrarClientesDePlan("avanzado", lavadero);
    printLavadero(lavadero);
    return 0;
}

