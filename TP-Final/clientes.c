#include "clientes.h"
#include "utilidades.h"
#include <stdio.h>
#define AR_CLIENTES "clientes.dat"
#define AR_CONSUMOS "consumos.dat"
#define ESC 27
#define DIM_CLI 100

/**********************************************
FUNCION TIPO CLIENTE CARGA UNA ESTRUCTURA.
NO RECIBO NADA.
CREO ESTRUCTURA, LA CARGO.
RETORNO ESTRUCTURA CLIENTE.
**********************************************/
stCliente cargaUnCliente ()
{
    stCliente c;

    do
    {
        printf("\nIngrese el numero de cliente.......: ");
        scanf("%d", &c.nroCliente);
    }
    while(c.nroCliente<0 && c.nroCliente < 99999 || validoNroCliente(c.nroCliente));

    printf("Ingrese el nombre..................: ");
    fflush(stdin);
    gets(c.nombre);
    printf("Ingrese el apellido................: ");
    fflush(stdin);
    gets(c.apellido);

    do
    {
        printf("Ingrese el DNI.....................: ");
        scanf("%d", &c.dni);
    }
    while(validoDNI(c.dni));

    do
    {
        printf("Ingrese el email...................: ");
        fflush(stdin);
        gets(c.email);
    }
    while(!validaEmail(c.email));

    printf("Ingrese el domicilio...............: ");
    fflush(stdin);
    gets(c.domicilio);

    printf("Ingrese el numero de celular.......: ");
    fflush(stdin);
    gets(c.movil);

    c.baja=0;




    return c;
}


/**********************************************
FUNCION CARGAR UN ARREGLO TIPO INT.
RECIBO EL ARREGLO, LOS VALIDOS, Y LA DIMENSION.
CARGO EL ARREGLO Y EL ID DE CADA POSICION.
RETORNO LOS VALIDOS.
**********************************************/
int cargarListaClientes(stCliente c[], int v, int dim)
{
    char opcion;
    while(v<dim && opcion!=ESC)
    {

        system("cls");
        c[v]=cargaUnCliente();
        c[v].id=v;
        v++;
        opcion=getch();
        printf("\n\nESC para salir...");

    }
    return v;
}
/**********************************************
GUARDAR UN CLIENTE EN UN ARCHIVO.
RECIBO EL CLIENTE(ESTRUCTURA), ABRO ARCHIVO
LO GUARDO Y LO CIERRO.
**********************************************/
void guardarUnCliente(stCliente c)
{
    FILE *pArchClientes=fopen(AR_CLIENTES,"ab");
    if(pArchClientes)
    {
        fwrite(&c,sizeof(stCliente),1,pArchClientes);
        fclose(pArchClientes);
    }
}
/**********************************************
CARGAR EN EL ARCHIVO UNA LISTA DE CLIENTES.
CREO UNA ESTRUCTURA Y LA METO EN UN BUCLE DE
CARGA.
**********************************************/
void cargarArchListaClientes()
{
    stCliente c;
    char opcion;
    while(opcion !=ESC)
    {
        printf("Ingrese sus datos: \n\n");
        c=cargaUnCliente();
        c.id=buscoUltimoID()+1;
        guardarUnCliente(c);
        printf("\n\nESC para salir...");
        fflush(stdin);
        opcion=getch();
        system("cls");
    }
}
/**********************************************
FUNCION QUE BUSCA EL ULTIMO ID EN EL ARCHIVO.
TIPO INT.
RECORRO EL CURSOR PARA BUSCAR EL ULTIMO ID.
RETORNO LA ULTIMA POSICION.
**********************************************/
int buscoUltimoID()
{
    stCliente c;
    int id=-1;
    FILE *pArchClientes = fopen(AR_CLIENTES,"rb");
    if(pArchClientes)
    {
        fseek(pArchClientes,sizeof(stCliente)*(-1),SEEK_END);
        if(fread(&c,sizeof(stCliente),1,pArchClientes)>0)
        {
            id=c.id;
        }
        fclose(pArchClientes);
    }
    return id;
}
/**********************************************
MUESTRO UN CLIENTE.
**********************************************/
void muestraUnCliente(stCliente c)
{
    printf("------------------------------------");
    printf("\nNumero de Cliente........: %d\n", c.nroCliente);
    printf("Nombre...................: %s\n", c.nombre);
    printf("Apellido.................: %s\n", c.apellido);
    printf("D.N.I....................: %d \n", c.dni);
    printf("Email....................: %s \n", c.email);
    printf("Telefono.................: %s \n", c.movil);
    printf("Domicilio................: %s\n", c.domicilio);
    printf("Baja s/n.................: %s \n", (c.baja)?"SI":"NO");
}
/**********************************************
MOSTRAR ARCHIVO DE CLIENTES.
**********************************************/
void mostrarArchClientes()
{
    stCliente c;
    FILE *pArchClientes = fopen(AR_CLIENTES,"rb");
    if(pArchClientes)
    {
        while(fread(&c,sizeof(stCliente),1,pArchClientes)>0)
        {
            muestraUnCliente(c);
        }
        fclose(pArchClientes);
    }
}

/**********************************************
FUNCION TIPO CLIENTE QUE BUSCA POR NRO DE CLIENTE
RECIBO EL NUMERO DE CLIENTE, ABRO EL ARCHIVO Y
COMPARO.
SI LO ENCUENTRO RETORNO EL CLIENTE.
**********************************************/
stCliente buscaClienteArchxNroCliente(int nroCliente)
{
    stCliente c;
    int flag=0;
    FILE *pArchClientes = fopen(AR_CLIENTES,"rb");
    if(pArchClientes)
    {
        while(flag==0 && fread(&c,sizeof(stCliente),1,pArchClientes)>0)
        {
            if(nroCliente == c.nroCliente)
            {
                flag=1;
            }
        }

        fclose(pArchClientes);
    }
    if(flag== 0)
    {
        c.id=-1;
    }
    return c;
}
/**********************************************
FUNCION DONDE SE BUSCA AL CLIENTE Y LO MUESTRA.
**********************************************/
void encontrarClienteArch()
{

    int nroCliente;
    stCliente c;
    printf("Ingrese el numero de cliente que desea modificar: ");
    scanf("%d", &nroCliente);
    system("cls");
    c=buscaClienteArchxNroCliente(nroCliente);
    if(c.id!=-1)
    {
        muestraUnCliente(c);
        system("pause");
        modificarClienteArch(c);
    }
    else
    {
        printf("No se ha encontrado el apellido en la lista.\n\n");
    }
}

/**********************************************
MODIFICAR UN CLIENTE DEL ARCHIVO.
RECIBO UN CLIENTE, LO MODIFICO.
**********************************************/
void modificarClienteArch(stCliente c)
{
    char opcion;
    do
    {
        system("cls");
        menuModificacionDatos();
        fflush(stdin);
        opcion=getch();
        system("cls");

        switch(opcion)
        {
        case '1':
            do
            {
                printf("\n Ingrese el nuevo numero de cliente: ");
                scanf("%d", &c.nroCliente);
            }
            while(c.nroCliente<0 || c.nroCliente>9999 || validoNroCliente(c.nroCliente));
            system("pause");
            break;
        case '2':
            printf("Ingrese el nuevo nombre de el cliente: ");
            fflush(stdin);
            gets(c.nombre);
            system("pause");
            break;
        case '3':
            printf("Ingrese el nuevo apellido de el cliente: ");
            fflush(stdin);
            gets(c.apellido);
            system("pause");
            break;
        case '4':
            do
            {
                printf("Ingrese el nuevo DNI del cliente: ");
                scanf("%d", &c.dni);
            }
            while(validoDNI(c.dni));
            break;
        case '5':
            do
            {
                printf("Ingrese el nuevo EMail de el cliente: ");
                fflush(stdin);
                gets(c.email);
            }
            while(!validaEmail(c.email));
            system("pause");
            break;
        case '7':
            printf("Ingrese el nuevo Domicilio de el cliente: ");
            fflush(stdin);
            gets(c.domicilio);
            system("pause");
            break;
        case '6':
            printf("Ingrese el nuevo Numero de celular de el cliente: ");
            scanf(" %d", &c.movil);
            system("pause");
            break;

        case '9':
            modifRegistro(c);
            printf("Cliente guardado...\n\n");
            system("pause");
            break;
        }
    }
    while(opcion!=ESC);
}


/**********************************************
BUSCO LA POSICION DE UN CLIENTE.
RECIBO LA ID ABRO ARCHIVO Y COMPARO.
RETORNO LA POSICION.
**********************************************/
int buscaPosicion(int id)
{
    int pos=-1;
    stCliente c;
    FILE *pArchClientes = fopen(AR_CLIENTES,"rb");
    if(pArchClientes)
    {
        while(pos == -1 && fread(&c, sizeof(stCliente), 1, pArchClientes) > 0)
        {
            if(c.id == id)
            {
                pos = ftell(pArchClientes)/sizeof(stCliente)-1;
            }
        }
        fclose(pArchClientes);
    }

    return pos;
}
/**********************************************
MODIFICO EL REGSITRO DE UN CLIENTE EN ARCHIVO.
RECIBO UN CLIENTE MODIFICADO Y LO GUARDO POR SU
ID.
**********************************************/
void modifRegistro(stCliente c)
{
    int pos;
    pos = buscaPosicion(c.id);
    FILE *pArchClientes = fopen(AR_CLIENTES, "r+b");
    if(pArchClientes)
    {
        fseek(pArchClientes, sizeof(stCliente)*pos, SEEK_SET); /// depende de lo que retorne buscaPosicion()
        fwrite(&c, sizeof(stCliente), 1, pArchClientes);
        fclose(pArchClientes);
    }
}

void funcion05()
{
    int DNI = 0;
    int dato=0;
    stCliente c;
    printf("Dar de baja un cliente \n\n");
    printf("Ingrese el DNI del cliente: ");
    scanf("%d", &DNI);
    printf("\n\nIngrese 1 para baja y 0 para alta: ");


    c = buscaPosicionDNI(DNI);
    scanf(" %d", &c.baja);
    if(c.id == -1)
    {
        printf("\nEl cliente no existe, ingrese un DNI valido: ");
    }
    else
    {
        modifRegistro(c);
    }

}
stCliente buscaPosicionDNI(int dni)
{

    stCliente c;
    int flag = 0;

    FILE *pArchClientes = fopen(AR_CLIENTES,"rb"); ///abrimos archivo
    if(pArchClientes)
    {
        while(flag == 0 && fread(&c, sizeof(stCliente), 1, pArchClientes) > 0) ///recorremos archivo si flag esta en 0
        {
            if(c.dni == dni) ///si hay coincidencia del dni del parametro con dni de archivo flag pasa a valer 1 y se corta el ciclo
            {
                flag = 1;
            }
        }
        fclose(pArchClientes); ///cerramos archivo

    }
    if(flag == 0) ///si no se econtro el dni, retornamos el cliente con id -1
    {
        c.id=-1;
    }
    return c; ///retornamos el cliente
}
int validoDNI(int dni)
{
    int flag = 0;///declaro una bandera
    stCliente c;

    FILE *pArchCliente = fopen(AR_CLIENTES, "rb");///abro el arcchivo

    if(pArchCliente)
    {
        while(flag == 0 && fread(&c, sizeof(stCliente), 1, pArchCliente) > 0)///recorro todo el archivo
        {
            if(dni == c.dni)///comparo el numero de dni recibido con los del resto del archivo
            {
                flag = 1;///si se encuentra uno igual el flag lo iguala a 0
            }
        }
    }

    return flag;///si retorna 0 es que es valido si retorna 1 no es valido
}
int validoNroCliente(int nro)
{
    int flag = 0;///decalro una bandera
    stCliente c;

    FILE *pArchCliente = fopen(AR_CLIENTES, "rb");///abro el archivo

    if(pArchCliente)
    {
        while(flag == 0 && fread(&c, sizeof(stCliente), 1, pArchCliente) > 0)///recorro todo el archivo
        {
            if(nro == c.nroCliente)///comparo el dni recibido con cada uno de los que estan en el archivo
            {
                flag = 1;///si existe otro igual retorna 1
            }
        }
    }

    return flag;///si retorna 0 es que es valido si retorna 1 no es valido
}

///*********************************************************************************///
///FUNCIONES DE LISTADO DE ACTIVOS
///*********************************************************************************///


int archivoAArregloAltas(stCliente a[], int dim)
{
    int v = 0;///creo los validos del arreglo recibido
    stCliente c;

    FILE *pArchCliente = fopen(AR_CLIENTES, "rb");///abro el archivo en modo lectura

    if(pArchCliente)
    {
        while(fread(&c, sizeof(stCliente),1, pArchCliente) > 0)///recorro todo el archivo
        {
            if((c.baja == 0) && v<dim)///controlo que el archivo no tenga mas datos de los que soporta el arreglo
            {
                a[v] = c;///igualo el dato de ese archivo al arreglo en su posicion correspondiente
                v++;///incremento su posicion
            }

        }

        fclose(pArchCliente);///cierro el archivo
    }

    return v;///retorno los validos
}

int buscaMenorDNIArreglo(int v, stCliente a[], int pos)
{
    int posmenor = pos;///toma como posicion menor el valor de pos
    int i = pos + 1;///al arreglo se empieza a recorrer una posicion mas adelante que posmenos

    while(i<v)///se recorre todo el arreglo

    {
        if(a[i].dni < a[posmenor].dni)///compara el valor de i con el de posmenor
        {
            posmenor = i;///si es menor posmenor toma el valor de i
        }
        i++;
    }

    return posmenor;///retorna el valor de la posicion menor
}
///recibe los validos y el array de alumnos
void ordenamientoSeleccionAregloDNI(int v, stCliente a[])
{
    int posmenor = 0;///recibe lo que retorna la busqueda de la posicion menor
    int i = 0;

    while(i<v)///recorre todo el arreglo
    {
        posmenor = buscaMenorDNIArreglo(v, a, i);///posmenor almacena lo que retorna la funcion aneterior

        intercambio(&a[i], &a[posmenor]);

        i++;
    }

}

void ordenacionSeleccionArchivoDNI()
{
    stCliente ordenacion[DIM_CLI];///este arreglo almacena los clientes del archivo para luego ser ordenado
    int vOrdenacion = 0;

    vOrdenacion = archivoAArregloAltas(ordenacion, DIM_CLI);///paso el archivo al arreglo

    ordenamientoSeleccionAregloDNI(vOrdenacion, ordenacion);///ordeno el arreglo

    muestraArreglo(vOrdenacion, ordenacion);

}

///funcion que busca el menor apellido dentro de un arreglo de stcliente

int buscaMenorApellidoArreglo(int v, stCliente a[], int pos)
{
    int posmenor = pos;///toma como posicion menor el valor de pos
    int i = pos + 1;///al arreglo se empieza a recorrer una posicion mas adelante que posmenos


    while(i<v)///se recorre todo el arreglo
    {
        ///res = strcmpi(a[i], a[posmenor]);
        if(strcmpi(a[i].apellido, a[posmenor].apellido) < 0)///compara el valor de i con el de posmenor
        {
            posmenor = i;///si es menor posmenor toma el valor de i
        }
        i++;
    }

    return posmenor;///retorna el valor de la posicion menor
}

///ordenamiento por selleccion por apellido
///recibe los validos y el array de alumnos
void ordenamientoSeleccionAregloApellido(int v, stCliente a[])
{
    int posmenor = 0;///recibe lo que retorna la busqueda de la posicion menor
    int i = 0;

    while(i<v)///recorre todo el arreglo
    {
        posmenor = buscaMenorApellidoArreglo(v, a, i);///posmenor almacena lo que retorna la funcion aneterior

        intercambio(&a[i], &a[posmenor]);

        i++;
    }

}

///ordena el archivo por apellido
/// FUNCION DE LLAMADA DESDE EL MAIN
void ordenacionSeleccionArchivoApellido()
{
    stCliente ordenacion[DIM_CLI];///este arreglo almacena los clientes del archivo para luego ser ordenado
    int vOrdenacion = 0;

    vOrdenacion = archivoAArregloAltas(ordenacion, DIM_CLI);///paso el archivo al arreglo

    ordenamientoSeleccionAregloApellido(vOrdenacion, ordenacion);///ordeno el arreglo

    muestraArreglo(vOrdenacion, ordenacion);

}

///busco y retorno cliente por numero de documento

stCliente buscaClienteDNI(int dni)
{
    stCliente c;
    int flag = 0;///creo una bandera que me sirva de corte para el while
    FILE *pArchCliente = fopen(AR_CLIENTES, "rb");///abro el archivo

    if(pArchCliente)
    {
        while(flag == 0 && fread(&c, sizeof(stCliente), 1, pArchCliente) > 0)///lo recorro
        {
            if(c.dni == dni)///compruebo si son iguales los numeros de dni
            {
                flag = 1;///pongo flag en uno para que no entre mas al while
            }
            else
            {
                c.id = -1;///si no existe un dni igual le asigno a nro de cliente -1
            }
        }
        fclose(pArchCliente);///cierro el archivo
    }


    return c;///retorno el cliente
}

///muestra el cliente que se deseo buscar

void muestraBuscaCliente()
{
    int dni;
    stCliente c;
    printf("Ingrese DNI para buscar: ");///le pido al usuario que ingrese el dni para buscarlo
    scanf("%d", &dni);

    c = buscaClienteDNI(dni);///igualo lo que retorna la funcion a c

    if(c.id == -1)///si el numero de cliente es -1 el cliente no existe
    {
        printf("\nEl cliente no existe...\n\n");
    }
    else
    {
        printf("\nEste es el cliente: \n\n");///si no se muestra los datos el cliente
        muestraUnCliente(c);
    }

}

/******************************************
ORDENAMIENTOS DE LOS CLIENTES DADOS DE
BAJA. ORDENADOS POR EMAIL (DRLRCCION)
******************************************/

///paso un archivo a un arreglo con filtro

int archivoAArregloBajas(stCliente a[], int dim)
{
    int v = 0;///creo los validos del arreglo recibido
    stCliente c;

    FILE *pArchCliente = fopen(AR_CLIENTES, "rb");///abro el archivo en modo lectura

    if(pArchCliente)
    {
        while(fread(&c, sizeof(stCliente),1, pArchCliente) > 0)///recorro todo el archivo
        {
            if((c.baja == 1) && v<dim)///controlo que el archivo no tenga mas datos de los que soporta el arreglo
            {
                a[v] = c;///igualo el dato de ese archivo al arreglo en su posicion correspondiente
                v++;///incremento su posicion
            }
        }

        fclose(pArchCliente);///cierro el archivo
    }

    return v;///retorno los validos
}

///funcion que busca el menor email dentro de un arreglo de stcliente (dados de baja)

int buscaMenorEmailArreglo(int v, stCliente a[], int pos)
{
    int posmenor = pos;///toma como posicion menor el valor de pos
    int i = pos + 1;///al arreglo se empieza a recorrer una posicion mas adelante que posmenos


    while(i<v)///se recorre todo el arreglo
    {
        ///res = strcmpi(a[i], a[posmenor]);
        if(strcmpi(a[i].email, a[posmenor].email) < 0)///compara el valor de i con el de posmenor
        {
            posmenor = i;///si es menor posmenor toma el valor de i
        }
        i++;
    }

    return posmenor;///retorna el valor de la posicion menor
}

///ordenamiento por selleccion por email dados de baja
///recibe los validos y el array de alumnos
void ordenamientoSeleccionAregloEmail(int v, stCliente a[])
{
    int posmenor = 0;///recibe lo que retorna la busqueda de la posicion menor
    int i = 0;

    while(i<v)///recorre todo el arreglo
    {
        posmenor = buscaMenorEmailArreglo(v, a, i);///posmenor almacena lo que retorna la funcion aneterior

        intercambio(&a[i], &a[posmenor]);

        i++;
    }

}

///ordena el archivo por email a los que estan dados de baja

void ordenacionSeleccionArchivoEmail()
{
    stCliente ordenacion[DIM_CLI];///este arreglo almacena los clientes del archivo para luego ser ordenado
    int vOrdenacion = 0;

    vOrdenacion = archivoAArregloBajas(ordenacion, DIM_CLI);///paso el archivo al arreglo

    ordenamientoSeleccionAregloEmail(vOrdenacion, ordenacion);///ordeno el arreglo

    muestraArreglo(vOrdenacion, ordenacion);///muestra el arrreglo ya ordenado

}
