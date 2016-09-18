//
//  main.cpp
//  Torres Hanoi
//
//  Created by Claudio Ibáñez Garduño and Rodrigo Montoya Rangel on 17/09/16.
//  Copyright (c) 2016 Claudio Ibáñez Garduño & Rodrigo Montoya Rangel. All rights reserved.
//




/*
	Implementa el ejercicio de las torres de Hanoi, utilizando pilas para representar las torres.
 */


#include <stdio.h>
#include <stdlib.h>

//Estructura Disco para calcular ancho y alto de nuestra "piramide"
struct DISCO
{
    int ancho;	// Contendrá el ancho, en intervalos impares, del disco.
    int altura;	// Contiene el nivel en el que se encuentra ese disco.
};

//Estructura Nodo
struct NODO
{
    struct DISCO disc;
    struct NODO *puntero;
};



// FUNCIÓN QUE INTRODUCE UN NUMERO EN UNA PILA:
//@params doble apuntador de tipo struc Nodo, int disco
//@result Vacio
void insertaDatoEnLaPila( struct NODO **pila, int disco )
{
    struct NODO *temp = (struct NODO *) malloc(sizeof(struct NODO));
    // Si la pila no tiene nodos (NULL) la altura del disco que se va a introducir sera siempre de 1. Sin embargo si ya tiene nodos, la altura sera igual a la del nodo inferior +1.
    if( *pila == NULL )
        temp->disc.altura = 1;
    else
        temp->disc.altura = (*pila)->disc.altura + 1;
    
    temp->disc.ancho = disco;
    temp->puntero	 = *pila;
    *pila			 = temp;
    
};



// FUNCIÓN QUE EXTRAE EL PRIMER ELEMENTO DE LA PILA Y BORRA EL NODO VACIO:
//@params doble apuntador a structura nodo y entero numNivel
//@result int regreesa el elemento a mover(disco)
int extraeDatoDeLaPila( struct NODO **pila, int *numNivel )
{
     /*Poscondición:
					Se devuelve el primer parámetro de tipo entero almacenado en la pila, si esta vacía devuelve un 0.
					Devuelve por referencia la altura del disco.
     */
    
    
    struct NODO *siguiente;
    int resp;
    
    if( *pila == NULL )
        resp = 0;
    else
    {
        // Se copia el ancho a la variable que va a ser retornada por la función:
        *numNivel	= (*pila)->disc.altura;
        resp		= (*pila)->disc.ancho;
        
        
        // Se elimina el primer Nodo (el vaciado):
        siguiente = (*pila)->puntero;
        free(*pila);
        *pila = siguiente;
    };
    
    return resp;
};



// FUNCIÓN QUE CREA UNA COPIA IDENTICA DE UNA PILA:
void creaUnaCopiaDePila( struct NODO **pila, struct NODO **pilaCopia )
{    
    struct NODO *siguiente = *pila;
    struct NODO *antBusq;
    struct NODO *sigBusq;
    struct NODO *temp;
    
    // Mientras el puntero siguiente siga apuntando a otro Nodo...
    while( siguiente != NULL )
    {
        temp = (struct NODO *) malloc(sizeof(struct NODO));
        // Si la pila nueva no tiene ningún Nodo se introduce al principio:
        if( *pilaCopia == NULL )
        {
            temp->disc 		= siguiente->disc;
            temp->puntero	= NULL;
            *pilaCopia		= temp;
        }
        // En caso contrario se introducen los siguientes Nodos siempre al final de la pila (que se esta tratando como una cola).
        else
        {
            sigBusq = *pilaCopia;
            // Se busca el ultimo Nodo:
            while( sigBusq != NULL )
            {
                antBusq = sigBusq;
                sigBusq = sigBusq->puntero;
            };
            temp->disc 		 = siguiente->disc;
            temp->puntero	 = NULL;
            antBusq->puntero = temp;
        };
        // Se avanza una posición en el puntero de la lista original:
        siguiente = siguiente->puntero;
    };
};

// FUNCIÓN QUE BORRA UNA LISTA ENTERA:
void borrarLista( struct NODO **lista )
{
    struct NODO *actual, *siguiente;
    actual = *lista;
    while(actual != NULL)
    {
        siguiente = actual->puntero;
        free(actual);
        actual = siguiente;
    };
    *lista = NULL;
};

// FUNCIÓN QUE IMPRIME EL TABLERO DE HANOI:
void imprimeTablero( struct NODO **pilaO, struct NODO **pilaA, struct NODO **pilaD, int totDiscos, int tamDiscGrande )
{
    // Se crean tres punteros temporales:
    struct NODO *pilaOc=NULL, *pilaAc=NULL, *pilaDc=NULL;
    int discoO, discoA, discoD, nivelO=0, nivelA=0, nivelD=0;
    int espO, espA, espD;
    int numNivel;
    int i;
    // Se usan los punteros temporales para que apunten a unas nuevas pilas idénticas a las originales:
    creaUnaCopiaDePila( pilaO, &pilaOc );
    creaUnaCopiaDePila( pilaA, &pilaAc );
    creaUnaCopiaDePila( pilaD, &pilaDc );
    // Se obtiene el numero de disco por return y la altura del disco por referencia...
    discoO = extraeDatoDeLaPila(&pilaOc, &nivelO);
    discoA = extraeDatoDeLaPila(&pilaAc, &nivelA);
    discoD = extraeDatoDeLaPila(&pilaDc, &nivelD);
    // Se recorren todos los niveles de las pilas aunque estén vacíos:
    for( numNivel=totDiscos; numNivel > 0; numNivel-- )
    {
        // Se calculan los espacios necesarios para el disco a imprimir en la altura correspondiente:
        espO = ( tamDiscGrande - discoO )/2;
        espA = ( tamDiscGrande - discoA )/2;
        espD = ( tamDiscGrande - discoD )/2;
        if( nivelO == numNivel )
        {
            // Espacios a la izquierda
            for( i=0; i < espO; i++ )
                printf( " " );
            // Imprime los comodines
            for( i=0; i < discoO; i++ )
                printf( "*" );
            // Espacios a la derecha
            for( i=0; i < espO; i++ )
                printf( " " );
            // Se recoge el siguiente disco:
            discoO = extraeDatoDeLaPila(&pilaOc, &nivelO);
        }
        else
        {
            // Se rellena todo de espacios ya que no hay disco en ese altura:
            for( i=0; i < tamDiscGrande; i++ )
                printf( " " );
        };
        printf( "  " );
        // Torre 1 o Auxiliar:
        if( nivelA == numNivel )
        {
            // Espacios a la izquierda
            for( i=0; i < espA; i++ )
                printf( " " );
            // Imprime los comodines
            for( i=0; i < discoA; i++ )
                printf( "*" );
            // Espacios a la derecha
            for( i=0; i < espA; i++ )
                printf( " " );
            discoA = extraeDatoDeLaPila(&pilaAc, &nivelA);
        }
        else
        {
            // Se rellena todo de espacios ya que no hay disco en ese altura:
            for( i=0; i < tamDiscGrande; i++ )
                printf( " " );
        };
        printf( "  " );
        // Torre 1 o Destino:
        if( nivelD == numNivel )
        {
            // Espacios a la izquierda
            for( i=0; i < espD; i++ )
                printf( " " );
            // Imprime los comodines
            for( i=0; i < discoD; i++ )
                printf( "*" );
            // Espacios a la derecha
            for( i=0; i < espD; i++ )
                printf( " " );
            
            discoD = extraeDatoDeLaPila(&pilaDc, &nivelD);
        }
        else
        {
            // Se rellena todo de espacios ya que no hay disco en ese altura:
            for( i=0; i < tamDiscGrande; i++ )
                printf( " " );
        };
        printf( "\n" );
    };
};

// FUNCIÓN QUE MUEVE UN DISCO DE UNA PILA A OTRA:
void mueveDisco( struct NODO **pilaO, struct NODO **pilaA, struct NODO **pilaD, int totDiscos, int tamDiscGrande, char listOrigen, char listDestino )
{
    int paraNada=0;
    if( listOrigen == 'O' )
    {
        if( listDestino == 'A' )
            insertaDatoEnLaPila( pilaA, extraeDatoDeLaPila(pilaO, &paraNada) );
        else if( listDestino == 'D' )
            insertaDatoEnLaPila( pilaD, extraeDatoDeLaPila(pilaO, &paraNada) );
    }
    else if( listOrigen == 'A' )
    {
        if( listDestino == 'O' )
            insertaDatoEnLaPila( pilaO, extraeDatoDeLaPila(pilaA, &paraNada) );
        else if( listDestino == 'D' )
            insertaDatoEnLaPila( pilaD, extraeDatoDeLaPila(pilaA, &paraNada) );
    }
    else if( listOrigen == 'D' )
    {
        if( listDestino == 'O' )
            insertaDatoEnLaPila( pilaO, extraeDatoDeLaPila(pilaD, &paraNada) );
        else if( listDestino == 'A' )
            insertaDatoEnLaPila( pilaA, extraeDatoDeLaPila(pilaD, &paraNada) );
    };
    // Se imprime el tablero:
    imprimeTablero( pilaO, pilaA, pilaD, totDiscos, tamDiscGrande );
};



// FUNCIÓN DE HANOI MEDIANTE RECURSIVIDAD:
void hanoi( struct NODO **pilaO, struct NODO **pilaA, struct NODO **pilaD, int nDiscos, int totDiscos, int tamDiscGrande, char O, char A, char D )
{
    if( nDiscos == 1 )
    {
        // Se borra la pantalla, se mueve el disco/imprime y se hace una pausa que varia dependiendo del numero de discos:
        system("clear");
        mueveDisco( pilaO, pilaA, pilaD, totDiscos, tamDiscGrande, O, D );
        if(totDiscos<=5) system("sleep 0.8"); else if(totDiscos<=10) system("sleep 0.3"); else if(totDiscos<=15) system("sleep 0.06"); else if(totDiscos>15) system("sleep 0.02");
    }
    else
    {
        hanoi( pilaO, pilaA, pilaD, nDiscos-1, totDiscos, tamDiscGrande, O, D, A );
        
        system("clear");
        mueveDisco( pilaO, pilaA, pilaD, totDiscos, tamDiscGrande, O, D );
        if(totDiscos<=5) system("sleep 0.8"); else if(totDiscos<=10) system("sleep 0.3"); else if(totDiscos<=15) system("sleep 0.06"); else if(totDiscos>15) system("sleep 0.02");
        
        hanoi( pilaO, pilaA, pilaD, nDiscos-1, totDiscos, tamDiscGrande, A, O, D );
    };
    
};

//Funcion Main
int main()
{
    struct NODO *pilaO=NULL, *pilaA=NULL, *pilaD=NULL;
    int nDiscos, disco, tamDiscGrande, i;
    printf( "Indique el número de discos: " );
    scanf( "%i", &nDiscos );
    // Se halla el disco más grande (de tamaño impar) que se usara:
    disco = 1 + 2*(nDiscos - 1);
    tamDiscGrande = disco; // Se hace una copia para poder conservar el numero.
    for( i=0; i < nDiscos; i++ )
    {
        // Se introduce el disco que corresponda y se resta 2 para la siguiente iteración:
        insertaDatoEnLaPila( &pilaO, disco );
        disco -= 2;
    };
    // Se imprime el tablero:
    system("clear");
    imprimeTablero( &pilaO, &pilaA, &pilaD, nDiscos, tamDiscGrande );
    system("sleep 1");
    // Se llama a hanoi para comenzar "la partida":
    hanoi( &pilaO, &pilaA, &pilaD, nDiscos, nDiscos, tamDiscGrande, 'O', 'A', 'D' );
    // Se borran la pila de destino que es la única que tiene nodos:
    borrarLista( &pilaD );
    
};