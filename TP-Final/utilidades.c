#include "utilidades.h"
#include "clientes.h"
#include "consumos.h"

#define AR_CLIENTES "clientes.dat"
#define AR_CONSUMOS "consumos.dat"
#define ESC 27
#define DIM_CLI 100

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
///Funcion que muestra un arreglo
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

/******************//**
* \brief Funcion que carga consumos aleatorios a un ID puntual en archivo
* \param Recibe un idCliente
* \return void
************************/
void CargaUnConsmoRandomID(int idCliente)
{
    stConsumo c;
    //stConsumo b;
    int flag;
    for (int i=0; i<23 ; i++)
    {
        c = ConsumoRandomID(idCliente);
        //c.id = idCliente;
        flag=verficaFecha(c);
        if(flag!=1)
        {
            guardarUnConsumo(c);
        }
    }
}

/*******************//**
* \brief Funcion que verifica la fecha de un consumo para que este no se repita
* \param Recibe el consumo
* \return Retorna 0 si no existe dicho consumo, 1 si existe en dicha fecha
**************************/
int verficaFecha(stConsumo a)
{
    stConsumo c;
    int flag=0;
    FILE *pArchConsumo = fopen(AR_CONSUMOS,"rb");
    if(pArchConsumo)
    {
        while(fread(&c,sizeof(stConsumo),1,pArchConsumo)> 0)
        {
            if(c.anio == a.anio && c.mes == a.mes && c.dia == a.dia && c.idCliente == a.idCliente)
            {
                c.datosConsumidos=a.datosConsumidos + c.datosConsumidos;
                modifRegistroCONSUMOS(c);
                flag=1;

            }

        }

        fclose(pArchConsumo);
    }
    return flag;
}

/*******************//**
* \brief Funcion que busca el mes que mas se consumio en el archivo
* \param None
* \return Retorna el mes de mayor consumo
**************************/
int buscarMesMAX()
{
    int mesMax=0;
    stConsumo a;
    FILE *pArchConsumo = fopen(AR_CONSUMOS,"rb");
    if(pArchConsumo)
    {
        while(fread(&a,sizeof(stConsumo),1,pArchConsumo)>0)
        {
            if(mesMax<a.mes)
            {
                mesMax++;
            }
        }
        fclose(pArchConsumo);
    }
    return mesMax;
}

/*******************//**
* \brief Funcion que carga una array con los meses de maximo consumo
* \param array, validos, mesMaximo
* \return Validos
**************************/
int cargarArreglo(int a[], int v, int mesMax)
{
    int suma;
    stConsumo c;
    FILE *pArchConsumo = fopen(AR_CONSUMOS,"rb");
    if(pArchConsumo)
    {
        while(v<mesMax)
        {
            while(fread(&c,sizeof(stConsumo),1,pArchConsumo)>0)
            {
                if(v==c.mes)
                {
                    suma=c.datosConsumidos+suma;
                    a[v]=suma;
                    v++;
                }
            }
        }

        fclose(pArchConsumo);
    }

    return v;
}

/*******************//**
* \brief Funcion que compara y retorna el mes mayor de un array
* \param int a[], int v
* \return mesMax
**************************/
int comprarMesMayor(int a[], int v)
{
    int mesMax=1;
    int i=mesMax + 1;
    while(i<v)
    {
        if(a[i]>a[mesMax])
        {
            mesMax=i;
        }
        i++;
    }
    return mesMax;
}

/****************************//**
* \brief Funcion que retorna la maxima cantidad de dias que tiene algun mes del anio (hasta mes 6)
* \param Recibe el mes
* \return Retorna la cantidad de dias de ese mes
********************************/
int diaMax (int mes)
{
    int dias; ///cantidad de dias que va a tener el mes
    if (mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12)
    {
        dias = 31;
    }
    else if (mes == 2)
    {
        dias = 28;
    }
    else if (mes == 4 || mes == 6 || mes == 9 || mes == 11)
    {
        dias= 30;
    }

    return dias;


}
/******************//**
* \brief Funcion que retorna un consumo aleatorio
* \param Recibe el id del cliente
* \return stConsumo cargado
******************************/
stConsumo ConsumoRandomID(int idCliente)
{
    stConsumo consumo;
    //stCliente cliente;
    //cliente = clienteRandom(); ///aca genero un cliente random
    consumo.idCliente = idCliente; ///le asigno a nuestro consumo random nuestro id random


    ///FUNCIONES DE TIEMPO
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int currentAnio;
    int currentDia;
    int currentMes;

    ///FECHA ACTUAL
    currentAnio = tm.tm_year + 1900;
    currentMes = tm.tm_mon +1;
    currentDia = tm.tm_mday;

    ///FECHAS RANDOM (aca las cargo)
    consumo.mes = randomRango(1,currentMes);
    consumo.dia = randomRango(1, diaMax(consumo.mes));
    consumo.anio = currentAnio;
    consumo.datosConsumidos = randomRango(1,500);
    consumo.baja=0;

    return consumo; ///retorno un consumo con datos al azar
}

