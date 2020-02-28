# Localizador de arquivo

Escreva um programa que localize um arquivo dentro de uma árvore de diretórios. A busca deve iniciar em algum subdiretório a ser informado, e ela termina ao encontrar o arquivo (ou se não encontrá-lo !). Ao localizar o arquivo procurado, deve ser informado o caminho seguido até encontrá-lo. O diretório inicial e o nome do arquivo devem ser fornecidos, respectivamente, no primeiro e segundo argumentos de linha de comando.

Um programa que localiza arquivos faz uma busca a partir de um subdiretório (ou pasta). Os subdiretórios são organizados hierarquicamente, formando uma estrutura conhecida como [árvore](https://pt.wikipedia.org/wiki/%C3%81rvore_(estrutura_de_dados)), como ilustrada a seguir.

![Árvore de diretórios](http://tele.sj.ifsc.edu.br/~msobral/prg2/imagens/src_tree.png)

*Um exemplo de uma pequena árvore de diretórios*  

Como dentro de um subdiretório, além de arquivos, possivelmente existem outros subdiretórios, a busca deve explorá-los sistematicamente. Cada subdiretório deve ser inspecionado uma única vez e, caso o arquivo seja localizado, deve ser apresentado o caminho percorrido até sua localização. Um algoritmo de busca se faz necessário, e para essa finalidade a [busca em profundidade](https://pt.wikipedia.org/wiki/Busca_em_profundidade) se mostra adequada.

![Algoritmo de busca em profundidade (DFS)](http://tele.sj.ifsc.edu.br/~msobral/prg2/imagens/dfs.gif)

*Representação visual de uma busca em profundidade. FONTE:* [Wikipedia](https://pt.wikipedia.org/wiki/Busca_em_profundidade).

# Algoritmo de busca em profundidade

O algoritmo de busca em profundidade, pode ser implementado usando uma pilha, onde se armazenam os nomes dos próximos subdiretórios a visitar. Este pseudo-código apresenta a estrutura genérica desse algoritmo:

```
algoritmo busca_dfs():
  cria uma pilha
  empilha o nó inicial
  enquanto pilha não vazia
    desempilha um nó
    se for o nó procurado, então retorna o valor do nó
    para cada nó adjacente ao nó desempilhado
      empilha nó adjacente
```

Observe que esse algoritmo se refere ao conceito de *nó*, que representa cada junção no diagrama pesquisado (no caso, seriam os subdiretórios). Além disso, para fazer a busca por um arquivo, uma pequena adaptação precisa ser feita, pois o que se deseja não é necessariamente encontrar um *subdiretório* (*nó*), e sim um arquivo contido em um subdiretório.

# Como listar arquivos e subdiretórios

A listagem de diretórios pode ser feita usando a classe *Diretorio*, a qual está declarada em *Diretorio.h*. Um objeto dessa classe possibilita listar arquivos e subdiretórios, o que é necessário para o algoritmo de busca.

```c++
// classe que representa diretórios
class Diretorio {
public:
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
};
```

Um exemplo de uso dessa classe é apresentado a seguir. Ele mostra como listar arquivos e subdiretórios dentro de um subdiretório específico (no caso, */home/aluno*). Veja a descrição da classe *Diretorio* para conhecer outras formas de usá-la.  

```c++
#include <iostream>
#include "Diretorio.h"

using namespace std;

void mostra_fila(queue<string> & q) {
    while (! q.empty()) {
        string e = q.front();
        q.pop();
        if (q.empty()) cout << e;
        else cout << e << ", ";
    }
}

int main() {
    Diretorio dir;

    queue<string> q1 = dir.lista_subdiretorios("/home/aluno");
    queue<string> q2 = dir.lista_arquivos("/home/aluno");

    cout << "Subdiretórios: ";
    mostra_fila(q1);

    cout << endl;
    cout << "Arquivos: ";
    mostra_fila(q2);
}
```