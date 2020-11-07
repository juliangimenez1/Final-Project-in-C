#ifndef UTILIDADES_H_INCLUDED
#define UTILIDADES_H_INCLUDED
#include "clientes.h"
#include "consumos.h"



int randomRango(int rangoMin,int rangoMax);
void intercambio(stCliente *i, stCliente *menor);
void muestraArreglo(int v, stCliente a[]);
int validaEmail(char email[]);
void CargaUnConsmoRandomID(int idCliente);
int verficaFecha(stConsumo a);
int buscarMesMAX();
int cargarArreglo(int a[], int v, int mesMax);
int comprarMesMayor(int a[], int v);
int diaMax (int mes);
stConsumo ConsumoRandomID(int idCliente);


#endif // UTILIDADES_H_INCLUDED
