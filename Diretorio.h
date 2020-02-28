/* 
 * File:   Diretorio.h
 * Author: msobral
 *
 * Created on 18 de Agosto de 2016, 09:10
 */

#ifndef DIRETORIO_H
#define	DIRETORIO_H

#include <sys/types.h>
#include <dirent.h>
#include <queue>

#include "tipos.h"

using std::queue;

// classe que representa diretórios
class Diretorio {
public:
    // construtores
    
    // cria um diretório associado ao diretório atual
    Diretorio();
    
    // cria um diretório com caminho "pathname". Se caminho
    // não existir, ou não puder ser acessado, dispara uma
    // exceção de valor inteiro
    Diretorio(const string & pathname);
    
    // cria um diretório com caminho "pathname". Se caminho
    // não existir ou não puder ser acessado, e block for false, 
    // dispara uma exceção de valor inteiro.
    // se block for true, tenta criar o diretório (se não
    // conseguir, dispara a exceção)
    Diretorio(const string & pathname, bool criar);
    Diretorio(const Diretorio& orig);
    
    // destrutor
    virtual ~Diretorio();
    
    // operador de atribuição
    Diretorio& operator=(const Diretorio & orig);
    
    // muda de diretório
    void muda(const string & pathname);
    
    // retorna a quantidade de entradas neste diretório
    unsigned int entradas() const;
    
    // retorna o caminho deste diretório
    string caminho() const { return path;}
    
    // retorna o caminho absoluto deste diretório
    string caminho_absoluto() const;

    // métodos para listar um diretório

    // obtém a listagem de entradas contidas no subdiretório indicado em subpath (default: diretório atual)
    queue<Entrada> obtem_listagem(const string & subpath=".") const;

    // obtém a listagem de subdiretórios existentes dentro do subdiretório indicado em subpath (default: diretório atual)
    queue<string> lista_subdiretorios(const string & subpath=".") const;

    // obtém a listagem de arquivos existentes dentro do subdiretório indicado em subpath (default: diretório atual)
    queue<string> lista_arquivos(const string & subpath=".") const;

    // inicia a listagem: deve ser invocado em primeiro lugar
    // se diretório não existir, ou não puder ser acessado,
    // dispara uma exceção de valor inteiro    
    void inicia_listagem();
    
    // obtém próxima entrada de diretório
    // se não houver iniciado a listagem, ou listagem 
    // chegou ao fim, dispara uma exceção de valor inteiro
    Entrada proximo();
    
    // testa se listagem chegou ao fim
    bool fim_listagem() const;
        
private:
    // atributos da classe: cada objeto desta classe
    // possui estes três atributos
    string path;
    DIR * dir;
    dirent * dent;

    void lista_por_tipo(const string & subdir, Tipo tipo, queue<string> & q) const;
};

ostream& operator<<(ostream & out, Entrada & e);

#endif	/* DIRETORIO_H */

