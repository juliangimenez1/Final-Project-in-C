#include "utilidades.h"
#include "clientes.h"
#include "consumos.h"

/// BUSCA UN RANGO AL AZAR, RECIBE EL PARAMETRO INFERIOR Y EL PARAMETRO SUPERIOR
int randomRango(int rangoMin,int rangoMax)
{
    int rango = rangoMin + rand() % (rangoMax +1 - rangoMin);
    return rango;
}

void intercambio(stCliente *i, stCliente *menor)
{
    stCliente aux;

    aux = *menor;
    *menor = *i;
    *i = aux;
}

void muestraArreglo(int v, stCliente a[])
{
    int i;
    for(i = 0; i<v; i++)
    {
        muestraUnCliente(a[i]);
    }

}

/***************************************
VALIDO EMAIL.
RECIBO STRING EMAIL.
RECORRO EL STRING LETRA POR LETRA
COMPRUEBO SI HAY UN "@", si hay flag=1
si no hay flag=-1
RETORNO FLAG. (VERDADERO O FALSO)
***************************************/
int validaEmail(char email[])
{
    int v=strlen(email);
    int i=0;
    int flag=0;
    while(i<v && flag==0)
    {
        if(email[i]==64)  ///64 ES "@" EN ASCII
        {
            flag=1;
        }
        i++;
    }
    return flag;
}
