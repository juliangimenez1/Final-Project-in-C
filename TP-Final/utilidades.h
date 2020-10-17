#ifndef UTILIDADES_H_INCLUDED
#define UTILIDADES_H_INCLUDED
#include "clientes.h"



int randomRango(int rangoMin,int rangoMax);
void intercambio(stCliente *i, stCliente *menor);
void muestraArreglo(int v, stCliente a[]);
int validaEmail(char email[]);


#endif // UTILIDADES_H_INCLUDED
