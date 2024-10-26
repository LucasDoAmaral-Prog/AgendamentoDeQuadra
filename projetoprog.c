#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <locale.h>

void alterarAgenda(){

    FILE* arq_Agenda;
    arq_Agenda = fopen("agenda.txt","w");
    
}   
void consultarAgenda(){

    FILE* arq_Agenda;
    arq_Agenda = fopen("agenda.txt", "r");
    
}

int alugarQuadra(){ 

    FILE *arq_Agenda;
    arq_Agenda = fopen("agenda.txt", "a+");
    if (arq_Agenda == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    int register_Agenda;
    char register_Data[6], register_Hora[12];
    
    // Dados de entrada do usuário
    printf("Digite seu Registro Academico (RA): ");
    scanf("%d", &register_Agenda);
    printf("Digite a Data (DD/MM): ");
    scanf("%s", register_Data);
    printf("Digite a Hora (HH:MM - HH:MM): ");
    scanf("%s", register_Hora);

    //varia veis para armazenar cada linha do arquivo
    int raFile;
    char dataFile[6], horaFile[12];
    int reserva_existente = 0;

    // Percorre o arquivo e verifica se a reserva já existe
    while (fscanf(arq_Agenda, "%d %s %s", &raFile, dataFile, horaFile) != EOF) {
        if (raFile == register_Agenda && strcmp(dataFile, register_Data) == 0 && strcmp(horaFile, register_Hora) == 0) {
            printf("Reserva já está ocupada para esta data e horário.\n");
            reserva_existente = 1;
            break;
        }
    }

    if (!reserva_existente) {
        fprintf(arq_Agenda, "%d %s %s\n", register_Agenda, register_Data, register_Hora);
        printf("Reserva concluída com sucesso.\n");
    }

    fclose(arq_Agenda);
    return 0;
}

int main(){
    setlocale(LC_ALL, "");
    int option_Input, interval_Option;

    while (option_Input != 4)
    {   
        if(interval_Option == 0){
            printf("Olá, bem vindo ao SportHub.\nSelecione o número do que deseja fazer hoje.\n1. Alugar quadra.\n2. Cancelar reserva\n3.Conferir datas disponíveis.\n4. Sair do programa\n");
        }
        scanf("%d", &option_Input);
        switch (option_Input)
        {
            case 1:
                interval_Option = 1;
                alugarQuadra();
                break;
            case 2:
                alterarAgenda();
                break;
            case 3:
                consultarAgenda();
                break;
            case 4:
                break;  
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    }
    

    return 0;
}