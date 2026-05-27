#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>

typedef struct
{
    float bateria_inicial;
    float bateria_final;
    float total_pagar;
    float energia_necessaria;
    float capacidade_bateria;
    float tempo_recarga;
} SessaoRecarga;

typedef struct
{
    int ocupado;
    SessaoRecarga sessao;
} Posto;

#define MAX_POSTOS 5
const int POTENCIA_CARREGADOR = 75;
const float VALOR_KWH = 0.8;
const int HORAS_EM_MINUTOS = 60;
Posto postos[MAX_POSTOS] = {0, 0, 0, 0, 0};
int postos_utilizados = 0;

void iniciar_menu();
void exibir_menu();
void menu_opcoes(int opcao);
void exibir_posto();
void carregar_carros(SessaoRecarga *sessao);
int ler_int();
float ler_float();
void limpar_buffer();
void entrada_valor_opcao(char resposta);
void processar_recarga();
int bateria_valida(float bateria_inicial);
void verificar_porcentagem_bateria(float bateria_inicial);
int capacidade_bateria_valida(float capacidade_bateria);
void verificar_capacidade_bateria(float capacidade_bateria);
float conversao_para_kwh(float bateria_inicial, float capacidade_bateria);
float calcular_energia_consumida(float capacidade_bateria, float bateria_kwh);
float calcular_tempo_recarga(float energia_necessaria);
float calcular_pagamento(float energia_necessaria);
float carregar_bateria();
void iniciar_sessao(SessaoRecarga *sessao, int indice);
void relatorio_sessao(SessaoRecarga sessao);
void sair_programa();

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    while (1)
    {
        iniciar_menu();
    }

    return 0;
}

void iniciar_menu()
{
    int opcao;

    exibir_menu();

    opcao = ler_int();

    menu_opcoes(opcao);
}

void exibir_menu()
{
    printf("\n=================================\n");
    printf("      ESTAÇÃO DE RECARGA\n");
    printf("=================================\n");

    printf("1 - Informações do Posto\n");
    printf("2 - Carregar Carro\n");
    printf("3 - Relatório Geral do Posto\n");
    printf("4 - Sair do Programa\n");

    printf("Digite a opção: ");
}

void menu_opcoes(int opcao)
{
    switch (opcao)
    {
    case 1:
        exibir_posto();
        break;
    case 2:
        processar_recarga();
        break;
    case 3:
        // Gerar relatório
        break;
    case 4:
        sair_programa();
        break;
    default:
        printf("Valor inválido!\n");
        break;
    }
}

int ler_int()
{
    int valor;   
    while (scanf("%d", valor) != 1)
    {
        printf("[ERRO]: Digite um número inteiro válido: ");

        limpar_buffer();
    }

    limpar_buffer();

    return valor;
}

float ler_float()
{
    float valor;

    while (scanf("%f", valor) != 1)
    {
        printf("[ERRO]: Digite um número decimal válido: ");

        limpar_buffer();
    }

    limpar_buffer();

    return valor;
}

void limpar_buffer() {
    while (getchar() != '\n');
}

void entrada_valor_opcao(char resposta)
{
    if (resposta == 's')
    {
        iniciar_menu();
    }
    else if (resposta == 'n')
    {
        sair_programa();
    }
    else
    {
        printf("Valor inválido!\nDigite exatamente 's' ou 'n': ");
        scanf(" %c", &resposta);

        entrada_valor_opcao(resposta);
    }
}

void carregar_carros(SessaoRecarga *sessao) {
    int quantidade_carros;
    printf("Quantos carros devem ser carregados?\n");
    printf("Digite a quatidade de carros: ");
    scanf("%d", &quantidade_carros);

    while (quantidade_carros > MAX_POSTOS) {
        printf("Valor errado");

    }

    for (int i = 0; i < quantidade_carros; i++) {
        iniciar_sessao(&sessao[i], i);
    }
    
}

void processar_recarga()
{
    int quantidade_carros;
    printf("Quantos carros deseja carregar?");

    do
    {
        quantidade_carros = ler_int();

        if (quantidade_carros <= 0 || quantidade_carros > MAX_POSTOS) {
            printf("Erro: Digite um valor entre 1 e %d", MAX_POSTOS);
        }
    } while (quantidade_carros <= 0 || quantidade_carros > MAX_POSTOS);

    SessaoRecarga sessoes[MAX_POSTOS];

    for (int i = 0; i < quantidade_carros; i++) {
        iniciar_sessao(&sessoes[i], i);

        float bateria_kwh;

        // ==== Carregar Carro ====

        // Verificando se o valor da portcentagem da bateria é válido
        verificar_porcentagem_bateria(sessoes[i].bateria_inicial);

        // Verificando se o valor da capacidade da bateria é válido
        verificar_capacidade_bateria(sessoes[i].capacidade_bateria);

        bateria_kwh = conversao_para_kwh(sessoes[i].bateria_inicial, sessoes[i].capacidade_bateria);

        // Cálculo do total de energia consumida
        sessoes[i].energia_necessaria = calcular_energia_consumida(sessoes[i].capacidade_bateria, bateria_kwh);

        // Tempo de recarga estimado, Potência do carregador: 75kW
        sessoes[i].tempo_recarga = calcular_tempo_recarga(sessoes[i].energia_necessaria);

        // Cálculo da cobrança do carregamento, preço médio do KWh em SP é R$0,80
        sessoes[i].total_pagar = calcular_pagamento(sessoes[i].energia_necessaria);

        // Carregamento da bateria
        sessoes[i].bateria_final = carregar_bateria();

        postos[i].ocupado = 1;

        postos[i].sessao = sessoes[i];

        relatorio_sessao(sessoes[i]);
    }
}

int bateria_valida(float bateria_inicial)
{
    return bateria_inicial >= 0 && bateria_inicial <= 100;
}

void verificar_porcentagem_bateria(float bateria_inicial)
{
    if (!bateria_valida(bateria_inicial))
    {
        printf("Valor de Bateria inválido!\n");
        exit(0);
    }
}

int capacidade_bateria_valida(float capacidade_bateria)
{
    return capacidade_bateria > 0;
}

void verificar_capacidade_bateria(float capacidade_bateria)
{
    if (!capacidade_bateria_valida(capacidade_bateria))
    {
        printf("Capacidade de bateria inválida!\n");
        exit(0);
    }
}

// Função para converter a porcentagem da bateria em kwh
float conversao_para_kwh(float bateria_inicial, float capacidade_bateria)
{
    return (bateria_inicial / 100) * capacidade_bateria;
}

float calcular_energia_consumida(float capacidade_bateria, float bateria_kwh)
{
    return capacidade_bateria - bateria_kwh;
}

float calcular_tempo_recarga(float energia_necessaria)
{
    return (energia_necessaria / POTENCIA_CARREGADOR) * HORAS_EM_MINUTOS;
}

float calcular_pagamento(float energia_necessaria)
{
    return energia_necessaria * VALOR_KWH;
}

float carregar_bateria()
{
    return 100;
}

int calcular_postos_disponiveis()
{
    int disponiveis = 0;

    for (int i = 0; i < MAX_POSTOS; i++)
    {
        if (!postos[i].ocupado)
        {
            disponiveis++;
        }
    }

    return disponiveis;
}

void exibir_posto()
{
    printf("\n=================================\n");
    printf("        POSTOS DISPONÍVEIS\n");
    printf("=================================\n");

    printf("Total de Postos: %d\n", MAX_POSTOS);

    printf("Postos Disponíveis: %d\n", calcular_postos_disponiveis());
}

void iniciar_sessao(SessaoRecarga *sessao, int indice)
{
    printf("\n=================================\n");
    printf("         Sessão iniciada\n");
    printf("         Carro %d\n", indice + 1);
    printf("Conecte O Carregador Ao Seu Carro\n\n");

    do
    {
        printf("Capacidade da bateria (kWh): ");
        sessao->capacidade_bateria = ler_float();
    } while (!capacidade_bateria_valida(sessao->capacidade_bateria));
    
    do
    {
        printf("Bateria atual (0%% a 100%%): ");

        sessao->bateria_inicial = ler_float();

        if (!bateria_valida(sessao->bateria_inicial))
        {
            printf("[ERRO] Valor inválido!\n");
        }

    } while (!bateria_valida(sessao->bateria_inicial));
    printf("=================================\n\n");
}

void relatorio_sessao(SessaoRecarga sessao)
{
    printf("\n=================================\n");
    printf("      RELATÓRIO DA RECARGA\n");
    printf("=================================\n");

    printf("Bateria inicial: %.2f%%\n",
           sessao.bateria_inicial);

    printf("Bateria final: %.2f%%\n",
           sessao.bateria_final);

    printf("Energia necessária: %.2f kWh\n",
           sessao.energia_necessaria);

    printf("Tempo estimado: %.2f min\n",
           sessao.tempo_recarga);

    printf("Valor total: R$ %.2f\n",
           sessao.total_pagar);
}

void relatorio_geral()
{
    printf("=============================================\n");
    printf("             Relatório Geral\n");
    printf("Total de Postos de Carregamento: %d\n");
    printf("Postos Disponíveis: %d\n", calcular_postos_disponiveis());
    printf("Total de Carros Carregados: %.2f\n", 0);
    printf("Total de Energia Consumida: %.2f\n", 0);
    printf("Preço Total das Recargas: R$%.2f\n");
    printf("Total de Tempo Gasto Carregando: %.2fh\n", 0);
    printf("Média das Capacidades das Baterias: %2.f\n", 0);
    printf("Média das Baterias Inciais: %2.f\n", 0);
    printf("=============================================");
}

void sair_programa()
{
    printf("\n\n======Programa Encerrado!======\n\n");
    exit(0);
}