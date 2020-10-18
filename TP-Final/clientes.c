#include "clientes.h"
#include "utilidades.h"
#include <stdio.h>
#define AR_CLIENTES "clientes.dat"
#define AR_CONSUMOS "consumos.dat"
#define ESC 27
#define DIM_CLI 100


/*******************//**
* \brief Funcion que carga un dato de tipo stCliente
* \param No recibe nada
* \return Retorna un cliente cargado
**************************/
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


/*******************//**
* \brief Funcion que carga un array de clientes
* \param stCliente c [], int v, int dim
* \return Retorna los validos
**************************/
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
/*******************//**
* \brief Funcion que guarda un cliente en el archivo de clientes
* \param stCliente c
* \return No retorna nada
**************************/
void guardarUnCliente(stCliente c)
{
    FILE *pArchClientes=fopen(AR_CLIENTES,"ab");
    if(pArchClientes)
    {
        fwrite(&c,sizeof(stCliente),1,pArchClientes);
        fclose(pArchClientes);
    }
}
/*******************//**
* \brief Funcion que carga un archivo de Clientes (mas de uno)
* \param None
* \return Void
**************************/
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
/*******************//**
* \brief Funcion que recorre el archivo de clientes y busca el ultimo ID
* \param None
* \return Retorna el ultimo ID, si no hay retorna -1
**************************/
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

/*******************//**
* \brief Funcion que busca en el archivo un cliente por su numero de cliente
* \param int nroCliente
* \return Retorna el cliente, si no existe retorna con el id en -1q
**************************/
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
/*******************//**
* \brief Funcion que busca al cliente por numero de cliente y lo modifica
* \param None
* \return Void
**************************/
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
        printf("No se ha encontrado al cliente en la lista.\n\n");
    }
}

/*******************//**
* \brief Funcion que recibe un cliente y lo modifica & guarda en archivo
* \param Recibe el cliente
* \return Void
**************************/
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

/*******************//**
* \brief Funcion que busca la posicion en archivo de un cliente por ID
* \param int id
* \return posicion en peso en bytes del cliente. Si no se encuentra retorna -1
**************************/
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

/*******************//**
* \brief Funcion que sobreescribe un cliente en el archivo (cuando lo modificamos)
* \param Recibe el cliente
* \return Void
**************************/
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

/*******************//**
* \brief Funcion auxiliar para dar de baja/alta un cliente
* \param None
* \return Void
**************************/
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
/*******************//**
* \brief Funcion que busca la posicion de un cliente por DNI
* \param Recibe el DNI (int)
* \return Retorna el cliente buscado. Si no se encuentra retorna id en -1
**************************/
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

/*******************//**
* \brief Funcion que valida en la carga el DNI
* \param Recibe el DNI
* \return 1 si ya se encuentra en uso el DNI, 0 si no lo esta
**************************/
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
                flag = 1;///si se encuentra uno igual el flag lo iguala a 1
            }
        }
    }

    return flag;///si retorna 0 es que es valido si retorna 1 no es valido
}

/*******************//**
* \brief Fucion que valida en la carga el Nro de cliente
* \param Recibe el numero (int)
* \return  1 si lo encontro, 0 si no esta en uso
**************************/
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

/*******************//**
* \brief Funcion que pasa del archivo de clientes a un Array
* \param stCliente a[], int dim
* \return Validos del array
**************************/
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

/*******************//**
* \brief Funcion que busca el cliente con menor DNI del arreglo
* \param Validos, Arreglo de clientes, posicion de inicio
* \return La posicion del menor DNI
**************************/
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

/*******************//**
* \brief Funcion de ordenamiento por seleccion de array por DNI
* \param Validos, Array
* \return Void
**************************/
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

/*******************//**
* \brief Funcion que ordena por seleccion (DNI) tomando los datos de un archivo y pasandolos a un array
* \param None
* \return Void
**************************/
void ordenacionSeleccionArchivoDNI()
{
    stCliente ordenacion[DIM_CLI];///este arreglo almacena los clientes del archivo para luego ser ordenado
    int vOrdenacion = 0;

    vOrdenacion = archivoAArregloAltas(ordenacion, DIM_CLI);///paso el archivo al arreglo

    ordenamientoSeleccionAregloDNI(vOrdenacion, ordenacion);///ordeno el arreglo

    muestraArreglo(vOrdenacion, ordenacion);

}

/*******************//**
* \brief Funcion que busca el menor apellido de un arreglo
* \param Validos, array, posicion de inicio
* \return Posicion del menor apellido
**************************/
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

/*******************//**
* \brief Funcion de ordenamiento por seleccion de apellido de un arreglo
* \param Validos, arreglo
* \return Void
**************************/
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

/*******************//**
* \brief Funcion de ordenamiento por Seleccion del archivo por apellido (pasa los datos a un array)
* \param None
* \return Void
**************************/
void ordenacionSeleccionArchivoApellido()
{
    stCliente ordenacion[DIM_CLI];///este arreglo almacena los clientes del archivo para luego ser ordenado
    int vOrdenacion = 0;

    vOrdenacion = archivoAArregloAltas(ordenacion, DIM_CLI);///paso el archivo al arreglo

    ordenamientoSeleccionAregloApellido(vOrdenacion, ordenacion);///ordeno el arreglo

    muestraArreglo(vOrdenacion, ordenacion);

}

/*******************//**
* \brief Funcion que busca un cliente en archivo por DNI
* \param DNI (int)
* \return Retorna el cliente, id en -1 si no se encuentra en el archivo
**************************/
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

/*******************//**
* \brief Funcion que muestra un cliente buscado por DNI
* \param None
* \return Void

**************************/

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

/*******************//**
* \brief Funcion que pasa del archivo a un arreglo los clientes dados de baja
* \param Array cargado, dimension
* \return Validos
**************************/

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

/*******************//**
* \brief Funcion que busca menor email en un arreglo de clientes
* \param validos, arreglo cargado, posicion de inicio
* \return posicion menor de ese cliente
**************************/
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

/*******************//**
* \brief Funcion de ordenamiento por seleccion de un arreglo de clientes por email
* \param Validos, arreglo cargado
* \return Void
**************************/
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

/*******************//**
* \brief Funcion que ordena por seleccion tomando como referencia email, pasando clientes del archivo al arreglo
* \param None
* \return Void
**************************/
void ordenacionSeleccionArchivoEmail()
{
    stCliente ordenacion[DIM_CLI];///este arreglo almacena los clientes del archivo para luego ser ordenado
    int vOrdenacion = 0;

    vOrdenacion = archivoAArregloBajas(ordenacion, DIM_CLI);///paso el archivo al arreglo

    ordenamientoSeleccionAregloEmail(vOrdenacion, ordenacion);///ordeno el arreglo

    muestraArreglo(vOrdenacion, ordenacion);///muestra el arrreglo ya ordenado

}
