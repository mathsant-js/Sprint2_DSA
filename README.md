# ⚡ Sistema Inteligente de Gerenciamento de Recarga EV

Sistema desenvolvido em linguagem C para simular o gerenciamento de uma estação inteligente de recarga para veículos elétricos.

O projeto implementa múltiplas sessões simultâneas, controle inteligente de potência, tarifação dinâmica, simulação de integração com protocolos industriais e geração de relatórios completos.

Repositório oficial:
[Sprint2_DSA no GitHub](docs/documentacao_projeto.pdf)

# Integrantes

- Bernardo Zauza Amorim | 568808
- Bruno Almeida de Oliveira | 572648
- Gabriel Góes Nunes Pereira | 571735
- Guilherme Vinciguerra Carvalho | 571951
- Marcos Peterson MartinsPereira | 573857
- Matheus Jorge Santana | 574166


# Objetivo do Projeto

O sistema foi desenvolvido com foco em simular funcionalidades presentes em eletropostos modernos, aplicando conceitos de:

* gerenciamento de múltiplos veículos;
* balanceamento de carga elétrica;
* tarifação dinâmica;
* comunicação entre sistemas;
* monitoramento e relatórios.

# Funcionalidades

## Gerenciamento de múltiplas sessões

O sistema suporta múltiplos veículos simultaneamente, permitindo carregar até:

* 5 veículos ao mesmo tempo.

Cada sessão armazena:

* bateria inicial;
* bateria final;
* energia necessária;
* potência aplicada;
* tempo estimado;
* valor total;
* horário da recarga.

# Controle Inteligente de Potência

A potência é ajustada dinamicamente conforme a quantidade de veículos conectados.

| Veículos conectados | Potência aplicada |
| ------------------- | ----------------- |
| 1 veículo           | 75 kW             |
| 2 veículos          | 60 kW             |
| 3 veículos          | 45 kW             |
| 4 ou mais           | 30 kW             |

Esse mecanismo simula sistemas reais de balanceamento de carga.

# Tarifação Dinâmica

O valor do kWh varia conforme o horário informado pelo usuário.

| Horário         | Tarifa      |
| --------------- | ----------- |
| 00h às 06h      | R$ 0,50/kWh |
| 18h às 22h      | R$ 1,20/kWh |
| Demais horários | R$ 0,80/kWh |


# Simulação de Protocolos Industriais

O sistema simula integração com protocolos utilizados no mercado de carregamento EV.

## OCPP

Simulação de envio de:

* energia consumida;
* potência aplicada;
* valor total;
* encerramento da sessão.

## MODBUS

Simulação de envio da potência aplicada ao carregador.


# Relatórios

## Relatório Individual

Após cada sessão, o sistema exibe:

* energia consumida;
* potência aplicada;
* tempo estimado;
* tarifa utilizada;
* valor total da recarga.

## Relatório Geral

O sistema também gera:

* total de sessões;
* energia total consumida;
* valor arrecadado;
* média de potência;
* média das baterias;
* tempo total de recarga.

# Conceitos Aplicados

O projeto utiliza diversos conceitos importantes da linguagem C:

* Structs;
* Vetores;
* Ponteiros;
* Modularização;
* Validação de entradas;
* Controle de fluxo;
* Separação de responsabilidades;
* Simulação de sistemas embarcados.

# Estrutura do Projeto

```bash
main.c
```

O código foi organizado em módulos lógicos:

* Menu;
* Entrada de dados;
* Sessões;
* Cálculos;
* Relatórios;
* Comunicação;
* Validações.

# Como Executar

## Compilar

### GCC (MinGW)

```bash
gcc main.c -o recarga
```

---

## Executar

```bash
./recarga
```

No Windows:

```bash
recarga.exe
```

# Exemplo de Fluxo

```text
1. Usuário escolhe quantidade de veículos
2. Sistema solicita dados da bateria
3. Potência é ajustada automaticamente
4. Tarifa dinâmica é aplicada
5. Sessão é processada
6. Dados são enviados via OCPP/MODBUS
7. Relatórios são exibidos
```