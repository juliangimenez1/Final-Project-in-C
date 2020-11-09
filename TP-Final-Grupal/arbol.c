#include "arbol.h"
#include "lista.h"

///FUNCIONES DE ARBOLES

nodoArbol* inicArbol()
{
    return NULL;
}

nodoArbol* crearNodoArbol(stCliente dato)
{
    nodoArbol* nuevo = (nodoArbol*) malloc(sizeof(nodoArbol));

    nuevo->consumos = inicLista();
    nuevo->dato = dato;
    nuevo->der = NULL;
    nuevo->izq = NULL;

    return nuevo;
}

nodoArbol* insertar (nodoArbol* arbol, nodoArbol* nuevo)
{
    if(!arbol)
    {
        arbol = nuevo;
    }
    else
    {
        if(nuevo->dato.dni > arbol->dato.dni)
        {
            arbol->der = insertar(arbol->der, nuevo);
        }
        else
        {
            arbol->izq = insertar(arbol->izq, nuevo);
        }
    }
    return arbol;
}

void muestraNodoArbol(nodoArbol* nodo)
{
    muestraUnCliente(nodo->dato);
}

void preOrder(nodoArbol* arbol)
{
    if(arbol)
    {
        muestraNodoArbol(arbol);
        preOrder(arbol->izq);
        preOrder(arbol->der);
    }
}

void inOrder(nodoArbol* arbol)
{
    if(arbol)
    {
        inOrder(arbol->izq);
        muestraNodoArbol(arbol);
        inOrder(arbol->der);
    }
}

void postOrder(nodoArbol* arbol)
{
    if(arbol)
    {
        postOrder(arbol->izq);
        postOrder(arbol->der);
        muestraNodoArbol(arbol);
    }

}


