#include "grafo.h"
#include "menu.h"
#include <stdio.h>
#include <string.h>

void animacao_aviao(UI32 tamanho)

{
  for(UI32 i=0; i<tamanho; i++)
  { 
    printf("\r");

    for (UI32 j=0; j<i; j++) printf(" ");
    printf("✈ \033[K");
    fflush(stdout);
    TIMER(10);
  }

  printf("\033[?25h");
  printf("\n");
}

void limpar_buffer_stdin() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void remover_nova_linha(char* str) {
    str[strcspn(str, "\n")] = 0;
}

void ler_string_valida(const char* prompt, char* buffer, int tamanho) {
    while (1) {
        printf("%s", prompt);
        fgets(buffer, tamanho, stdin);
        remover_nova_linha(buffer);

        if (buffer[0] != '\0') {
            break;
        }
        printf("Entrada inválida. O campo não pode ser em branco.\n\n");
    }
}


void menu(Grafo* grafo)
{
    int escolha = 0;
    bool aux = true;

    while (escolha != 6)
    {
        if (aux) aux = !aux;
        else printf("\033[2J\033[H");

        printf("%s", opcoes());
        if (scanf("%d", &escolha) != 1) {
            printf("Entrada inválida. Por favor, digite um número.\n");
            limpar_buffer_stdin();
            escolha = 0;
            continue;
        }
        
        limpar_buffer_stdin();
        executar(grafo, escolha);
    }
}

const char* opcoes()
{
    animacao_aviao(50);
    return " \n\
               [MENU]\n\
    1. Cadastrar Aeroporto\n\
    2. Cadastrar Voo\n\
    3. Remover Voo\n\
    4. Listar Voos de um Aeroporto\n\
    5. Encontrar Melhor Trajeto\n\
    6. Encerrar\n\
    Escolha uma opção: ";
}


void executar(Grafo* g, int opcao) {
    char sigla_origem[5];
    char sigla_destino[5];
    char nome_cidade[100];
    UI32 numero_voo;

    switch (opcao) {
        case 1:
            ler_string_valida("Digite a sigla do novo aeroporto (ex: VCP): ", sigla_origem, sizeof(sigla_origem));
            ler_string_valida("Digite o nome da cidade: ", nome_cidade, sizeof(nome_cidade));
            adicionar_vertice(g, sigla_origem, nome_cidade);
            break;

        case 2:
            ler_string_valida("Digite a sigla de ORIGEM: ", sigla_origem, sizeof(sigla_origem));
            ler_string_valida("Digite a sigla de DESTINO: ", sigla_destino, sizeof(sigla_destino));
            
            printf("Digite o numero do VOO: ");
            scanf("%u", &numero_voo);
            limpar_buffer_stdin();

            adicionar_aresta(g, sigla_origem, sigla_destino, numero_voo);
            break;

        case 3:
            ler_string_valida("Digite a sigla de ORIGEM do voo a remover: ", sigla_origem, sizeof(sigla_origem));
            ler_string_valida("Digite a sigla de DESTINO do voo a remover: ", sigla_destino, sizeof(sigla_destino));
            remover_aresta(g, sigla_origem, sigla_destino);
            break;

        case 4:
            ler_string_valida("Digite a sigla do aeroporto para listar os voos: ", sigla_origem, sizeof(sigla_origem));
            listar_voos_do_aeroporto(g, sigla_origem);
            break;

        case 5:
            ler_string_valida("Digite a sigla de ORIGEM do trajeto: ", sigla_origem, sizeof(sigla_origem));
            ler_string_valida("Digite a sigla de DESTINO do trajeto: ", sigla_destino, sizeof(sigla_destino));
            encontre_e_mostre_caminho(g, sigla_origem, sigla_destino);
            break;

        case 6:
            printf("Encerrando o programa...\n");
            break;
        
        default:
            printf("Opção inválida! Tente novamente.\n");
            break;
    }

    if (opcao != 6) {
        printf("\nPressione Enter para continuar...");
        getchar();
    }
}
