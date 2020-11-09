#include "lista.h"
///FUNCIONES DE LISTA

nodoLista* inicLista()
{
    return NULL;
}

nodoLista* crearNodo(stConsumo dato)
{
    nodoLista* nuevo = (nodoLista*) malloc(sizeof(nodoLista));
    nuevo->dato = dato;
    nuevo->sig = NULL;

    return nuevo;
}

nodoLista* agregarAlPrincipio(nodoLista* lista, nodoLista* nuevoNodo)
{
    if(lista == NULL)
    {
        lista = nuevoNodo;
    }
    else
    {
        nuevoNodo->sig = lista;
        lista = nuevoNodo;
    }
    return lista;
}

nodoLista* buscoUltimoNodo(nodoLista* lista)
{
    nodoLista* aux = lista;

    while(aux->sig != NULL)
    {
        aux = aux->sig;
    }
    return aux;
}

nodoLista* agregarAlFinal(nodoLista* lista, nodoLista* nuevo)
{
    if(lista == NULL)
    {
        lista = nuevo;
    }
    else
    {
        nodoLista* ultimo = buscoUltimoNodo(lista);
        ultimo->sig = nuevo;
    }

    return lista;
}


void muestraNodo(nodoLista* aMostrar)
{
    muestraUnConsumo(aMostrar->dato);
}

void mostrarLista(nodoLista* lista)
{
    nodoLista* aux = lista;

    while(aux != NULL)
    {
        muestraNodo(aux);
        aux = aux->sig;
    }
}
