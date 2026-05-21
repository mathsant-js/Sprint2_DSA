#include <stdio.h>
#include <stdlib.h>

//Função para converter a porcentagem da bateria em kwh
float conversao_para_kwh(float bateria_inicial, float capacidade_bateria) {

    return (bateria_inicial / 100) * capacidade_bateria;

}

int main() {

    //Variáveis
    float bateria_inicial;
    float bateria_final;
    float total_pagar;
    float energia_necessaria;
    float capacidade_bateria;
    float temp_recarga;
    int opcao;

    //Formatação de entrada
    printf("=================================\n");
    printf("        Estacao De Recarga\n");
    printf("1 - Iniciar recarga - 2 - Sair: ");
    scanf("%d", &opcao);
    if (opcao == 1)
    {
        printf("=================================\n");
        printf("         Sessao iniciada\n");
        printf("Conecte O Carregador Ao Seu Carro\n");
        printf("Digite a capacidade da bateria do seu carro: ");
        scanf("%f", &capacidade_bateria);
        printf("Digite a porcentagem da bateria do seu carro: ");
        scanf("%f", &bateria_inicial);
        printf("=================================\n");

    }else if (opcao == 2)
    {
        exit(0);
    }
    else
    {
        printf("Valor invalido\n");
        return 0;
    }

    //Verificando se o valor da portcentagem da bateria é válido
    if (bateria_inicial < 0 ||  bateria_inicial > 100)
    {
        printf("Valor Invalido!");
        return 0;
    }

    //Verificando se o valor da capacidade da bateria é válido
    if (capacidade_bateria <= 0)
    {
    printf("Capacidade invalida!\n");
    return 0;
    }

    //Cálculo do total de energia consumida
    energia_necessaria = capacidade_bateria - conversao_para_kwh(bateria_inicial, capacidade_bateria);

    //Tempo de recarga estimado, Potência do carregador: 75kW  
    temp_recarga = (energia_necessaria / 75) * 60;


    //Cálculo da cobrança do carregamento, preço médio do KWh em SP é R$0,80
    total_pagar = energia_necessaria * 0.8;
    
    //Carregamento da bateria
    bateria_final = bateria_inicial;
    while (bateria_final < 100)
    {
        bateria_final ++;
    }

    //Formatação da saída e registros da sessão de recarga
    printf("=============================================\n");
    printf("             Relatorio Da Sessao\n");
    printf("Carga inicial da bateria: %.2f%%\n", bateria_inicial);
    printf("Carga atual da bateria: %.0f%%\n", bateria_final);
    printf("Carga adicionada: %.2f kWh\n", energia_necessaria);
    printf("Preco da recarga: R$%.2f\n", total_pagar);
    printf("Tempo de recarga estimado: %.0f min\n", temp_recarga);
    printf("              Sessao finalizada\n");
    printf("=============================================");
    
    return 0;
}
