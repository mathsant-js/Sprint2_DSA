#include <stdio.h>
#include <stdlib.h>

void exibir_estacao_recarga();
void menu_opcoes(int opcao);
int isBateriaValido(float bateria_inicial);
void verificar_porcentagem_bateria(int isBateriaValido());
int isCapacidadeBateriaValido(float capacidade_bateria);
int verificar_capacidade_bateria(int (*isCapacidadeBateriaValido)(float));
float conversao_para_kwh(float bateria_inicial, float capacidade_bateria);
float calcular_energia_consumida(float capacidade_bateria, float bateria_kwh);
float calcular_tempo_recarga(float energia_necessaria);
float calcular_pagamento(float energia_necessaria);
float carregar_bateria(float bateria_inicial);
void relatorio_sessao();

float bateria_inicial;
float bateria_final;
float total_pagar;
float energia_necessaria;
float capacidade_bateria;
float temp_recarga;

int main() {
    int opcao;

    // Formatação de entrada
    exibir_estacao_recarga();
    scanf("%d", &opcao);
    
    menu_opcoes(opcao);

    // Verificando se o valor da portcentagem da bateria é válido
    verificar_porcentagem_bateria(!isBateriaValido, bateria_inicial);

    // Verificando se o valor da capacidade da bateria é válido
    verificar_capacidade_bateria(!isCapacidadeBateriaValido, capacidade_bateria);

    //Cálculo do total de energia consumida
    energia_necessaria = calcular_energia_consumida(capacidade_bateria, conversao_para_kwh(bateria_inicial, capacidade_bateria));

    //Tempo de recarga estimado, Potência do carregador: 75kW  
    temp_recarga = calcular_tempo_recarga(energia_necessaria);

    //Cálculo da cobrança do carregamento, preço médio do KWh em SP é R$0,80
    total_pagar = calcular_pagamento(energia_necessaria);
    
    // Carregamento da bateria
    bateria_final = carregar_bateria(bateria_inicial);

    //Formatação da saída e registros da sessão de recarga
    relatorio_sessao();
    
    return 0;
}

void exibir_estacao_recarga() {
    printf("=================================\n");
    printf("        Estacao De Recarga\n");
    printf("1 - Iniciar recarga - 2 - Sair: ");
}

void menu_opcoes(int opcao) {
    switch (opcao)
    {
    case 1:
        printf("=================================\n");
        printf("         Sessao iniciada\n");
        printf("Conecte O Carregador Ao Seu Carro\n");
        printf("Digite a capacidade da bateria do seu carro: ");
        scanf("%f", &capacidade_bateria);
        printf("Digite a porcentagem da bateria do seu carro: ");
        scanf("%f", &bateria_inicial);
        printf("=================================\n");
        break;
    case 2:
        exit(0);
        break;
    default:
        printf("Valor inválido");
        break;
    }
}

int isBateriaValido(float bateria_inicial) {
    return bateria_inicial > 0 ||  bateria_inicial < 100;
}

void verificar_porcentagem_bateria(int (*isBateriaValido)(float)) {
    if (!isBateriaValido(bateria_inicial)) {
        printf("Valor de Bateria inválido!\n");
    }
}

int isCapacidadeBateriaValido(float capacidade_bateria) {
    return capacidade_bateria >= 0;
}

int verificar_capacidade_bateria(int (*isCapacidadeBateriaValido)(float)) {
    if (!isCapacidadeBateriaValido(capacidade_bateria)) {
        printf("Capacidade inválida!\n");
    }
}

//Função para converter a porcentagem da bateria em kwh
float conversao_para_kwh(float bateria_inicial, float capacidade_bateria) {
    return (bateria_inicial / 100) * capacidade_bateria;
}

float calcular_energia_consumida(float capacidade_bateria, float bateria_kwh) {
    return capacidade_bateria - bateria_kwh;
}

float calcular_tempo_recarga(float energia_necessaria) {
    return (energia_necessaria / 75) * 60;
}

float calcular_pagamento(float energia_necessaria) {
    return energia_necessaria * 0.8;
}

float carregar_bateria(float bateria_inicial) {
    while (bateria_inicial < 100)
    {
        bateria_inicial++;
    }
    return bateria_inicial;
}

void relatorio_sessao() {
    printf("=============================================\n");
    printf("             Relatorio Da Sessao\n");
    printf("Carga inicial da bateria: %.2f%%\n", bateria_inicial);
    printf("Carga atual da bateria: %.0f%%\n", bateria_final);
    printf("Carga adicionada: %.2f kWh\n", energia_necessaria);
    printf("Preco da recarga: R$%.2f\n", total_pagar);
    printf("Tempo de recarga estimado: %.0f min\n", temp_recarga);
    printf("              Sessao finalizada\n");
    printf("=============================================");
}