#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <time.h>
#include <malloc.h>
#include "clientes.h"
//#include "consumos.h"
//#include "utilidades.h"
#include "lista.h"




///ESTRUCTURA DE ARBOL
typedef struct _nodoArbol
{
    stCliente dato;
    nodoLista* consumos;
    struct _nodoArbol* izq;
    struct _nodoArbol* der;
} nodoArbol;


///PROTOTIPADOS DE ARBOLES
nodoArbol* inicArbol();
nodoArbol* crearNodoArbol(stCliente a);
nodoArbol* insertar (nodoArbol* arbol, nodoArbol* nuevo);
void muestraNodoArbol(nodoArbol* nodo);
void preOrder(nodoArbol* arbol);
void inOrder(nodoArbol* arbol);
void postOrder(nodoArbol* arbol);


#endif // ARBOL_H_INCLUDED
