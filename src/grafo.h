#pragma once
#include <stdbool.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_GREEN   "\e[1;32m"
#define ANSI_BOLD          "\x1b[1m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define ERRO(msg) \
    fprintf(stderr, "\n" ANSI_BOLD ANSI_COLOR_RED "ERRO" ANSI_COLOR_YELLOW " [%s:%d]\n" \
            "Função %s(): " ANSI_BOLD ANSI_COLOR_RED "%s" ANSI_COLOR_RESET "\n", \
            __FILE__, __LINE__, __func__, msg)

#define SUCESS(msg) fprintf(stdout, "\n" ANSI_COLOR_GREEN "SUCESSO:" ANSI_BOLD "%s" ANSI_COLOR_RESET "\n", msg)


// =================================================================================== //

#define TAMANHO_INICIAL 1; 

typedef const char* string; 
typedef unsigned int UI32;

typedef struct vertice_t
{
  string sigla;
  string nome_cidade;
} Vertice; // aeroporto

typedef struct grafo_t 
{
  UI32 total_vertices; 
  UI32 contagem_vertices; 
  Vertice* aeroportos;
  UI32** matriz; // matriz de adjacencia que simboliza a relacao entre
} Grafo;

Grafo* criar_grafo();
bool   adicionar_vertice(Grafo* grafo, string sigla, string nome_cidade);
bool   adicionar_aresta(Grafo* grafo, string sigla_origem, string sigla_destino, UI32 numero_voo);
bool   remover_aresta(Grafo* grafo, string sigla_origem, string sigla_destino);

void listar_voos_do_aeroporto(Grafo* grafo, string sigla_aeroporto);
void mostrar_grafo(Grafo* grafo);
void encontre_e_mostre_caminho(Grafo* grafo, string origem, string destino);
