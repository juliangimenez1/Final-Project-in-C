#ifndef CONSUMOS_H_INCLUDED
#define CONSUMOS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <time.h>
#include "clientes.h"
#define AR_CLIENTES "clientes.dat"
#define AR_CONSUMOS "consumos.dat"

#define ESC 27
#define DIM_CLI 100


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



#endif // CONSUMOS_H_INCLUDED
