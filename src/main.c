#include <stdio.h>
#include <stdlib.h>

void exibir_estacao_recarga();
void menu_opcoes(int opcao);
void entrada_valor_float(float *valor);
int isBateriaValido(float bateria_inicial);
void verificar_porcentagem_bateria(float bateria_inicial);
int isCapacidadeBateriaValido(float capacidade_bateria);
void verificar_capacidade_bateria(float capacidade_bateria);
float conversao_para_kwh(float bateria_inicial, float capacidade_bateria);
float calcular_energia_consumida(float capacidade_bateria, float bateria_kwh);
float calcular_tempo_recarga(float energia_necessaria);
float calcular_pagamento(float energia_necessaria);
float carregar_bateria();
void relatorio_sessao();

const int POTENCIA_CARREGADOR = 75;
const float VALOR_KWH = 0.8;
const int HORAS_EM_MINUTOS = 60;
float bateria_inicial;
float bateria_final;
float total_pagar;
float energia_necessaria;
float capacidade_bateria;
float temp_recarga;

int main() {
    int opcao;
    float bateria_kwh;

    // Formatação de entrada
    exibir_estacao_recarga();
    scanf("%d", &opcao);
    
    menu_opcoes(opcao);

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

    // Formatação da saída e registros da sessão de recarga
    relatorio_sessao();
    
    return 0;
}

void exibir_estacao_recarga() {
    printf("=================================\n");
    printf("        Estação De Recarga\n");
    printf("1 - Iniciar recarga - 2 - Sair: ");
}

void menu_opcoes(int opcao) {
    switch (opcao)
    {
    case 1:
        printf("\n=================================\n");
        printf("         Sessão iniciada\n");
        printf("Conecte O Carregador Ao Seu Carro\n");

        printf("Digite a capacidade da bateria do seu carro: ");
        entrada_valor_float(&capacidade_bateria);

        printf("Digite a porcentagem da bateria do seu carro: ");
        entrada_valor_float(&bateria_inicial);

        printf("=================================\n\n");
        break;
    case 2:
        exit(0);
        break;
    default:
        printf("Valor inválido");
        exit(0);
        break;
    }
}

void entrada_valor_float(float *valor) {
    if (scanf("%f", valor) != 1) {
        printf("[ERRO]: O valor deve ser numérico!\n");
        exit(0);
    }
}

int isBateriaValido(float bateria_inicial) {
    return bateria_inicial >= 0 &&  bateria_inicial <= 100;
}

void verificar_porcentagem_bateria(float bateria_inicial) {
    if (!isBateriaValido(bateria_inicial)) {
        printf("Valor de Bateria inválido!\n");
        exit(0);
    }
}

int isCapacidadeBateriaValido(float capacidade_bateria) {
    return capacidade_bateria > 0;
}

void verificar_capacidade_bateria(float capacidade_bateria) {
    if (!isCapacidadeBateriaValido(capacidade_bateria)) {
        printf("Capacidade de bateria inválida!\n");
        exit(0);
    }
}

// Função para converter a porcentagem da bateria em kwh
float conversao_para_kwh(float bateria_inicial, float capacidade_bateria) {
    return (bateria_inicial / 100) * capacidade_bateria;
}

float calcular_energia_consumida(float capacidade_bateria, float bateria_kwh) {
    return capacidade_bateria - bateria_kwh;
}

float calcular_tempo_recarga(float energia_necessaria) {
    return (energia_necessaria / POTENCIA_CARREGADOR) * HORAS_EM_MINUTOS;
}

float calcular_pagamento(float energia_necessaria) {
    return energia_necessaria * VALOR_KWH;
}

float carregar_bateria() {
    return 100;
}

void relatorio_sessao() {
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