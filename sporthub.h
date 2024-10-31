#ifndef SPORTHUB_H    // Guarda para evitar inclusão múltipla
#define SPORTHUB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Função para pausar antes de retornar ao menu
void pausar();

// Função para alugar quadra
int alugarQuadra();

// Função para cancelar uma reserva
void alterarAgenda();

// Função para consultar reservas
void consultarAgenda();

// Função para exibir o menu principal
void menu();

#endif // SPORTHUB_H
