#include <iostream>
#include <stdio.h>
#include <assert.h>
#include <string.h>


class Email
{
public:
    int id_email;
    int tam; 
    int id_usuario; 
    char msg[200][40];
}; 

class TipoNo
{
public:
    TipoNo();

private:
    Email email;
    TipoNo *esq;
    TipoNo *dir;
    friend class ArvoreBinaria;
};

class ArvoreBinaria
{
public:
    ArvoreBinaria(); 
    // ~ArvoreBinaria();
    void Insere(Email email);
    void Caminha(int tipo);
    Email Pesquisa(int id_email);
    void Remove(int id_email);
    void Limpa();

private:
    void InsereRecursivo(TipoNo *&p, Email email);
    void ApagaRecursivo(TipoNo *p);
    Email PesquisaRecursivo(TipoNo *p, int id_email);
    void RemoveRecursivo(TipoNo *&p, int id_email);
    void Antecessor(TipoNo *q, TipoNo *&r);
    void PorNivel();
    void PreOrdem(TipoNo *p);
    void InOrdem(TipoNo *p);
    void PosOrdem(TipoNo *p);
    TipoNo *raiz;
};

class Hash_LE
{
public:
    Hash_LE(int M); 
    Email Pesquisa(int id_usuario, int id_email);
    void Insere(Email email);
    void Remove(int id_usuario, int id_email);

//private:
    //static const int M; 
    int Hash(int id_usuario);
    ArvoreBinaria *Tabela;
};

void abreEntrada(char *nome_arquivo);
void inicializaHash();
void abreSaida(char *nome_arquivo); 
void processaComandos(); 
void escreveEntrega(Email email); 
void escreveConsulta(Email email); 
bool palavrasSaoIguais(char p1[], char p2[]);
void entrega();
void leMensagem(Email *email); 
void consulta();
void apaga();