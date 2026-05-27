#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>

void iniciar_menu();
void tela_inicial();
void menu_opcoes(int opcao);
void exibir_posto();
void exibir_estacao_recarga();
void voltar_tela_inicial();
int entrada_valor_int(int *valor);
float entrada_valor_float(float *valor);
void entrada_valor_opcao(char resposta);
void processar_recarga();
int bateria_valido(float bateria_inicial);
void verificar_porcentagem_bateria(float bateria_inicial);
int capacidade_bateria_valido(float capacidade_bateria);
void verificar_capacidade_bateria(float capacidade_bateria);
float conversao_para_kwh(float bateria_inicial, float capacidade_bateria);
float calcular_energia_consumida(float capacidade_bateria, float bateria_kwh);
float calcular_tempo_recarga(float energia_necessaria);
float calcular_pagamento(float energia_necessaria);
void adicionar_carro();
float carregar_bateria();
void iniciar_sessao();
void relatorio_sessao(
    float bateria_inicial,
    float bateria_final,
    float energia_necessaria,
    float total_pagar,
    float temp_recarga);
void sair_programa();

const int POTENCIA_CARREGADOR = 75;
const float VALOR_KWH = 0.8;
const int HORAS_EM_MINUTOS = 60;
int postos_carregamento[5] = {0, 0, 0, 0, 0};
int tamanho_postos_carregamento = sizeof(postos_carregamento) / sizeof(postos_carregamento[0]);
int postos_utilizados = 0;
float bateria_inicial;
float bateria_final;
float total_pagar;
float energia_necessaria;
float capacidade_bateria;
float temp_recarga;

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    iniciar_menu();

    return 0;
}

void iniciar_menu()
{
    int opcao;

    tela_inicial();

    entrada_valor_int(&opcao);

    menu_opcoes(opcao);
}

void tela_inicial()
{
    printf("=================================\n");
    printf("        Bem-Vindo!\n");
    printf("1 - Informações do Posto\n");
    printf("2 - Carregar Carro\n");
    printf("3 - Relatório Geral do Posto\n");
    printf("4 - Sair do Programa\n");
    printf("Digite a opção: ");
}

void exibir_estacao_recarga()
{
    printf("=================================\n");
    printf("        Estação De Recarga\n");

    if (postos_utilizados == tamanho_postos_carregamento)
    {
        printf("1 - Verificar recarga | 2 - Sair: ");
    }
    else
    {
        printf("1 - Iniciar recarga | 2 - Sair: ");
    }
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
        printf("Valor inválido");
        tela_inicial();
        break;
    }
}

int entrada_valor_int(int *valor)
{
    while (scanf("%d", valor) != 1)
    {
        printf("[ERRO]: Digite um número válido: ");

        while (getchar() != '\n')
            ;
    }

    return *valor;
}

float entrada_valor_float(float *valor)
{
    while (scanf("%f", valor) != 1)
    {
        printf("[ERRO]: Digite um número inteiro válido: ");

        while (getchar() != '\n')
            ;
    }

    return *valor;
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

void processar_recarga()
{
    float bateria_kwh;

    // ==== Carregar Carro ====

    // Verificando se o valor da portcentagem da bateria é válido
    verificar_porcentagem_bateria(bateria_inicial);

    // Verificando se o valor da capacidade da bateria é válido
    verificar_capacidade_bateria(capacidade_bateria);

    bateria_kwh = conversao_para_kwh(bateria_inicial, capacidade_bateria);

    // Cálculo do total de energia consumida
    energia_necessaria = calcular_energia_consumida(capacidade_bateria, bateria_kwh);

    // Tempo de recarga estimado, Potência do carregador: 75kW
    temp_recarga = calcular_tempo_recarga(energia_necessaria);

    // Cálculo da cobrança do carregamento, preço médio do KWh em SP é R$0,80
    total_pagar = calcular_pagamento(energia_necessaria);

    // Carregamento da bateria
    bateria_final = carregar_bateria();

    relatorio_sessao(
        bateria_inicial,
        bateria_final,
        energia_necessaria,
        total_pagar,
        temp_recarga);
}

int bateria_valido(float bateria_inicial)
{
    return bateria_inicial >= 0 && bateria_inicial <= 100;
}

void verificar_porcentagem_bateria(float bateria_inicial)
{
    if (!bateria_valido(bateria_inicial))
    {
        printf("Valor de Bateria inválido!\n");
        exit(0);
    }
}

int capacidade_bateria_valido(float capacidade_bateria)
{
    return capacidade_bateria > 0;
}

void verificar_capacidade_bateria(float capacidade_bateria)
{
    if (!capacidade_bateria_valido(capacidade_bateria))
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

void adicionar_carro()
{
    if (postos_utilizados < tamanho_postos_carregamento)
    {
        postos_carregamento[postos_utilizados] = 1;
        postos_utilizados++;
    }
}

float carregar_bateria()
{
    return 100;
}

int calcular_postos_disponiveis()
{
    int postos_disponiveis = 0;
    for (int i = 0; i < tamanho_postos_carregamento; i++)
    {
        if (postos_carregamento[i] == 0)
        {
            postos_disponiveis++;
        }
    }

    return postos_disponiveis;
}

void exibir_posto()
{
    printf("=============================================\n");
    printf("             Postos de Carregamento\n");
    printf("Total de Postos de Carregamento: %d\n", tamanho_postos_carregamento);
    printf("Postos Disponíveis: %d\n", calcular_postos_disponiveis());
    voltar_tela_inicial();
}

void voltar_tela_inicial()
{
    char opcao;

    printf("\n\nVocê deseja voltar a tela inicial?\n");
    printf("s - Sim\n");
    printf("n - Não\n");
    printf("Digite a opção: ");
    scanf(" %c", &opcao);

    entrada_valor_opcao(opcao);
}

void iniciar_sessao()
{
    printf("\n=================================\n");
    printf("         Sessão iniciada\n");
    printf("Conecte O Carregador Ao Seu Carro\n");

    printf("Digite a capacidade da bateria do seu carro: ");
    entrada_valor_float(&capacidade_bateria);

    printf("Digite a porcentagem da bateria do seu carro: ");
    entrada_valor_float(&bateria_inicial);

    printf("=================================\n\n");
}

void relatorio_sessao(
    float bateria_inicial,
    float bateria_final,
    float energia_necessaria,
    float total_pagar,
    float temp_recarga)
{
    printf("=============================================\n");
    printf("             Relatório Da Sessão\n");
    printf("Carga inicial da bateria: %.2f%%\n", bateria_inicial);
    printf("Carga atual da bateria: %.0f%%\n", bateria_final);
    printf("Energia Carregada: %.2f kWh\n", energia_necessaria);
    printf("Preço da recarga: R$%.2f\n", total_pagar);
    printf("Tempo de recarga estimado: %.0f min\n", temp_recarga);
    printf("              Sessão finalizada\n");
    printf("=============================================");
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