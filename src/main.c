#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define MAX_POSTOS 5
#define MAX_SESSOES 100

const int POTENCIA_CARREGADOR = 75;
const float VALOR_KWH = 0.8f;
const int HORAS_EM_MINUTOS = 60;

typedef struct
{
    float bateria_inicial;
    float bateria_final;
    float total_pagar;
    float energia_necessaria;
    float capacidade_bateria;
    float tempo_recarga;
    float potencia_recebida;
    float tarifa_aplicada;
    int horario_recarga;
} SessaoRecarga;

typedef struct
{
    int ocupado;
    SessaoRecarga sessao;

} Posto;


Posto postos[MAX_POSTOS] = {0};

SessaoRecarga historico[MAX_SESSOES];

int total_sessoes = 0;

/* MENU */
void iniciar_menu();
void exibir_menu();
void menu_opcoes(int opcao);

/* ENTRADA */
int ler_int();
float ler_float();
void limpar_buffer();

/* POSTOS */
void exibir_posto();
int calcular_postos_disponiveis();

/* RECARGA */
void processar_recarga();
void iniciar_sessao(SessaoRecarga *sessao, int indice);
void processar_calculos(SessaoRecarga *sessao, int carros_ativos);
void salvar_sessao(SessaoRecarga sessao);

/* VALIDAÇÕES */
int bateria_valida(float bateria);
int capacidade_valida(float capacidade);

/* CÁLCULOS */
float converter_para_kwh(float bateria, float capacidade);
float calcular_energia_consumida(float capacidade, float bateria_kwh);
float calcular_tempo_recarga(float energia);
float calcular_pagamento(float energia);
float carregar_bateria();
float calcular_potencia_dinamica(int carros_ativos);

/* RELATÓRIOS */
void relatorio_sessao(SessaoRecarga sessao);
void relatorio_geral();

/* SISTEMA */
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
    printf("\n====================================\n");
    printf("      ESTAÇÃO DE RECARGA EV\n");
    printf("====================================\n");

    printf("1 - Informações do Posto\n");
    printf("2 - Carregar Carros\n");
    printf("3 - Relatório Geral\n");
    printf("4 - Sair\n");

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
        relatorio_geral();
        break;

    case 4:
        sair_programa();
        break;

    default:
        printf("\n[ERRO] Opção inválida!\n");
    }
}

int ler_int()
{
    int valor;

    while (scanf("%d", &valor) != 1)
    {
        printf("[ERRO] Digite um inteiro válido: ");

        limpar_buffer();
    }

    limpar_buffer();

    return valor;
}

float ler_float()
{
    float valor;

    while (scanf("%f", &valor) != 1)
    {
        printf("[ERRO] Digite um número válido: ");

        limpar_buffer();
    }

    limpar_buffer();

    return valor;
}

void limpar_buffer()
{
    while (getchar() != '\n');
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
    printf("\n====================================\n");
    printf("         POSTOS DISPONÍVEIS\n");
    printf("====================================\n");

    printf("Total de postos: %d\n", MAX_POSTOS);

    printf("Postos disponíveis: %d\n",
           calcular_postos_disponiveis());

    printf("Postos ocupados: %d\n",
           MAX_POSTOS - calcular_postos_disponiveis());
}

void processar_recarga()
{
    int quantidade_carros;

    printf("\nQuantos carros deseja carregar? ");

    do
    {
        quantidade_carros = ler_int();

        if (quantidade_carros <= 0 ||
            quantidade_carros > MAX_POSTOS)
        {
            printf("[ERRO] Digite um valor entre 1 e %d: ",
                   MAX_POSTOS);
        }

    } while (quantidade_carros <= 0 ||
             quantidade_carros > MAX_POSTOS);

    SessaoRecarga sessoes[MAX_POSTOS];

    for (int i = 0; i < quantidade_carros; i++)
    {
        iniciar_sessao(&sessoes[i], i);

        processar_calculos(&sessoes[i], quantidade_carros);

        postos[i].ocupado = 1;

        postos[i].sessao = sessoes[i];

        salvar_sessao(sessoes[i]);

        relatorio_sessao(sessoes[i]);
    }
}

void iniciar_sessao(SessaoRecarga *sessao, int indice)
{
    printf("\n====================================\n");
    printf("            CARRO %d\n", indice + 1);
    printf("====================================\n");

    do
    {
        printf("Capacidade da bateria (kWh): ");

        sessao->capacidade_bateria = ler_float();

        if (!capacidade_valida(
                sessao->capacidade_bateria))
        {
            printf("[ERRO] Valor inválido!\n");
        }

    } while (!capacidade_valida(
        sessao->capacidade_bateria));

    do
    {
        printf("Bateria atual (0%% a 100%%): ");

        sessao->bateria_inicial = ler_float();

        if (!bateria_valida(
                sessao->bateria_inicial))
        {
            printf("[ERRO] Valor inválido!\n");
        }

    } while (!bateria_valida(
        sessao->bateria_inicial));
}

void processar_calculos(SessaoRecarga *sessao, int carros_ativos)
{
    float bateria_kwh;

    bateria_kwh =
        converter_para_kwh(
            sessao->bateria_inicial,
            sessao->capacidade_bateria);

    sessao->energia_necessaria =
        calcular_energia_consumida(
            sessao->capacidade_bateria,
            bateria_kwh);

    sessao->potencia_recebida =
        calcular_potencia_dinamica(
            carros_ativos);
                
    sessao->tempo_recarga =
        calcular_tempo_recarga(
            sessao->energia_necessaria);

    sessao->total_pagar =
        calcular_pagamento(
            sessao->energia_necessaria);

    sessao->bateria_final =
        carregar_bateria();
}

void salvar_sessao(SessaoRecarga sessao)
{
    if (total_sessoes < MAX_SESSOES)
    {
        historico[total_sessoes] = sessao;

        total_sessoes++;
    }
}

int bateria_valida(float bateria)
{
    return bateria >= 0 &&
           bateria <= 100;
}

int capacidade_valida(float capacidade)
{
    return capacidade > 0;
}

float converter_para_kwh(
    float bateria,
    float capacidade)
{
    return (bateria / 100.0f)
           * capacidade;
}

float calcular_energia_consumida(
    float capacidade,
    float bateria_kwh)
{
    return capacidade - bateria_kwh;
}

float calcular_tempo_recarga(float energia)
{
    return (energia / POTENCIA_CARREGADOR)
           * HORAS_EM_MINUTOS;
}

float calcular_pagamento(float energia)
{
    return energia * VALOR_KWH;
}

float carregar_bateria()
{
    return 100.0f;
}

float calcular_potencia_dinamica(int carros_ativos)
{
    if (carros_ativos == 1)
    {
        return 75.0f;
    }

    if (carros_ativos == 2)
    {
        return 60.0f;
    }

    if (carros_ativos == 3)
    {
        return 45.0f;
    }

    return 30.0f;
}

void relatorio_sessao(SessaoRecarga sessao)
{
    printf("\n====================================\n");
    printf("       RELATÓRIO DA RECARGA\n");
    printf("====================================\n");

    printf("Bateria inicial: %.2f%%\n",
           sessao.bateria_inicial);

    printf("Bateria final: %.2f%%\n",
           sessao.bateria_final);

    printf("Capacidade da bateria: %.2f kWh\n",
           sessao.capacidade_bateria);
    
    printf("Potência aplicada: %.2f kW\n",
           sessao.potencia_recebida);

    printf("Energia necessária: %.2f kWh\n",
           sessao.energia_necessaria);

    printf("Tempo estimado: %.2f minutos\n",
           sessao.tempo_recarga);

    printf("Valor total: R$ %.2f\n",
           sessao.total_pagar);
}

void relatorio_geral()
{
    float total_energia = 0;
    float total_valor = 0;
    float total_tempo = 0;
    float media_capacidade = 0;
    float media_potencia = 0;
    float media_bateria = 0;

    if (total_sessoes == 0)
    {
        printf("\n[INFO] Nenhuma sessão registrada.\n");

        return;
    }

    for (int i = 0; i < total_sessoes; i++)
    {
        total_energia +=
            historico[i].energia_necessaria;

        total_valor +=
            historico[i].total_pagar;

        total_tempo +=
            historico[i].tempo_recarga;

        media_capacidade +=
            historico[i].capacidade_bateria;

        media_potencia +=
            historico[i].potencia_recebida;

        media_bateria +=
            historico[i].bateria_inicial;
    }

    media_capacidade /= total_sessoes;

    media_potencia /= total_sessoes;

    media_bateria /= total_sessoes;

    printf("\n====================================\n");
    printf("         RELATÓRIO GERAL\n");
    printf("====================================\n");

    printf("Total de postos: %d\n",
           MAX_POSTOS);

    printf("Postos disponíveis: %d\n",
           calcular_postos_disponiveis());

    printf("Total de sessões: %d\n",
           total_sessoes);

    printf("Energia total consumida: %.2f kWh\n",
           total_energia);

    printf("Valor total arrecadado: R$ %.2f\n",
           total_valor);

    printf("Tempo total de recarga: %.2f min\n",
           total_tempo);

    printf("Média capacidade bateria: %.2f kWh\n",
           media_capacidade);

    printf("Média de potência: %2.f kW\n",
            media_potencia);

    printf("Média bateria inicial: %.2f%%\n",
           media_bateria);
}

void sair_programa()
{
    printf("\n====================================\n");
    printf("       PROGRAMA ENCERRADO\n");
    printf("====================================\n");

    exit(EXIT_SUCCESS);
}