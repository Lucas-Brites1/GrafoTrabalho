#pragma once
#include "grafo.h"

#ifdef _WIN32           
 #include <windows.h>  
#else                   
 #include <unistd.h>   
#endif                  

#ifdef _WIN32
  #define TIMER(ms) Sleep(ms)
#else
  #define TIMER(ms) usleep((ms) * 1000)
#endif

void        menu(Grafo* grafo);
const char* opcoes();
void        executar(Grafo* g, int opcao);
