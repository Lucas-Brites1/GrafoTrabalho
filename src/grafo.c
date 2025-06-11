#include "grafo.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Vertice* criar_vertice(string sigla, string cidade)
{
  Vertice* v = (Vertice*) malloc(sizeof(Vertice));
  if (!v)
  {
    ERRO("Falha ao tentar alocar memoria para novo vertice.\n");
    return NULL;
  }


  v->sigla = strdup(sigla);
  v->nome_cidade = strdup(cidade);
  if (!v->sigla || !v->nome_cidade) {
      ERRO("Falha ao alocar memoria para strings do vertice.\n");
      free((void*)v->sigla);
      free((void*)v->nome_cidade);
      free(v);
      return NULL;
  }

  return v;
}

void procurar_vertice(Grafo* grafo, string sigla, int* indice)
{
  *indice = -1;

  Vertice* aeroportos = grafo->aeroportos;
  for (int i=0; i<grafo->contagem_vertices; i++)
  {
    if (strcmp(aeroportos[i].sigla, sigla) == 0) {
      *indice = i;
      return;
    };
  }
}

bool procurar_voo(UI32 numero_voo, Grafo* grafo) 
{
  for (int i=0; i<grafo->contagem_vertices; i++)
  {
    for (int j=0; j<grafo->contagem_vertices; j++) 
    {
      if(grafo->matriz[i][j] == numero_voo) return true;
    }
  }

  return false;
}

UI32** criar_matriz_adjacencia(UI32 tamanho)
{
  UI32** matriz = (UI32**) calloc(tamanho, sizeof(UI32*));
  if (!matriz)
  {
    ERRO("Falha ao tentar alocar memoria para matriz de adjacencia.\n");
    return NULL;
  }
  
  for (int i=0; i<tamanho; i++)
  {
    matriz[i] = (UI32*) calloc(tamanho, sizeof(UI32));
    if (!matriz[i])
    {
      ERRO("Falha ao alocar as colunas da matriz.\n");
      for(int j=0; j<i; j++)
      {
        free(matriz[j]);
      }
      free(matriz);
      return NULL;
    }
  }

  return matriz;
}

bool realocar_array_vertices(Grafo* grafo)
{
  UI32 novo_tamanho = grafo->total_vertices * 2;
  Vertice* novo_array_vertices = (Vertice*) realloc(grafo->aeroportos, novo_tamanho * sizeof(Vertice));
  if (!novo_array_vertices)
  {
    ERRO("Falha ao tentar expandir vetor de vertices.\n");
    return false;
  }

  grafo->total_vertices = novo_tamanho;
  grafo->aeroportos = novo_array_vertices;
  return true;
}

bool realocar_matriz_adjacencia(Grafo* grafo)
{
  UI32 novo_tamanho = grafo->total_vertices * 2;
  UI32** nova_matriz_adjacencia = criar_matriz_adjacencia(novo_tamanho);

  if (!nova_matriz_adjacencia)
  {
    ERRO("Falha ao tentaer expandir matriz de adjacencia.\n");
    return false;
  }

  for (int i=0; i < grafo->contagem_vertices; i++) 
  {
    for (int j=0; j < grafo->contagem_vertices; j++)
    {
      nova_matriz_adjacencia[i][j] = grafo->matriz[i][j];
    }
    free(grafo->matriz[i]);
  }

  free(grafo->matriz);
  grafo->matriz = nova_matriz_adjacencia;
  return true;
}

// ========================================================================================== //

Grafo* criar_grafo()
{
  Grafo* g = (Grafo*) malloc(sizeof(Grafo));
  if (!g) 
  {
    ERRO("Falha ao tentar alocar memoria para grafo.");
    return NULL;
  }

  g->total_vertices=TAMANHO_INICIAL;
  g->contagem_vertices=0;
  g->aeroportos = (Vertice*) malloc(sizeof(Vertice) * g->total_vertices);
  g->matriz = criar_matriz_adjacencia(g->total_vertices);
  if(!g->matriz)
  {
    ERRO("Erro ao inicializar grafo.");
    free(g->aeroportos);
    free(g);
    return NULL;
  }

  return g;
}

bool adicionar_vertice(Grafo* grafo, string sigla, string nome_cidade)
{
  if (!grafo)
  {
    ERRO("Parametro grafo nao foi inicializado corretamente.");
    return false;
  }

  Vertice* novo_vertice = criar_vertice(sigla, nome_cidade);
  if (!novo_vertice) 
  {
    ERRO("Falha ao adicionar novo vertice.");
    return false;
  }

  if (grafo->contagem_vertices >= grafo->total_vertices)
  {
    if(!realocar_array_vertices(grafo))
    {
      ERRO("Falha ao tentar realocar array de vertices.");
      return false;
    }
    if(!realocar_matriz_adjacencia(grafo)) 
    {
      ERRO("Falha ao tentar realocar matriz de adjacencia.");
      return false;
    }
  }

  grafo->aeroportos[grafo->contagem_vertices++] = (*novo_vertice);
  SUCESS("Aeroporto cadastrado com sucesso!");
  return true;
}

bool adicionar_aresta(Grafo* grafo, string sigla_origem, string sigla_destino, UI32 numero_voo) 
{
  if (!grafo)
  {
    ERRO("Parametro grafo nao foi inicializado corretamente.");
    return false;
  }
  
  int idx_origem; int idx_destino;
  procurar_vertice(grafo, sigla_origem, &idx_origem);
  procurar_vertice(grafo, sigla_destino, &idx_destino);
  if (idx_origem == -1)
  {
    ERRO("Aeroporto de origem nao encontrado.");
    return false;
  }
  else if (idx_destino == -1)
  {
    ERRO("Aeroporto de destino nao encontrado.");
    return false;
  }
  else if( idx_origem == -1 && idx_destino == -1) 
  {
    ERRO("Aeroportos especificados nao encontrados.");
    return false;
  }

  if (idx_origem == idx_destino) 
  {
    ERRO("Cadastro de voo invalido.\nAeroporto de destino igual ao de origem.");
    return false;
  }

  if (procurar_voo(numero_voo, grafo))
  {
    ERRO("Voo ja cadastrado.");
    return false;
  }

  grafo->matriz[idx_origem][idx_destino] = numero_voo;
  SUCESS("Voo cadastrado com sucesso!");
  return true;
}

bool remover_aresta(Grafo* grafo, string sigla_origem, string sigla_destino)
{
  if (!grafo)
  {
    ERRO("Parametro grafo nao foi inicializado corretamente.\n");
    return false;
  }
  
  int idx_origem; int idx_destino;
  procurar_vertice(grafo, sigla_origem, &idx_origem);
  procurar_vertice(grafo, sigla_destino, &idx_destino);
  if (idx_origem == -1)
  {
    ERRO("Aeroporto de origem nao encontrado.");
    return false;
  }
  else if (idx_destino == -1)
  {
    ERRO("Aeroporto de destino nao encontrado.");
    return false;
  }
  else if( idx_origem == -1 && idx_destino == -1) 
  {
    ERRO("Aeroportos especificados nao encontrados.");
    return false;
  }

  grafo->matriz[idx_origem][idx_destino] = 0;
  SUCESS("Voo removido com sucesso!");
  return true;
}

void listar_voos_do_aeroporto(Grafo* grafo, string sigla_aeroporto)
{

  if (!grafo)
  {
    ERRO("Parametro grafo nao foi inicializado corretamente.");
    return;
  }

  int idx_aeroporto;
  procurar_vertice(grafo, sigla_aeroporto, &idx_aeroporto);

  if (idx_aeroporto == -1)
  {
    ERRO("Aeroporto nao encontrado.");
    return;
  }

  Vertice aeroporto_origem = grafo->aeroportos[idx_aeroporto];
  printf("Voos saindo do aeroporto %s(%s):  \n", aeroporto_origem.nome_cidade, aeroporto_origem.sigla);
  UI32* aeroporto_matriz = grafo->matriz[idx_aeroporto];
  for(int i=0; i<grafo->contagem_vertices;i++)
  {
    if(aeroporto_matriz[i] != 0) printf(ANSI_BOLD"[ VOO:  %u  ] | [ DESTINO: %s(%s) ]\n", aeroporto_matriz[i], grafo->aeroportos[i].nome_cidade, grafo->aeroportos[i].sigla);
  }
}

void achar_todos_os_caminhos_recursivo(
    Grafo* grafo,
    UI32 idx_atual,
    UI32 idx_destino,
    UI32* mapa_visitado,
    UI32* caminho,
    UI32 tamanho_caminho )
{
  mapa_visitado[idx_atual] = 1;
  caminho[tamanho_caminho] = idx_atual;
  tamanho_caminho++;

  if (idx_atual == idx_destino) 
  {
    printf("  ");
    for (UI32 i = 0; i < tamanho_caminho; i++) {
      printf("%s%s", grafo->aeroportos[caminho[i]].sigla, (i < tamanho_caminho - 1) ? " -> " : "\n");
    }
  } else 
  {
    for (int idx_vizinho = 0; idx_vizinho < grafo->contagem_vertices; idx_vizinho++) 
    {
      if (grafo->matriz[idx_atual][idx_vizinho] != 0 && !mapa_visitado[idx_vizinho]) 
      {
        achar_todos_os_caminhos_recursivo(grafo, idx_vizinho, idx_destino, mapa_visitado, caminho, tamanho_caminho);
      }
    }
  }

  mapa_visitado[idx_atual] = 0;
}

void encontre_e_mostre_caminho(Grafo* grafo, string origem, string destino)
{
  int idx_origem; int idx_destino;
  procurar_vertice(grafo, origem, &idx_origem);
  procurar_vertice(grafo, destino, &idx_destino);
  if (idx_origem == -1 || idx_destino == -1)
  {
    ERRO("Destino ou origem invalidos.\n");
    return;
  }

  printf("\nBuscando trajeto de %s para %s...\n", grafo->aeroportos[idx_origem].nome_cidade, grafo->aeroportos[idx_destino].nome_cidade);

  UI32* mapa_visita = (UI32*) calloc(grafo->contagem_vertices, sizeof(UI32));
  UI32* caminho = (UI32*) malloc(grafo->contagem_vertices * sizeof(UI32));
  UI32  tamanho_caminho = 0;

  if (!mapa_visita || !caminho)
  {
    ERRO("Erro de alocacao de memoria para realizar busca.\n");
    free(mapa_visita); free(caminho);
    return;
  }

  SUCESS("Trajetos encontrados: \n");
  achar_todos_os_caminhos_recursivo(grafo, idx_origem, idx_destino, mapa_visita, caminho, tamanho_caminho);
  free(mapa_visita);
  free(caminho);
}
