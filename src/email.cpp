#include "email.hpp"

void leEntrada(char *nome_arquivo)
{
    FILE *entrada = fopen(nome_arquivo, "r");
    assert(entrada && "Arquivo nao encontrado!");
}