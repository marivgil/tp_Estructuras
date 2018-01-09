#include "Lavadero.h"


/**
* INVARIANTE DE REPRESENTACION
* => c cliente c E map <=> c E set
* es decir, sea c un cliente que pertenece al Map de clientes,
* entonces si o si debe estar incluido en el set de planes... y viceversa
*/


/**
* PRO: crea un lavadero vacio
* PRE:
* ORD: O(1)
*/
// Prop.: crea un lavadero vacio
// O(n) utiliza crearPlanes que es de orden N
Lavadero crearLavadero() {
    /// HECHO
    Lavadero l = new LavaderoSt;
    l->clientes = emptyM();
    l->planes   = crearPlanes();
    return l;
}

// Prop.: se obtiene el cliente asociado al cuit recibido
// Pre: no tiene
// O(log n) porque recorre como mucho una rama del arbol de clientes
Cliente obtenerCliente(Lavadero& lavadero, string cuit) {
    /// HECHO
    return lookupM(lavadero->clientes, cuit);
}

// Prop.: incorpora un cliente nuevo con plan inicial
// Pre: no tiene
// O(log n) recorre como mucho una rama del arbol de clientes para darlo de alta
void agregarCliente(Lavadero& lavadero, string cuit, string nombre) {
    /// HECHO
    Cliente c = crearCliente(cuit, nombre, "inicial"); //O(1)
    addM(lavadero->clientes, c); //O(log n)
    agregarAPlan(lavadero->planes, "inicial", cuit); //O(1)
}

// Prop.: elimina un cliente del lavadero
// O(n) el orden maximo que utiliza es el de borrarDePlan
void borrarCliente(Lavadero& lavadero, string cuit) {
    /// HECHO
    Cliente c = lookupM(lavadero->clientes, cuit); // O(log n)
    string p = getPlan(c);
    borrarDePlan(lavadero->planes, p, cuit);// O(n)
    removeM(lavadero->clientes, cuit);// O(log n)
}

// Prop.: le otorga una cantidad de prendas a un cliente
//pre:
// O(n) el mayor costo es cuando chequea el plan
void darPrendas(Lavadero& lavadero, string cuit, int cantidad) {
    /// HECHO
    Cliente c = obtenerCliente(lavadero, cuit); //log n
    aumentarPrendas(c, cantidad); // 0(1)  //seteo nueva cantidad de prendas en el cliente
    string nuevo_plan = chequearPlan(lavadero->planes, getPlan(c), cuit, cantidad); //O(n)
    //ubico al cliente en el plan correcto
    setPlan(c, nuevo_plan);
}

// Prop.: recibe una cantidad de prendas devueltas por un cliente
// O(log n) el mayor costo es cuando chequea el plan
void recibirPrendas(Lavadero& lavadero, string cuit, int cantidad) {
    /// HECHO
    Cliente c = obtenerCliente(lavadero, cuit); //log n
    disminuirPrendas(c, cantidad); //O(1)
    string nuevo_plan = chequearPlan(lavadero->planes, getPlan(c), cuit, cantidad); //O(n)
    setPlan(c, nuevo_plan);
}

// Prop.: devuelve la cantidad total de clientes del lavadero
// pre: no tiene
// O(n) el domM recorre todo el map de clientes, idem ellength
int cantidadTotalDeClientes(Lavadero lavadero) {
    /// HECHO
    return length(domM(lavadero->clientes));
}

// Prop.: devuelve el plan con mas clientes
// Pre.: existe por lo menos un plan en el lavadero
// O(n) recorro todos los planes
string planConMasClientes(Lavadero lavadero) {
    /// HECHO
    PlanIterator it = startIt(lavadero->planes);
    string resultado = currentIt(it);
    int cantidadClientesPlanActual = cantidadDeClientes(lavadero->planes, currentIt(it));

    while(!finishedIt(it)){
        nextIt(it);
        if (cantidadClientesPlanActual < cantidadDeClientes(lavadero->planes, currentIt(it))){

            resultado=currentIt(it);
        }
    }
    destroyIt(it);
    return resultado;
}

// Prop.: destruye la memoria utilizada por el lavadero
// O(n . log n) por cada cliente (N veces) debe recorrer la rama del arbol para eliminarlo
void destroyLavadero(Lavadero& lavadero) {
     destroyM(lavadero->clientes);
     destroyPlanes(lavadero->planes);
     delete lavadero;
     lavadero=NULL;
}

/**
*Prop: elimina el plan indicado por parametro del lavadero ********************************
*O(n): el recorrido sobre el set y sobre el map son de O(n) y los uso en momentos distintos
*/
void borrarClientesDePlan(string plan, Lavadero& lavadero){
    ArrayList lista_cliente = eliminarClientesDelPlanS(plan, lavadero->planes);
    eliminarClientesDelPlanM(lista_cliente, lavadero->clientes);
}

void printLavadero(Lavadero lavadero) {
    printMap(lavadero->clientes);
    printSet(lavadero->planes);
}
