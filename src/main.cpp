#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "email.hpp"

int main()
{
    int opt;
    char *arquivo_entrada;
    char *arquivo_saida;

    while ((opt = getopt(argc, argv, "i:I:o:O:s:S:m:M:")) != -1)
    {
        switch (opt)
        {
        case 'i':
        case 'I':
            arquivo_entrada = optarg;
            break;
        case 'o':
        case 'O':
            arquivo_saida = optarg;
        }
    }
    leEntrada(arquivo_entrada);

    return 0; 
}