#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED
#include "consumos.h"




///ESTRUCTURA DE LISTA
typedef struct _nodoLista
{
    stConsumo dato;
    struct _nodoLista* sig;
} nodoLista;

///PROTOTIPADOS DE LISTAS

nodoLista* inicLista();
nodoLista* crearNodo(stConsumo dato);
nodoLista* agregarAlPrincipio(nodoLista* lista, nodoLista* nuevoNodo);
nodoLista* buscoUltimoNodo(nodoLista* lista);
nodoLista* agregarAlFinal(nodoLista* lista, nodoLista* nuevo);
void muestraNodo(nodoLista* aMostrar);
void mostrarLista(nodoLista* lista);

#endif // LISTA_H_INCLUDED
