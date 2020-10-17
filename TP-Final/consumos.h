#ifndef CONSUMOS_H_INCLUDED
#define CONSUMOS_H_INCLUDED
#include "clientes.h"
typedef struct
{
    int id;
    int idCliente;
    int anio;
    int mes; ///1 al 12.
    int dia; ///1 a... depende los meses.
    int datosConsumidos;
    int baja; /// 1 activo / 0 de baja.
} stConsumo;

void guardarUnConsumo(stConsumo consumo);
stCliente clienteRandom (); ///utilidades
stConsumo cargaUnConsumo ();
int buscoUltimoIDConsumos();
void cargaArchListaConsumos();
void muestraUnConsumo(stConsumo c);
void mostrarArchConsumos();
void menuModificacionConsumo();
void modificacionConsumo();
stConsumo cambiarConsumo(stConsumo a);
void modifRegistroCONSUMOS(stConsumo c);
int buscaPosicionCONSUMO(int id);
stConsumo buscaxIDConsumo(int id, int anio, int mes, int dia);
void modificarConsumo(stConsumo a);
void modificoBajaConsumo();
void buscarConsumoFecha(int anio, int mes, int dia);
void preguntaFechaConsumo();
stConsumo ConsumoRandom();
void CargaUnConsmoRandom(); ///utilidades
int buscarMesMAX();
int cargarArreglo(int a[], int v, int mesMax);
void mostrarArreglo(int a[], int v); ///utilidades
int comprarMesMayor(int a[], int v);
int verficaFecha(stConsumo a);


#endif // CONSUMOS_H_INCLUDED
