#ifndef UTILIDADES_H_INCLUDED
#define UTILIDADES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <time.h>
#include "clientes.h"
#include "consumos.h"
#define AR_CLIENTES "clientes.dat"
#define AR_CONSUMOS "consumos.dat"
#define ESC 27
#define DIM_CLI 100



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
stCliente clienteRandom (); ///utilidades


#endif // UTILIDADES_H_INCLUDED
