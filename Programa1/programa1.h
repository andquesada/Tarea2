/* 
 * File:   programa1.h
 * Author: Andrés Quesada
 *
 * Created on May 7, 2011, 1:56 PM
 */

#ifndef PROGRAMA1_H
#define	PROGRAMA1_H

//------------------------------------------------------------------------------
//                IMPORTACIÓN DE BIBLIOTECAS NECESARIAS
//------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//------------------------------------------------------------------------------
//                            PARA MANEJO DE ERRORES
//------------------------------------------------------------------------------

#ifndef CANTIDAD_ERRORES
   #define CANTIDAD_ERRORES 6
#endif

typedef enum RESULTADO_e
{
   RESULTADO_OK            = 0,  //cuando una operación se llevó a cabo correctamente
   RESULTADO_VERDADERO     = 1,
   RESULTADO_IP_INVALIDA   = 2,  //cuando se pasa una dirección ip inválida
   RESULTADO_NULL          = 3,  //cuando algún valor es nulo
   RESULTADO_CANT_PARAM    = 4,  //cantidad de parámetros inválida
   RESULTADO_SUBRED_INV    = 5   //cuando el número de bits para subred no es un entero
} RESULTADO_t;

const char *MENSAJES_ERROR[CANTIDAD_ERRORES] = {
   "\nLa operación se llevó a cabo correctamente.\n\n",
   "\nVerdadero.\n\n",
   "\nDirección ip inválida: %u.\nSe espera un entero sin signo.\n\n",
   "\nParámetro nulo.\n\n",
   "\nCantidad de parámetros inválida.\nEsperados: %d.\nProvistos: %d.\nUso: ./programa2 dir_ip bits_subred\n\n",
   "\nBits para subred inválidos: %d.\nSe espera un valor entero que se encuentre en el rango [1, 32].\n\n"
};

//------------------------------------------------------------------------------
//                REPRESENTACIÓN DE DIRECCIONES IP (IPv4)
//------------------------------------------------------------------------------

#ifndef ELEMENTOS_IPV4
   #define ELEMENTOS_IPV4 4
#endif

typedef unsigned int dir_ipv4[ELEMENTOS_IPV4];

//------------------------------------------------------------------------------
//                      MENSAJES PARA EL USUARIO
//------------------------------------------------------------------------------

#ifndef MENSAJE_DIRECCION_STRING
   #define MENSAJE_DIRECCION_STRING "\nAddress is %s\n\n"
#endif

#ifndef MENSAJE_RED_PUERTA_ENLACE
   #define MENSAJE_RED_PUERTA_ENLACE "\nNetwork is %s, Mask is %s\n\n"
#endif

//------------------------------------------------------------------------------
//                      CÁLCULO DE MÁSCARAS/SUBREDES
//------------------------------------------------------------------------------

#ifndef VALORES_MIN_MAX
   #define VALORES_MIN_MAX 2
#endif

#ifndef TB_SUBRED_IND_INF
   #define TB_SUBRED_IND_INF 0
#endif

#ifndef TB_SUBRED_IND_SUP
   #define TB_SUBRED_IND_SUP 1
#endif

const int TABLA_SUBREDES[ELEMENTOS_IPV4][VALORES_MIN_MAX] = {
   {1,   8},
   {9,   16},
   {17,  24},
   {25,  32}
};

//------------------------------------------------------------------------------
//                               MICELÁNEOS
//------------------------------------------------------------------------------

//cantidad de argumentos que espera el programa
#ifndef ARGUMENTOS_ESPERADOS
   #define ARGUMENTOS_ESPERADOS 2
#endif

#ifndef TAM_HILERA_TMP
   #define TAM_HILERA_TMP 15
#endif

//tamaño de la hilera donde se imprimirá el texto de salida para el usuario
#ifndef TAM_HIL_OUTPUT
   #define TAM_HIL_OUTPUT 200
#endif

#ifndef INDICE_DIR_IP
   #define INDICE_DIR_IP 1
#endif

#ifndef INDICE_BITS_SUBRED
   #define INDICE_BITS_SUBRED 2
#endif

//------------------------------------------------------------------------------

//convierte una dirección IPv4 representada en un entero sin signo y la
//convierta a una dirección IPv4 que puede utilizar este programa
RESULTADO_t obtener_ipv4(const unsigned int ip, dir_ipv4 ipv4);

//pasa una dirección IPv4 a su representación string
RESULTADO_t ipv4_to_string(const dir_ipv4 dir_ip, char *dir_ipv4_str);

#endif	/* PROGRAMA1_H */