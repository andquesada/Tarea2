/* 
 * File:   programa1.c
 * Author: Andrés Quesada
 *
 * Created on May 7, 2011, 1:20 PM
 */

#include "programa1.h"

RESULTADO_t obtener_ipv4(const unsigned int ip,
                         dir_ipv4 ipv4)
{
   if (ipv4 == NULL)
   {
      return RESULTADO_NULL;
   }
   else
   {
      int num_octetos;
      unsigned int mascara;
      unsigned int corrimiento;
      int i;

      num_octetos    = ELEMENTOS_IPV4 - 1;
      mascara        = 0xFF;
      corrimiento    = 0;

      for (i = num_octetos; i >= 0; i--)
      {
         ipv4[i] = ip & mascara;

         if (i < num_octetos)
         {
            corrimiento += 8;
            ipv4[i]     >>= corrimiento;
         }

         mascara <<= 8;
      }

      return RESULTADO_OK;
   }
}

RESULTADO_t ipv4_to_string(const dir_ipv4 dir_ip,
                           char *dir_ipv4_str)
{
   if (dir_ipv4_str == NULL)
   {
      return RESULTADO_NULL;
   }
   else
   {
      char hil_tmp[TAM_HILERA_TMP];
      int canEleIPv4;
      int i;

      canEleIPv4 = ELEMENTOS_IPV4 - 1;

      for (i = 0; i < ELEMENTOS_IPV4; i++)
      {
         //pasa un valor entero a string
         sprintf(hil_tmp,
                 "%u",
                 dir_ip[i]);

         //la primera iteración tiene que usar strcpy para que inicialice
         //correctamente el arreglo
         if (i == 0)
         {
            strcpy(dir_ipv4_str,
                   hil_tmp);
         }
         //las siguientes iteraciones concatenan
         else
         {
            strcat(dir_ipv4_str,
                   hil_tmp);
         }

         //hasta el penúltimo elemento de una dirección de tipo IPv4 se tiene
         //que poner el punto
         if (i < canEleIPv4)
         {
            strcat(dir_ipv4_str,
                   ".");
         }
      }

      return RESULTADO_OK;
   }
}

int main(int argc, char** argv)
{
   if (argc == ARGUMENTOS_ESPERADOS)
   {
      int resultado;

      unsigned int dir_ip_uint;
      dir_ipv4 dir_ip;

      //si se cambian estas variables de lugar el compilador algo hace y se
      //pierden los punteros a la hora de obtener la representación string de
      //una dirección IPv4
      char dir_ip_str[TAM_HILERA_TMP];

      //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
      //          se obtiene el número que representará la dirección IP
      //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

      dir_ip_uint = strtoul(argv[INDICE_DIR_IP],
                            NULL,
                            0);

      //cuando es cero implica que el número digitado es inválido
      if (dir_ip_uint == 0)
      {
         printf(MENSAJES_ERROR[RESULTADO_IP_INVALIDA],
                dir_ip_uint);

         return (EXIT_FAILURE);
      }

      //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
      //             se interpreta la dirección IPv4 que digitó el usuario
      //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

      resultado = obtener_ipv4(dir_ip_uint,
                               dir_ip);

      if (resultado != RESULTADO_OK)
      {
         printf(MENSAJES_ERROR[resultado]);

         return (EXIT_FAILURE);
      }

      resultado = ipv4_to_string(dir_ip,
                                 dir_ip_str);

      if (resultado != RESULTADO_OK)
      {
         printf(MENSAJES_ERROR[resultado]);

         return (EXIT_FAILURE);
      }

      //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
      //             impresión en la consola de los resultados
      //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

      printf(MENSAJE_DIRECCION_STRING,
             dir_ip_str);

      return (EXIT_SUCCESS);
   }
   else
   {
      printf(MENSAJES_ERROR[RESULTADO_CANT_PARAM],
             ARGUMENTOS_ESPERADOS,
             argc);

      return (EXIT_FAILURE);
   }
}