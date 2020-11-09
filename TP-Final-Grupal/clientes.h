#ifndef CLIENTES_H_INCLUDED
#define CLIENTES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <time.h>
#define AR_CLIENTES "clientes.dat"
#define AR_CONSUMOS "consumos.dat"
#define ESC 27
#define DIM_CLI 100




typedef struct
{
    int id;
    int nroCliente;
    char nombre[30];
    char apellido[30];
    int dni;
    char email[30];
    char domicilio[45];
    char movil[20];
    int baja; /// 1 si esta activo / 0 si esta dado de baja.
} stCliente;

stCliente cargaUnCliente(); ///cliente
int cargarListaClientes(stCliente c[], int v, int dim); ///cliente
void guardarUnCliente(stCliente c); ///cliente
void cargarArchListaClientes(); ///cliente
int buscoUltimoID(); ///cliente
void muestraUnCliente(stCliente c); ///cliente
void mostrarArchClientes(); ///cliente
stCliente buscaClienteArchxNroCliente(int nroCliente);
void encontrarClienteArch();
void modificarClienteArch(stCliente c);
void menuModificacionDatos();
int buscaPosicion(int id);
void guardarClienteModificadoArch(stCliente c);
void modifRegistro(stCliente c);
void funcion05(); ///DAR DE ALTA O BAJA
stCliente buscaPosicionDNI(int dni);
int validoDNI(int dni);
int validoNroCliente(int nro);
int archivoAArregloAltas(stCliente a[], int dim);
void muestraArreglo(int v, stCliente a[]);
int buscaMenorDNIArreglo(int v, stCliente a[], int pos);
void ordenacionSeleccionArchivoDNI();
void ordenamientoSeleccionAregloDNI(int v, stCliente a[]);
int buscaMenorApellidoArreglo(int v, stCliente a[], int pos);
void ordenamientoSeleccionAregloApellido(int v, stCliente a[]);
void ordenacionSeleccionArchivoApellido();
stCliente buscaClienteDNI(int dni);
void muestraBuscaCliente();
int archivoAArregloBajas(stCliente a[], int dim);
int buscaMenorEmailArreglo(int v, stCliente a[], int pos);
void ordenacionSeleccionArchivoEmail();


#endif // CLIENTES_H_INCLUDED
