#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"
int main()
{
  Grafo* g = criar_grafo();
  adicionar_vertice(g, "GRU", "Sao Paulo");
  adicionar_vertice(g, "BSB", "Brasilia");
  adicionar_vertice(g, "TRU", "Paraiba");
  adicionar_vertice(g, "CEE", "Ceara"); 
  adicionar_aresta(g, "GRU", "TRU", 400);
  adicionar_aresta(g, "BSB", "TRU", 666);
  adicionar_aresta(g, "GRU", "CEE", 202);
  adicionar_aresta(g, "TRU", "CEE", 303);
  adicionar_aresta(g, "BSB", "CEE", 10);
  remover_aresta(g, "BSB", "CEE");
  listar_voos_do_aeroporto(g, "GRU");
}
