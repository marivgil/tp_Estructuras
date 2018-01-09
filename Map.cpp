#include "Map.h"

///////////////////////////////////////////////
/// OPERACIONES SOBRE AVL
///////////////////////////////////////////////

// Prop.: crea una hoja con determinado cliente
AVL leafAVL(Cliente c) {
    AVLNode* node = new AVLNode;
    node->height = 1;
    node->left   = NULL;
    node->right  = NULL;
    node->kv     = c;
    return node;
}

// Prop.: devuelve la altura de un AVL
int heightAVL(AVL t) {
    return t == NULL ? 0 : t->height;
}

// Prop.: hace una rotación simple
AVL sJoinAVL(Cliente kv, AVL ti, AVL td) {
    AVL node      = leafAVL(kv);
    node->height  = 1 + max(heightAVL(ti), heightAVL(td));
    node->left    = ti;
    node->right   = td;
    return node;
}

/// PRECOND: ti es dos más profundo que td (y por lo tanto es no vacio)
// Prop.: realiza una rotación a izquierda
AVL lJoinAVL(Cliente kv, AVL ti, AVL td) {
    Cliente kvi = ti->kv;
    AVL tii     = ti->left;
    AVL tid     = ti->right;
    int hii     = heightAVL(tii);
    int hid     = heightAVL(tid);
    if (hii >= hid) {
        return sJoinAVL(kvi, tii, sJoinAVL(kv, tid, td));
    }

    Cliente kvid = tid->kv;
    AVL tidi     = tid->left;
    AVL tidd     = tid->right;
    return sJoinAVL(kvid, sJoinAVL(kvi, tii, tidi), sJoinAVL(kv, tidd, td));
}

/// PRECOND: td es dos más profundo que ti (y por lo tanto es no vacio)
// Prop.: realiza una rotación a derecha
AVL rJoinAVL(Cliente kv, AVL ti, AVL td) {
    Cliente kvd = td->kv;
    AVL tdi     = td->left;
    AVL tdd     = td->right;
    int hdi = heightAVL(tdi);
    int hdd = heightAVL(tdd);
    if (hdi <= hdd) {
        return sJoinAVL(kvd, sJoinAVL(kv, ti, tdi), tdd);
    }

    Cliente kvdi = tdi->kv;
    AVL tdii = tdi->left;
    AVL tdid = tdi->right;
    return sJoinAVL(kvdi, sJoinAVL(kv, ti, tdii), sJoinAVL(kvd, tdid, tdd));
}

/**
PRECOND:
  * ti y td son BSTs
  * las claves de ti son menores que kv
  * las claves de td son mayores que kv
  * ti y td son AVLs
  * PERO ti y td pueden tener mas altura que lo necesario!!! (pero no deben!)
     (ojo: ti dos mas que td, o td dos mas que ti, pues antes eran AVLs...)
**/
// Prop.: realiza una rotación en base a las alturas
AVL joinAVL(Cliente c, AVL ti, AVL td) {
    int hi = heightAVL(ti);
    int hd = heightAVL(td);
    if (abs(hi-hd) <= 1) {
        return sJoinAVL(c, ti, td);
    } else if (hi == hd + 2) {
        return lJoinAVL(c, ti, td);
    } else if (hd == hi + 2) {
        return rJoinAVL(c, ti, td);
    }
    // nunca puede darse otro caso
    cout << "Se viola el invariante de representación!" << endl;
}

/// PRECOND: el AVL no está vacío
// Prop.: asigna el minimo al primer parametro y devuelve "t" sin ese minimo
AVL splitMaxAVL(Cliente& c, AVL t) {
    if(t->right == NULL) {
        Cliente cliente = t->kv;
        AVL left        = t->left;
        delete t->right;
        delete t;
        c  = cliente;
        return left;
    } else {
        AVL td = splitMaxAVL(c, t->right);
        return joinAVL(t->kv, t->left, td);
    }
}

///////////////////////////////////////////////
/// INTERFAZ DE MAP Y AUXILIARES
///////////////////////////////////////////////

/**
* INVARIANTES DE REPRESENTACION
* - el arbol es AVL
*/

/**
*PRO: crea un map vacio
*PRE: no tiene
*ORD: O(1)
*/
// Prop.: crea un Map vacio
Map emptyM() {
    return NULL;
}


/**
*PRO: valida si el map es vacio
*PRE: no tiene
*ORD: O(1)
*/
// Prop.: crea un Map vacio
bool isEmptyM(Map& m) {
    return (m==NULL);
}

/**
*PRO: dado un cuit, retorna el cliente previa busqueda en el arbol
*PRE: no tiene
*ORD: O(log n) ya que en el peor de los casos, cuando no encuentro
        lo buscado, solo debe recorrer completa una de las ramas del arbol
*/
// Prop.: devuelve un value dado una key
Cliente lookupM(Map& m, string key) {

    if(isEmptyM(m))
        return NULL;

    if(key==getCuit(m->kv)){
        return m->kv;
    } else {
        if(key<getCuit(m->kv))
                return lookupM(m->left,key);
        else
            if(key>getCuit(m->kv))
                    return lookupM(m->right,key);
    }

}

/**
*PRO: Agrega un cliente al arbol
*PRE: no tiene
*ORD: O(log n) porque para agregar un elemento debo recorrer como mucho
    una sola rama del arbol
*/
// Prop.: asocia un key con un value
void addM(Map& m, Cliente cliente) {

    if(isEmptyM(m))
        m = leafAVL(cliente);

    if(getCuit(cliente) < getCuit(m->kv)){
        if(isEmptyM(m->left))
            m->left = leafAVL(cliente);
        else
            addM(m->left, cliente);
    }else{
        if(getCuit(cliente) > getCuit(m->kv))
            if(isEmptyM(m->right))
                m->right = leafAVL(cliente);
            else
                addM(m->right, cliente);
    }

    m = joinAVL(m->kv, m->left, m->right);
}


// Prop.: indica si la respuesta del lookup es válida
bool isNothing(Cliente c) {
    return c == NULL;
}

/**
*PRO: eliminar del  arbol el valor que recibe
*PRE: no  tiene
*ORD: O(log n) porque debe recorrer como mucho una rama del arbol hasta encontrar el elemento
*     buscado para eliminar
*/
// Prop.: elimina un value dado una key
void removeM(Map& m, string key) {
    if(m == NULL) {
        return;
    }

    if(getCuit(m->kv) == key) {
       if(m->left == NULL){
            Map aux=m->right;
            delete m;
            m=aux;
            return;
       } else {
          m = splitMaxAVL(m->kv, m);
       }
    } else if(key > getCuit(m->kv)) {
        removeM(m->right, key);
    } else if(key < getCuit(m->kv)) {
        removeM(m->left, key);
    }

    m = joinAVL(m->kv, m->left, m->right);
}

/**
*PRO: devuelve la lista de claves de un Map
*PRE: no tiene
*ORD: O(n) ya que debe recorrer todo el arbol para pasarlo a lista de claves
*/
// Prop.: devuelve la lista de claves de un Map
ArrayList domM(Map& m) {

    ArrayList resultado = crearArrayList();

    if (!isEmptyM(m)){
        add(resultado, getCuit(m->kv));
        if ((!isEmptyM(m->left))){
            addAll(resultado, domM(m->left));
        }

        if ((!isEmptyM(m->right))){
            addAll(resultado, domM(m->right));
        }
    }
    return resultado;
}

/**
*PRO: libera la memoria del map
*PRE: no tiene
*ORD: O(n) ya que debe recorrer todo el arbol eliminando cada nodo
*/
// Prop.: libera la memoria de un Map
void destroyM(Map& m) {
    if(!isEmptyM(m->right) && !isEmptyM(m->left)){
        destroyM(m->left);
        destroyM(m->right);
    }else{
        destroyCliente(m->kv);
        delete m;
        m=NULL;
    }
}

/****************************************************************
* prop: elimina del arbol los clientes recibidos
* O(n . log m ): siendo n la cantidad de clientes recibido y
* m la cantidad de clientes totales del arbol
*/
void eliminarClientesDelPlanM(ArrayList clientes, Map& m){

    for(int i = 0; i < length(clientes); i++){
        removeM(m, getAt(clientes, i));
    }
    //elimino el array auxiliar que cree para hacer la eliminacion en esta 2da estructura
    destroyArrayList(clientes);
}

///////////////////////////////////////////////
/// PRINT DEL MAP (para ver AVL como usuario)
/// NOTAR QUE ROMPE ENCAPSULAMIENTO
/// PERO AYUDA A VER EL ARBOL HASTA TENER
/// BIEN LA IMPLEMENTACION
///////////////////////////////////////////////

void emptySpace(int i) {
    for(; i > 0; i--) {
        cout << "-";
    }
}

void printMapAux(Map m, int i) {
    if(m == NULL) {
        emptySpace(i);
        cout << "NULL";
        return;
    }

    emptySpace(i);
    cout << "ROOT ";
    cout << getCuit(m->kv) << endl;

    emptySpace(i);
    printMapAux(m->left, i+1);
    cout << endl;

    emptySpace(i);
    printMapAux(m->right, i+1);
    cout << endl;
}

void printMap(Map m) {
     printMapAux(m, 0);
}
