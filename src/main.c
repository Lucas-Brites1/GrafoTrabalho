#include "grafo.h"
#include "menu.h"
int main()
{
  Grafo* g = criar_grafo();
  adicionar_vertice(g, "BSB", "Brasília");
  adicionar_vertice(g, "CNF", "Belo Horizonte");
  adicionar_vertice(g, "GIG", "Rio de Janeiro");
  adicionar_vertice(g, "GRU", "Guarulhos");
  adicionar_vertice(g, "SSA", "Salvador");

  adicionar_aresta(g, "BSB", "SSA", 107);
  adicionar_aresta(g, "CNF", "GIG", 555);
  adicionar_aresta(g, "CNF", "GRU", 101);
  adicionar_aresta(g, "CNF", "SSA", 214);
  adicionar_aresta(g, "GIG", "CNF", 554);
  adicionar_aresta(g, "GIG", "GRU", 90);
  adicionar_aresta(g, "GRU", "BSB", 50);
  adicionar_aresta(g, "GRU", "CNF", 102);
  adicionar_aresta(g, "GRU", "GIG", 89);
  adicionar_aresta(g, "SSA", "CNF", 215); 
  menu(g);
  /*
  Grafo g = criar_grafo();
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
  encontre_e_mostre_caminho(g, "GRU", "CEE");
  */
}
