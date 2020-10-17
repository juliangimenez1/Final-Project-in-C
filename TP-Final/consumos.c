#include "consumos.h"
#include "clientes.h"
#include <stdio.h>
#include <time.h>
#include "utilidades.h"
#define AR_CLIENTES "clientes.dat"
#define AR_CONSUMOS "consumos.dat"
#define ESC 27
#define DIM_CLI 100


///GUARDA UN CONSUMO EN ARCHIVO
void guardarUnConsumo(stConsumo consumo)
{
    FILE *pArchConsumos=fopen(AR_CONSUMOS,"ab");
    if(pArchConsumos)
    {
        fwrite(&consumo,sizeof(stConsumo),1,pArchConsumos);
        fclose(pArchConsumos);
    }
}

/// CARGA UN CONSUMO, RETORNA EL CONSUMO
stConsumo cargaUnConsumo ()
{
    int dni =0;
    do
    {
        printf("Ingrese el DNI del cliente a cargar el consumo: ");
        scanf(" %d", &dni);
    }
    while(!validoDNI(dni));
    printf("\n");

    stCliente cliente = buscaClienteDNI(dni);
    stConsumo consumo;

    consumo.idCliente = cliente.id ;

    do
    {
        printf("Ingrese al anio.............: ");
        scanf(" %d", &consumo.anio);
    }
    while(consumo.anio < 1 || consumo.anio > 2050);

    do
    {
        printf("Ingrese el mes..............: ");
        scanf(" %d", &consumo.mes);
    }
    while(consumo.mes < 1 || consumo.mes > 12);

    printf("Ingrese el dia..............: ");
    scanf(" %d", &consumo.dia);
    do
    {
        printf("Ingrese el consumo 0/500....: ");
        scanf(" %d", &consumo.datosConsumidos);
    }
    while(consumo.datosConsumidos < 0 || consumo.datosConsumidos > 500);

    consumo.baja = 0;

    return consumo;
}

///BUSCA UN CLIENTE AL AZAR Y LO RETORNA
stCliente clienteRandom ()
{
    stCliente c;
    int id = randomRango(0,buscoUltimoID());
    int flag = 0;

    FILE *pArchClientes = fopen(AR_CLIENTES,"rb");
    if(pArchClientes)
    {
        while(flag == 0 && fread(&c,sizeof(stCliente),1,pArchClientes) > 0)
        {
            if(id== c.id)
            {
                flag = 1;
            }
        }
        fclose(pArchClientes);
    }
    return c;
}

///BUSCA EL ULTIMO ID DE CONSUMOS
int buscoUltimoIDConsumos()
{
    stConsumo c;
    int id=-1;
    FILE *pArchConsumos = fopen(AR_CONSUMOS,"rb");
    if(pArchConsumos)
    {
        fseek(pArchConsumos,sizeof(stConsumo)*(-1),SEEK_END);
        if(fread(&c,sizeof(stConsumo),1,pArchConsumos)>0)
        {
            id=c.id;
        }
        fclose(pArchConsumos);
    }
    return id;
}

///CARGA EL ARCHIVO CON UN CONSUMO
void cargaArchListaConsumos()
{
    stConsumo c;
    char opcion;
    while(opcion !=ESC)
    {

        c=cargaUnConsumo();
        c.id= buscoUltimoIDConsumos()+1;
        guardarUnConsumo(c);
        printf("ESC para salir \n");
        fflush(stdin);
        opcion = getch();
        system("cls");
    }
}
///MUESTRA UN CONSUMO, RECIBE EL CONSUMO
void muestraUnConsumo(stConsumo c)
{
    printf("------------------------------------\n");
    printf("Anio.................: %d\n", c.anio);
    printf("Mes..................: %d\n", c.mes);
    printf("Dia..................: %d \n", c.dia);
    printf("Consumos en MB.......: %d \n", c.datosConsumidos);
    printf("Baja s/n.............: %s \n\n", (c.baja)?"SI":"NO");

}

///MUESTRA TODOS LOS CONSUMOS
void mostrarArchConsumos()
{
    stConsumo c;
    FILE *pArchConsumos = fopen(AR_CONSUMOS,"rb");
    if(pArchConsumos)
    {
        while(fread(&c,sizeof(stConsumo),1,pArchConsumos)>0)
        {
            muestraUnConsumo(c);
        }
        fclose(pArchConsumos);
    }
}

/****************************************
MODIFICA LOS DATOS CONSUMIDOS DE CONSUMO.
BUSCO X DNI AL CLIENTE, BUSCO FECHA DE CONSUMO Y MODIFICO.
****************************************/
void modificacionConsumo()
{
    stCliente c;
    stConsumo a;
    int dni;
    int anio;
    int mes;
    int dia;
    printf("Ingrese el a%co.....: ", 164);
    scanf("%d",&anio);
    printf("Ingrese el el mes...: ");
    scanf("%d",&mes);
    printf("Ingrese el dia......: ");
    scanf("%d",&dia);
    system("cls");
    printf("Ingrese el DNI del cliente: ");
    scanf("%d",&dni);
    system("cls");
    c=buscaClienteDNI(dni);
    a=buscaxIDConsumo(c.id,anio,mes,dia);
    muestraUnConsumo(a);
    if(a.idCliente!=-1)
    {
        printf("\n\nUsted busco el cliente: %s\n\n",c.apellido);
        system("pause");
        system("cls");
        modificarConsumo(a);
    }
    else
    {
        printf("No se ha encontrado ningun cliente con el DNI ingresado...\n\n");
    }
}
/****************************************
MENU DE LA MODIFICACION DE CONSUMO.
****************************************/
void menuModificacionConsumo()
{
    printf("\t\t MODIFICACION CONSUMOS.");
    printf("\n\n");
    printf("1-Modificar consumo.\n\n");
    printf("2-GUARDAR MODIFICACION.");
    printf("\n\n");
    printf("ESC para salir...");
}

/****************************************
MODIFICO CONSUMO, RECIBO UN CONSUMO A.
OPCIONES 1: MODIFICO DATO CONSUMIDO.
OPCION 2: GUARDO MODIFICACION EN ARCHIVO.
****************************************/
void modificarConsumo(stConsumo a)
{

    char opcion;
    do
    {
        system("cls");
        menuModificacionConsumo();
        opcion=getch();
        system("cls");
        switch(opcion)
        {
        case '1':
            ///a=cambiarConsumo(a);
            printf("Ingrese los MB nuevos: ");
            scanf("%d",&a.datosConsumidos);
            break;
        case '2':
            modifRegistroCONSUMOS(a);
            system("pause");
            break;
        }
    }
    while(opcion!=ESC);


}
/****************************************
CAMBIO CONSUMO, RECIBO CONSUMO A.
CAMBIO DATOS CONUMIDOS.
RETORNO EL CONSUMO.
****************************************/
stConsumo cambiarConsumo(stConsumo a)
{

    if(a.idCliente!= -1)
    {
        printf("Ingrese el nuevo consumo: \n\n");
        scanf("%d", &a.datosConsumidos);
        system("pause");
    }
    else
    {
        printf("No se ha encontrado una fecha en los consumos.\n\n");
        system("pause");
    }

    return a;
}
/****************************************
MODIFICO CONSUMO, RECIBO EL CONSUMO MODIFICADO.
GUARDO EN EL ARCHIVO DE LA MISMA POSICION.
****************************************/
void modifRegistroCONSUMOS(stConsumo c)
{
    int pos;
    pos = buscaPosicionCONSUMO(c.id);
    FILE *pArchConsumo = fopen(AR_CONSUMOS, "r+b");
    if(pArchConsumo)
    {
        fseek(pArchConsumo, sizeof(stConsumo)*pos, SEEK_SET); /// depende de lo que retorne buscaPosicion()
        fwrite(&c, sizeof(stConsumo), 1, pArchConsumo);
        fclose(pArchConsumo);
    }
}
/****************************************
BUSCO LA POSICION EN ARCHIVO CONSUMO.
RECIBO UNA ID.
LO BUSCO Y RETORNO POSICION.
SI NO EXISTE RETORNO -1.
****************************************/
int buscaPosicionCONSUMO(int id)
{
    int pos=-1;
    stConsumo c;
    FILE *pArchConsumo = fopen(AR_CONSUMOS,"rb");
    if(pArchConsumo)
    {
        while(pos == -1 && fread(&c, sizeof(stConsumo), 1, pArchConsumo) > 0)
        {
            if(c.id == id)
            {
                pos = ftell(pArchConsumo)/sizeof(stConsumo)-1;
            }
        }
        fclose(pArchConsumo);
    }

    return pos;
}

/****************************************
BUSCO ID EN EL CONSUMO.
RECIBO EL ID, Y LA FECHA DEL CONSUMO.
RETORNO EL CONSUMO... LA POSICION SI EXISTE.
Y -1 SI NO EXISTE.
****************************************/
stConsumo buscaxIDConsumo(int id, int anio, int mes, int dia)
{
    stConsumo a;
    int flag=0;
    FILE *pArchConsumo = fopen(AR_CONSUMOS,"rb");
    if(pArchConsumo)
    {
        while(flag ==0 && fread(&a,sizeof(stConsumo),1,pArchConsumo)>0)
        {
            if(a.idCliente == id && a.anio==anio && a.mes==mes && a.dia==dia)
            {
                flag=1;
            }
        }
        fclose(pArchConsumo);
    }
    if(flag == 0)
    {
        a.idCliente = -1;
    }
    return a;
}

void modificoBajaConsumo()
{
    stCliente cliente;
    stConsumo consumo;
    int dni = 0;
    int baja = 0;
    int anio, mes, dia;
    int flag = 0;

    ///le pide al usuario que ingrese la fecha en la cual se quiere dar de baja
    printf("Ingrese a%co.....: ", 164);
    scanf("%d", &anio);
    printf("Ingrese mes.....: ");
    scanf("%d", &mes);
    printf("Ingrese dia.....: ");
    scanf("%d", &dia);
    system("cls");

    printf("Ingrese el DNI: ");///pide el DNI
    scanf("%d", &dni);

    cliente = buscaClienteDNI(dni);///busca el cliente por dni y lo retorna
    consumo = buscaxIDConsumo(cliente.id, anio, mes, dia);///busca el consumo relacionado al cliente que reotorna la funcion anterior

    if(cliente.nroCliente != -1)///si se retorna el cliente deseado se muestra el nombre y el apellido
    {
        printf("\nUsted busco a: %s %s \n\n",cliente.nombre, cliente.apellido);

    }
    else///si no existe se muestra este mensaje
    {
        printf("El cliente no existe\n\n");
    }

    if(consumo.idCliente != -1)///se corrobora que exista el consumo
    {
        do
        {
            printf("Ingrese 1 para dar de baja o 0 para dar de alta: ");///se pide si se quiere dar de alta o de baja
            scanf("%d", &baja);
            consumo.baja = baja;///se iguala la baja requerida a la baja del consumo
        }
        while(baja < 0 || baja > 1);
    }
    else
    {
        printf("\nLa fecha no existe...\n\n");
    }

    modifRegistroCONSUMOS(consumo);///se modifica el regsitro

}

void buscarConsumoFecha(int anio, int mes, int dia)
{
    stConsumo a;
    FILE *pArchConsumo= fopen(AR_CONSUMOS,"rb");
    if(pArchConsumo)
    {
        while(fread(&a,sizeof(stConsumo),1,pArchConsumo)> 0)
        {
            if(a.anio == anio && a.mes == mes && a.dia == dia)
            {
                muestraUnConsumo(a);
            }
        }
        fclose(pArchConsumo);
    }
}
void preguntaFechaConsumo()
{
    int anio;
    int mes;
    int dia;
    printf("Ingrese el anio.....: ");
    scanf("%d",&anio);
    printf("Ingrese el el mes...: ");
    scanf("%d",&mes);
    printf("Ingrese el dia......: ");
    scanf("%d",&dia);
    system("cls");
    buscarConsumoFecha(anio,mes,dia);
}
/**
* \brief Funcion que retorna la maxima cantidad de dias que tiene algun mes del anio (hasta mes 6)
* \param Recibe el mes
* \return Retorna la cantidad de dias de ese mes
**/
int diaMax (int mes)
{
    int dias; ///cantidad de dias que va a tener el mes
    if (mes == 1 || mes == 3 || mes == 5)
    {
        dias = 31;
    }
    else if (mes == 2)
    {
        dias = 28;
    }
    else if (mes == 4 || mes == 6)
    {
        dias= 30;
    }

    return dias;


}


stConsumo ConsumoRandom()
{
    stConsumo consumo;
    stCliente cliente;
    cliente = clienteRandom(); ///aca genero un cliente random
    consumo.idCliente = cliente.id; ///le asigno a nuestro consumo random nuestro id random

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
    consumo.datosConsumidos = randomRango(1,50);
    consumo.baja=0;

    return consumo; ///retorno un consumo con datos al azar
}

void CargaUnConsmoRandom()
{
    stConsumo c;
    stConsumo b;
    int flag;
    for (int i=0; i<1000 ; i++)
    {
        c = ConsumoRandom();
        c.id = buscoUltimoIDConsumos()+1;
        flag=verficaFecha(c);
        if(flag!=1)
        {
            guardarUnConsumo(c);
        }
    }

}
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

void mostrarArreglo(int a[], int v)
{
    int mes = 1;
    for(int i=1; i<v; i++)
    {
        printf("Mes %d se consumieron %d MB \n\n",mes,a[i]);
        mes++;
    }
    printf("\n\n");
}
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
