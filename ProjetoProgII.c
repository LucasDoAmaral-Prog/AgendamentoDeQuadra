#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "sporthub.h"

   // Função para pausar antes de voltar ao menu
void pausar() {
    printf("Pressione ENTER para voltar ao menu...\n");
    getchar();
    getchar();
}

        // Função para alugar quadra
int alugarQuadra() { 
    FILE *arq_Agenda = fopen("agenda.txt", "a+");
    if (arq_Agenda == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    int *register_Agenda = malloc(sizeof(int));     // Alocação dinâmica para o RA
    char register_Data[6], register_Hora[12];
    
    // Dados de entrada do usuário
    printf("Digite seu Registro Academico (RA): ");
    scanf("%d", register_Agenda);
    printf("Digite a Data (DD/MM): ");
    scanf("%s", register_Data);

    // Verifica o horário
    int horario_valido = 0;
    while (!horario_valido) {
        printf("Digite a Hora (HH:MM): ");
        scanf("%s", register_Hora);

        // Verifica se o é "redondo"
        if (strlen(register_Hora) >= 5 && register_Hora[3] == '0' && register_Hora[4] == '0') {
            horario_valido = 1;
        } else {
            printf("Horário inválido. Por favor, insira um horário redondo (ex: 14:00).\n");
        }
    }
              // Variáveis para armazenar cada linha do arquivo
    int raFile;
    char dataFile[6], horaFile[12];
    int reserva_existente = 0;

    // Percorre o arquivo e verifica se a reserva já existe
    while (fscanf(arq_Agenda, "%d %s %s", &raFile, dataFile, horaFile) != EOF) {
        if (strcmp(dataFile, register_Data) == 0 && strcmp(horaFile, register_Hora) == 0) {
            printf("Reserva já está ocupada para esta data e horário.\n");
            reserva_existente = 1;
            break;
        }
    }

    if (!reserva_existente) {
        fprintf(arq_Agenda, "%d %s %s\n", *register_Agenda, register_Data, register_Hora);
        printf("Reserva concluída com sucesso.\n");
    }

    free(register_Agenda); 
    fclose(arq_Agenda);
    pausar();
    return 0;
}

// Função para cancelar uma reserva
void alterarAgenda() {
    FILE *arq_Agenda = fopen("agenda.txt", "r");
    if (arq_Agenda == NULL) {
        printf("Nenhuma reserva encontrada.\n");
        pausar();
        return;
    }

    int ra, encontrado = 0;
    printf("Digite seu Registro Academico (RA) para cancelar a reserva: ");
    scanf("%d", &ra);

    FILE *tempFile = fopen("temp.txt", "w");
    int raFile;
    char dataFile[6], horaFile[12];

    while (fscanf(arq_Agenda, "%d %s %s", &raFile, dataFile, horaFile) != EOF) {
        if (raFile == ra) {
            encontrado = 1;
            char confirm[4];
            printf("Reserva encontrada para %s %s. Deseja cancelar? (sim/nao): ", dataFile, horaFile);
            scanf("%s", confirm);
            if (strcmp(confirm, "sim") == 0) {
                printf("Reserva cancelada com sucesso.\n");
                continue;
            }
        }
        fprintf(tempFile, "%d %s %s\n", raFile, dataFile, horaFile);
    }

    fclose(arq_Agenda);
    fclose(tempFile);

    if (!encontrado) {
        printf("Nenhuma reserva encontrada com o RA informado.\n");
    }

    remove("agenda.txt");
    rename("temp.txt", "agenda.txt");
    pausar();
}

// Função para consultar reservas
void consultarAgenda() {
    FILE *arq_Agenda = fopen("agenda.txt", "r");
    if (arq_Agenda == NULL) {
        printf("Nenhuma reserva encontrada.\n");
        pausar();
        return;
    }

    int *ra = malloc(20 * sizeof(int)); // Aloca espaço para até 20 registros de RA
    char (*data)[6] = malloc(20 * sizeof(char[6])); // Aloca espaço para até 20 datas
    char (*hora)[12] = malloc(20 * sizeof(char[12])); // Aloca espaço para até 20 horários
    int count = 0;

    printf("Reservas atuais:\n");
    while (fscanf(arq_Agenda, "%d %s %s", &ra[count], data[count], hora[count]) != EOF) {
        printf("RA: %d, Data: %s, Horário: %s\n", ra[count], data[count], hora[count]);
        count++;
    }
    
    free(ra);
    free(data);
    free(hora);
    fclose(arq_Agenda);
    pausar();
}

// Função recursiva para o menu
void menu() {
    int option_Input;

    printf("Olá, bem-vindo ao SportHub.\n");
    printf("Selecione o número do que deseja fazer hoje:\n");
    printf("1. Alugar quadra\n");
    printf("2. Cancelar reserva\n");
    printf("3. Conferir datas indisponiveis\n");
    printf("4. Sair do programa\n");

    scanf("%d", &option_Input);
    
    switch (option_Input) {
        case 1:
            alugarQuadra();
            break;
        case 2:
            alterarAgenda();
            break;
        case 3:
            consultarAgenda();
            break;
        case 4:
            printf("Encerrando o programa.\n");
            return; // Termina a recursão
        default:
            printf("Opção inválida. Tente novamente.\n");
            pausar();
    }

    menu(); // Chama novamente a função para exibir o menu
}

int main() {
    setlocale(LC_ALL, "Portuguese_Brasil");
    menu(); // Chama a função recursiva de menu
    return 0;
}
