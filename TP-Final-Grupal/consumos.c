#include "consumos.h"
/*
#include "clientes.h"
#include <stdio.h>
#include <time.h>
#include "utilidades.h"
#define AR_CLIENTES "clientes.dat"
#define AR_CONSUMOS "consumos.dat"
#define ESC 27
#define DIM_CLI 100
*/


/*******************//**
* \brief Funcion que guarda un consumo en el archivo de consumos
* \param Recibe un consumo
* \return Void
**************************/
void guardarUnConsumo(stConsumo consumo)
{
    FILE *pArchConsumos=fopen(AR_CONSUMOS,"ab");
    if(pArchConsumos)
    {
        fwrite(&consumo,sizeof(stConsumo),1,pArchConsumos);
        fclose(pArchConsumos);
    }
}

/*******************//**
* \brief Funcion que completa los campos de un stConsumo validando los mismos y lo retorna cargado
* \param None
* \return retorna el Consumo
**************************/
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



/*******************//**
* \brief Funcion que retorna el ultimo ID de los consumos
* \param None
* \return retorna el utimo ID. Si no encuentra, retorna id en -1
**************************/
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

/*******************//**
* \brief Funcion de carga del archivo de consumos
* \param None
* \return Void
**************************/
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

/*******************//**
* \brief Funcion para mostrar un solo consumo
* \param stConsumo c
* \return Void
**************************/
void muestraUnConsumo(stConsumo c)
{
    printf("------------------------------------\n");
    printf("Anio.................: %d\n", c.anio);
    printf("Mes..................: %d\n", c.mes);
    printf("Dia..................: %d \n", c.dia);
    printf("Consumos en MB.......: %d \n", c.datosConsumidos);
    printf("ID cliente: %d \n", c.idCliente);
    printf("Baja s/n.............: %s \n\n", (c.baja)?"SI":"NO");

}

/*******************//**
* \brief Funcion que muestra todos los consumos de un archivo
* \param None
* \return Void
**************************/
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

/*******************//**
* \brief Funcion que busca un cliente por DNI, pide Fecha exacta de un consumo, y si encuentra lo modifica
* \param None
* \return Void
**************************/
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

/*******************//**
* \brief Funcion que modifica consumos del archivo de consumos
* \param Recibe el consumo cargado
* \return Void
**************************/
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
/*******************//**
* \brief Funcion que recibe un consumo y lo modifica
* \param stConsumo a (el consumo a modificar)
* \return Retorna el consumo nuevo
**************************/
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
/*******************//**
* \brief Funcio para guardar un consumo modificado en el archivo de consumos
* \param Recibo el consumo
* \return Void
**************************/
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
/*******************//**
* \brief Funcion que busca a posicion de un consumo por ID en el archivo de consumos
* \param Recibo el ID de consumo
* \return Retorno en bytes la posicion del consumo. Retorna -1 si no fue encontrado
**************************/
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

/*******************//**
* \brief Funcion que busca un consumo en el archivo por ID de cliente, anio, mes y dia
* \param int id, int anio, int mes, int dia
* \return Retorna el consumo. Si no lo encuentra retorna el consumo con id -1
**************************/
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

/*******************//**
* \brief Funcion que da de baja un consumo buscado por Fecha y DNI del usuario
* \param None
* \return Void
**************************/
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

/*******************//**
* \brief Funcion que busca un consumo en una fecha exacta
* \param int anio, int mes, int dia
* \return Void
**************************/
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

/*******************//**
* \brief Funcion que pregunta y muestra un consumo en una fecha exacta
* \param None
* \return Void
**************************/
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



