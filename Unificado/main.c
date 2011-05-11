/* 
 * File:   main.c
 * Author: Andrés Quesada
 * Course: Desarrollo de sistemas empotrados en C y Linux
 *
 * Created on May 7, 2011, 2:37 PM
 */

#include "main.h"

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

RESULTADO_t obtener_mascara_red(const int bits_subred,
                                dir_ipv4 mascara)
{
   if (mascara == NULL)
   {
      return RESULTADO_NULL;
   }
   else
   {
      int octeto;
      int i;
      int bit_actual;
      int cant_bits;
      int encendido_bits;

      //se va a buscar el octeto donde está la subred
      for (octeto = 0; octeto < ELEMENTOS_IPV4; octeto++)
      {
         if ((bits_subred >= TABLA_SUBREDES[octeto][TB_SUBRED_IND_INF]) &&
             (bits_subred <= TABLA_SUBREDES[octeto][TB_SUBRED_IND_SUP]))
         {
            break;
         }
      }

      for (i = 0; i < ELEMENTOS_IPV4; i++)
      {
         if (i < octeto)
         {
            mascara[i] = 255;
         }
         else if (octeto == i)
         {            
            mascara[i]     = 0;
            encendido_bits = 128;

            if (octeto == 0)
            {
               cant_bits = bits_subred;
            }
            else
            {
               cant_bits = (bits_subred - TABLA_SUBREDES[octeto][TB_SUBRED_IND_INF]) + 1;
            }

            for (bit_actual = 0; bit_actual < cant_bits; bit_actual++)
            {               
               mascara[i]     |= encendido_bits;
               encendido_bits >>= 1;
            }
         }
         else
         {
            mascara[i] = 0;
         }
      }

      return RESULTADO_OK;
   }
}

RESULTADO_t obtener_subred(const dir_ipv4 ip,
                           const int bits_subred,
                           dir_ipv4 subred)
{
   if (subred == NULL)
   {
      return RESULTADO_NULL;
   }
   else
   {
      int octeto;
      int i;
      int bit_actual;
      int cant_bits;
      int encendido_bits;

      //se va a buscar el octeto donde está la subred
      for (octeto = 0; octeto < ELEMENTOS_IPV4; octeto++)
      {
         if ((bits_subred >= TABLA_SUBREDES[octeto][TB_SUBRED_IND_INF]) &&
             (bits_subred <= TABLA_SUBREDES[octeto][TB_SUBRED_IND_SUP]))
         {
            break;
         }
      }

      for (i = 0; i < ELEMENTOS_IPV4; i++)
      {
         if (i < octeto)
         {
            subred[i] = ip[i];
         }
         else if (octeto == i)
         {
            subred[i]      = 0;
            encendido_bits = 128;

            if (octeto == 0)
            {
               cant_bits = bits_subred;
            }
            else
            {
               cant_bits = (bits_subred - TABLA_SUBREDES[octeto][TB_SUBRED_IND_INF]);
            }

            for (bit_actual = 0; bit_actual < cant_bits; bit_actual++)
            {
               subred[i]      |= ip[i] & encendido_bits;
               encendido_bits >>= 1;
            }
         }
         else
         {
            subred[i] = 0;
         }
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
      int cant_bits_subred;

      dir_ipv4 dir_ip;
      dir_ipv4 subred;
      dir_ipv4 mascara;

      //si se cambian estas variables de lugar el compilador algo hace y se
      //pierden los punteros a la hora de obtener la representación string de
      //una dirección IPv4
      char mascara_str[TAM_HILERA_TMP];
      char subred_str[TAM_HILERA_TMP];      

      //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
      //          se obtiene el número que representará la dirección IP
      //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

      dir_ip_uint = strtoul(argv[INDICE_DIR_IP],
                            NULL,
                            0);

      //cuando es cero implica que el número digitado es inválido
      if (dir_ip_uint == 0)
      {
         fprintf(stderr,
                 MENSAJES_ERROR[RESULTADO_IP_INVALIDA],
                 dir_ip_uint);

         return (EXIT_FAILURE);
      }

      //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
      //se obtiene el número que representará la cantidad de bits a usar para la subred
      //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

      cant_bits_subred = atoi(argv[INDICE_BITS_SUBRED]);

      if (cant_bits_subred < 1 || cant_bits_subred > 32)
      {
         fprintf(stderr,
                 MENSAJES_ERROR[RESULTADO_SUBRED_INV],
                 cant_bits_subred);

         return (EXIT_FAILURE);
      }

      //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
      //             se interpreta la dirección IPv4 que digitó el usuario
      //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

      resultado = obtener_ipv4(dir_ip_uint,
                               dir_ip);

      if (resultado != RESULTADO_OK)
      {
         fprintf(stderr,
                 MENSAJES_ERROR[resultado]);

         return (EXIT_FAILURE);
      }

      //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
      //                            se obtiene la subred
      //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

      resultado = obtener_subred(dir_ip,
                                 cant_bits_subred,
                                 subred);

      if (resultado != RESULTADO_OK)
      {
         fprintf(stderr,
                 MENSAJES_ERROR[resultado]);

         return (EXIT_FAILURE);
      }

      resultado = ipv4_to_string(subred,
                                 subred_str);

      if (resultado != RESULTADO_OK)
      {
         fprintf(stderr,
                 MENSAJES_ERROR[resultado]);

         return (EXIT_FAILURE);
      }

      //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
      //                            se obtiene la máscara
      //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

      resultado = obtener_mascara_red(cant_bits_subred,
                                      mascara);

      if (resultado != RESULTADO_OK)
      {
         fprintf(stderr,
                 MENSAJES_ERROR[resultado]);

         return (EXIT_FAILURE);
      }

      resultado = ipv4_to_string(mascara,
                                 mascara_str);

      if (resultado != RESULTADO_OK)
      {
         fprintf(stderr,
                 MENSAJES_ERROR[resultado]);

         return (EXIT_FAILURE);
      }

      //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
      //             impresión en la consola de los resultados
      //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

      printf(MENSAJE_RED_PUERTA_ENLACE,
             subred_str,
             mascara_str);

      return (EXIT_SUCCESS);
   }
   else
   {
      fprintf(stderr,
              MENSAJES_ERROR[RESULTADO_CANT_PARAM],
              ARGUMENTOS_ESPERADOS,
              argc);

      return (EXIT_FAILURE);
   }   
}