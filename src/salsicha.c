#include "salsicha.h"
#include "grafo.h"
#include <stdio.h>
#include <stdlib.h>

int ler_txt_mostrar(const char* nome_arquivo)
{
  FILE* ptr_arquivo;
  unsigned int caractere;

  ptr_arquivo = fopen(nome_arquivo, "r");

  if (ptr_arquivo == NULL)
  {
    ERRO("Falha ao abrir arquivo maligno\n");
    return EXIT_FAILURE;
  }

  while((caractere = fgetc(ptr_arquivo)) != EOF)
  {
    putchar(caractere);
  }

  fclose(ptr_arquivo);
  return 0;
}
