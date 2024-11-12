#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#include <string.h>

#define MAX_AGENDAMENTOS 300

// Definição do tipo Consulta usando typedef para simplificar
typedef struct {
    char nome[100];
    int dia;
    int hora;
} Consulta;

// Variáveis globais
Consulta agenda[MAX_AGENDAMENTOS];
int qtdAgendamento = 0;

// Função para verificar a disponibilidade do horário
bool verificarDisponibilidade(int diaAgenda, int horaAgenda) {
    if (horaAgenda <= 7 || horaAgenda >= 21) {
        printf("Clínica fechada neste horário.\n");
        return false;
    }
    return true;
}

// Função para consumir o caractere de nova linha deixado pelo scanf
void limparBuffer() {
    while (getchar() != '\n'); // Limpa o buffer de entrada
}

// Função para agendar consulta
void agendarConsulta() {
    if (qtdAgendamento >= MAX_AGENDAMENTOS) {
        printf("Não é possível agendar mais consultas. Limite atingido.\n");
        return;
    }

    int diaAgenda, horaAgenda;
    
    // Entrada do dia
    printf("Qual dia do mês você quer agendar? ");
    scanf("%d", &diaAgenda);
    
    // Entrada da hora
    printf("Qual hora do dia você quer agendar? ");
    scanf("%d", &horaAgenda);

    // Verificação da disponibilidade do horário
    if (verificarDisponibilidade(diaAgenda, horaAgenda)) {
        printf("Horário disponível! Vamos confirmar seu agendamento.\n");
        
        // Limpeza do buffer de entrada
        limparBuffer();

        // Entrada do nome
        printf("Qual seu nome? ");
        fgets(agenda[qtdAgendamento].nome, sizeof(agenda[qtdAgendamento].nome), stdin);

        // Remover o '\n' extra no final do nome (se houver)
        size_t len = strlen(agenda[qtdAgendamento].nome);
        if (len > 0 && agenda[qtdAgendamento].nome[len - 1] == '\n') {
            agenda[qtdAgendamento].nome[len - 1] = '\0';
        }

        // Registrar o agendamento
        agenda[qtdAgendamento].dia = diaAgenda;
        agenda[qtdAgendamento].hora = horaAgenda;
        qtdAgendamento++;

        printf("Agendamento realizado com sucesso!\n");
    } else {
        printf("Horário não disponível.\n");
    }
}

// Função para listar as consultas agendadas
void listarConsultas() {
    if (qtdAgendamento == 0) {
        printf("Não há consultas agendadas.\n");
        return;
    }

    for (int i = 0; i < qtdAgendamento; i++) {
        printf("==============================\n");
        printf("Nome: %s\n", agenda[i].nome);
        printf("Dia: %d\n", agenda[i].dia);
        printf("Hora: %d\n", agenda[i].hora);
        printf("==============================\n");
    }
}

int main() {
    setlocale(LC_ALL, "");  // Definir a localidade para suportar caracteres acentuados

    int opcao;

    do {
        // Exibição do menu
        printf("==============================\n");
        printf("Qual a opção desejada?\n");
        printf("1 - Agendar\n");
        printf("2 - Listar\n");
        printf("3 - Sair\n");
        printf("==============================\n");        

        // Entrada da opção
        scanf("%d", &opcao);

        // Limpeza do buffer após o scanf
        limparBuffer();

        // Processamento das opções
        switch (opcao) {
            case 1:
                agendarConsulta();
                break;

            case 2:
                listarConsultas();
                break;

            case 3:
                printf("Saindo do programa...\n");
                break;

            default:
                printf("Opção inválida.\n");
                break;
        }
    } while (opcao != 3);

    return 0;
}
