#include "SetPlanes.h"
#define INT_MAX 1000000

/***
    CONSTANTES SOBRE PLANES
***/

int cantidadDePlanes() {
    return 5;
}

ArrayList nombresDePlanes() {
    ArrayList xs = crearArrayList();
    add(xs, "inicial");
    add(xs, "basico");
    add(xs, "intermedio");
    add(xs, "avanzado");
    add(xs, "full");
    return xs;
}

int planToIndex(string plan) {
    if(plan == "inicial") {
        return 0;
    }
    if(plan == "basico") {
        return 1;
    }
    if(plan == "intermedio") {
        return 2;
    }
    if(plan == "avanzado") {
        return 3;
    }
    if(plan == "full") {
        return 4;
    }
}

string indexToPlan(int index) {
    if(index == 0) {
        return "inicial";
    }
    if(index == 1) {
        return "basico";
    }
    if(index == 2) {
        return "intermedio";
    }
    if(index == 3) {
        return "avanzado";
    }
    if(index == 4) {
        return "full";
    }
}

int cantidadDePlan(string plan) {
    if(plan == "inicial") {
        return 0;
    }
    if(plan == "basico") {
        return 10;
    }
    if(plan == "intermedio") {
        return 50;
    }
    if(plan == "avanzado") {
        return 100;
    }
    if(plan == "full") {
        return INT_MAX;
    }
}

/***
    INTERFAZ DE PLANES
***/

/// AUXILIAR
Plan nuevoPlan(string nombre) {
    Plan p = new PlanSt;
    p->nombre = nombre;
    p->cuitsClientes = crearArrayList();
    return p;
}

// Prop.: agrega un cliente al plan inicial
// O(n)
SetPlanes crearPlanes() {
    ArrayList nombres = nombresDePlanes();
    Plan* planes = new Plan[cantidadDePlanes()];
    for(int i = 0; i < cantidadDePlanes(); i++) {
        string nombreActual = getAt(nombres, i);
        int indiceDeNombre  = planToIndex(nombreActual);
        planes[indiceDeNombre] = nuevoPlan(nombreActual);
    }
    destroyArrayList(nombres);
    return planes;
}

/// AUXILIAR
Plan planConNombre(SetPlanes ps, string plan) {
    return ps[planToIndex(plan)];
}

// Prop.: agrega un cliente a un plan
// Pre: el plan recibido debe pertenecer al set de planes
// O(1) tanto planConNombre como addAt son acciones sobre un array, por lo que tienen orden uno
void agregarAPlan(SetPlanes& ps, string plan, string cuit) {
    /// HECHO
    ArrayList list_c = planConNombre(ps, plan)->cuitsClientes;
    addAt(list_c, length(list_c),  cuit);
}

// Prop.: agrega un cliente al plan inicial
// O(1) utiliza agregarAPlan que es de orden uno
void agregarAPrimerPlan(SetPlanes& ps, string cuit) {
    return agregarAPlan(ps, "inicial", cuit);
}

// Prop.: borra un cliente de un plan
// Pre: no tiene
// O(n)
void borrarDePlan(SetPlanes& ps, string plan, string cuit) {
    /// HECHO
    ArrayList list_c = planConNombre(ps, plan)->cuitsClientes;
    removeAt(list_c, indexOf(list_c, cuit));
}

// Prop.: devuelve la cantidad de clientes de un plan
//pre: no tiene
// O(1) length y planConNombre son de orden uno
int cantidadDeClientes(SetPlanes ps, string plan) {
    /// HECHO
    Plan p = planConNombre(ps, plan);
    return length(p->cuitsClientes);
}

/// AUXILIAR
bool debeAumentarPlan(string planActual, int cantidadDeCliente) {
    return cantidadDePlan(planActual) < cantidadDeCliente;
}

/// AUXILIAR
string siguientePlan(string planActual) {
    return indexToPlan(planToIndex(planActual) + 1);
}

/// AUXILIAR
void pasarASiguientePlan(SetPlanes& ps, string plan, string cuit) {
    borrarDePlan(ps, plan, cuit);
    agregarAPlan(ps, siguientePlan(plan), cuit);
}

// Prop.: pasa un cliente al siguiente plan si corresponde
// y devuelve el plan en el que debería estar
// O(n) recorre la lista de planes
//recibe plan actual del cliente
string chequearPlan(SetPlanes& ps, string plan, string cuit, int cantidadDePrendas) {
    /// HECHO
    while(debeAumentarPlan(plan, cantidadDePrendas)){
        pasarASiguientePlan(ps, plan, cuit);
        plan = indexToPlan(planToIndex(plan)+1);
    }
    return plan;
}

/// AUXILIAR
void destroyPlan(Plan& p) {
    destroyArrayList(p->cuitsClientes);
    delete p;
    p = NULL;
}

// Prop.: elimina todos los planes
// O(n) recorre los planes
void destroyPlanes(SetPlanes& ps) {
    /// HECHO
    PlanIterator it = startIt(ps);
    while(!finishedIt(it)){
        Plan p = planConNombre(ps, indexToPlan(it->indiceActual));
        destroyPlan(p);
        nextIt(it);
    }
    delete ps;
    ps=NULL;
    destroyIt(it);
}

/*******************************************
* Prop: Elimina los clientes del plan recibido, retorna los clientes eliminados
* O(n): con N cantidad de clientes de ese plan, porque estoy recorriendo con el for,
*el remove de un array es de O(1)
*/
ArrayList eliminarClientesDelPlanS(string plan, SetPlanes& ps){
    ArrayList list_clientes = planConNombre(ps, plan)->cuitsClientes;
    ArrayList lista_retorno = copiar(list_clientes);
    for(int i = 0; i < length(lista_retorno); i++){
        removeAt(list_clientes, i);
    }
    list_clientes=NULL;
    return lista_retorno;
}

/***
    ITERADOR DE PLANES --------------------------------------------
***/

/**
* PRO: creo un nuevo iterador sobre el set de planes dado
* ORD: O(1)
*/
PlanIterator startIt(SetPlanes ps) {
    /// HECHO
    PlanIterator it = new PlanesIteratorSt;
	it->planes = ps;
	it->indiceActual= 0;
	return it;
}

/**
* PRO: retorna el nombre del elemento actual
* PRE: n/a
* ORD: O(1)
*/
string currentIt(PlanIterator it) {
    /// Hecho
    return indexToPlan(it->indiceActual);
}

void nextIt(PlanIterator& it) {
    /// HECHO
    it->indiceActual++;
}

/**
* PRO: indica si finalizo el plan a recorrer
* PRE: n/a
* ORD: O(1)
*/
bool finishedIt(PlanIterator it) {
    /// HECHO
    return (it->indiceActual>=5);
}

/**
* PRO: elimino el iterador
* ORD: O(1)
*/
void destroyIt(PlanIterator& it) {
    /// HECHO
    delete it;
	it = NULL;
}


/***
    IMPRESION DE PLANES
***/

void printPlan(Plan p) {
    cout << "---- Plan: " << p->nombre << endl;
    cout << "---- Clientes: " << endl;
    imprimirArrayList(p->cuitsClientes);
}

void printSet(SetPlanes ps) {

    cout << "-- Planes: " << endl;

    for(int i = 0; i < cantidadDePlanes(); i++) {
        printPlan(ps[i]);
    }

}
