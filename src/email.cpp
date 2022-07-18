#include "email.hpp"

FILE *entrada, *saida;
Hash_LE *hash;
int M;

void abreEntrada(char *nome_arquivo)
{
    entrada = fopen(nome_arquivo, "r");
    assert(entrada && "Arquivo nao encontrado!");
}
void inicializaHash()
{
    fscanf(entrada, "%d\n", &M);
    hash = new Hash_LE(M);
}

void processaComandos()
{
    char comando[10];
    while (fscanf(entrada, "%s\n", comando) == 1)
    {
        if (feof(entrada))
            break;
        if (palavrasSaoIguais(comando, "ENTREGA"))
            entrega();
        else if (palavrasSaoIguais(comando, "CONSULTA"))
            consulta();
        else if (palavrasSaoIguais(comando, "APAGA"))
            apaga();
    }
}

void entrega()
{
    Email email;
    fscanf(entrada, "%d %d %d\n", &email.id_usuario, &email.id_email, &email.tam);
    leMensagem(&email);
    hash->Insere(email);
    escreveEntrega(email);
}

void consulta()
{
    int id_user, id_email;
    fscanf(entrada, "%d %d", &id_user, &id_email);
    fprintf(saida, "CONSULTA %d %d: ", id_user, id_email);
    Email aux = hash->Pesquisa(id_user, id_email);
    if(aux.id_usuario != id_user || aux.id_email != id_email)
        aux.id_email = -1; 
    escreveConsulta(aux);
}

void apaga()
{
    int id_user, id_email;
    fscanf(entrada, "%d %d", &id_user, &id_email);
    hash->Remove(id_user, id_email);
}

void leMensagem(Email *email)
{
    for (int i = 0; i < email->tam; i++)
        fscanf(entrada, "%s ", email->msg[i]);
}

bool palavrasSaoIguais(char p1[], char p2[])
{
    if (strcmp(p1, p2) == 0)
        return true;
    return false;
}

void abreSaida(char *nome_arquivo)
{
    if (!saida)
    {
        saida = fopen(nome_arquivo, "w");
        assert(saida && "Falha em abrir o arquivo!");
    }
}

void escreveEntrega(Email email)
{
    fprintf(saida, "OK: MENSAGEM %d PARA %d ARMAZENADA EM %d\n", email.id_email, email.id_usuario, hash->Hash(email.id_usuario));
}

void escreveConsulta(Email email)
{
    if (email.id_email == -1)
        fprintf(saida, "MENSAGEM INEXISTENTE\n");
    else
    {
        for (int i = 0; i < email.tam; i++)
        {
            if (i != email.tam - 1)
                fprintf(saida, "%s ", email.msg[i]);
            else
                fprintf(saida, "%s\n", email.msg[i]);
        }
    }
}

TipoNo::TipoNo()
{
    email.id_email = -1;
    esq = NULL;
    dir = NULL;
}

ArvoreBinaria::ArvoreBinaria()
{
    raiz = NULL;
}

Email ArvoreBinaria::Pesquisa(int id_email)
{
    return PesquisaRecursivo(raiz, id_email);
}

Email ArvoreBinaria::PesquisaRecursivo(TipoNo *no, int id_email)
{
    Email aux;
    if (no == NULL)
    {
        aux.id_email = -1; // Flag para item não presente
        return aux;
    }
    if (id_email < no->email.id_email)
        return PesquisaRecursivo(no->esq, id_email);
    else if (id_email > no->email.id_email)
        return PesquisaRecursivo(no->dir, id_email);
    else
        return no->email;
}

void ArvoreBinaria::Insere(Email email)
{
    InsereRecursivo(raiz, email);
}

void ArvoreBinaria::InsereRecursivo(TipoNo *&p, Email email)
{
    if (p == NULL)
    {
        p = new TipoNo();
        p->email = email;
    }
    else
    {
        if (email.id_email < p->email.id_email)
            InsereRecursivo(p->esq, email);
        else
            InsereRecursivo(p->dir, email);
    }
}

void ArvoreBinaria::Antecessor(TipoNo *q, TipoNo *&r)
{
    if (r->dir != NULL)
    {
        Antecessor(q, r->dir);
        return;
    }
    q->email = r->email;
    q = r;
    r = r->esq;
    free(q);
}

void ArvoreBinaria::Remove(int id_email)
{
    return RemoveRecursivo(raiz, id_email);
}
void ArvoreBinaria::RemoveRecursivo(TipoNo *&no, int id_email)
{
    TipoNo *aux;
    if (no == NULL)
    {
        fprintf(saida, "ERRO: MENSAGEM INEXISTENTE\n");
        return; 
    }
    if (id_email < no->email.id_email)
        return RemoveRecursivo(no->esq, id_email);
    else if (id_email > no->email.id_email)
        return RemoveRecursivo(no->dir, id_email);
    else
    {

        if (no->dir == NULL)
        {
            aux = no;
            no = no->esq;
            free(aux);
        }
        else if (no->esq == NULL)
        {
            aux = no;
            no = no->dir;
            free(aux);
        }
        else
            Antecessor(no, no->esq);
        fprintf(saida, "OK: MENSAGEM APAGADA\n");
    }
}

Hash_LE::Hash_LE(int M)
{
    this->Tabela = new ArvoreBinaria[M];
    for (int i = 0; i < M; i++)
    {
        ArvoreBinaria a;
        Tabela[i] = a;
    }
}

int Hash_LE::Hash(int id_usuario)
{
    return id_usuario % M;
}

Email Hash_LE::Pesquisa(int id_usuario, int id_email)
{
    int pos = Hash(id_usuario);
    Email email = Tabela[pos].Pesquisa(id_email);
    return email;
}

void Hash_LE::Insere(Email email)
{
    int pos = Hash(email.id_usuario);
    Tabela[pos].Insere(email);
}

void Hash_LE::Remove(int id_usuario, int id_email)
{
    int pos = Hash(id_usuario);
    Tabela[pos].Remove(id_email);
}