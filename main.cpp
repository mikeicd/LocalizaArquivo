#include <iostream>
#include <queue>
#include <stack>
#include "Diretorio.h"

using namespace std;

//Função para adicionar a fila de subdiretórios à pilha de subdiretórios.
void queueToStack(stack<string>& x, Diretorio& dir, string& aux) {
    queue<string> q = dir.lista_subdiretorios(aux);
    while (!q.empty()) {
         x.push(aux+"/"+q.front());
        q.pop();
    }
}

//Função para verificar se o arquivo desejado está da fila.
bool checkFile(queue<string>& q, string& file) {
    while (!q.empty()){
        if (q.front()==file){
            return true;
        }
        q.pop();
    }
    return false;
}


int main(int argc, char *argv[]) {
    Diretorio dir;
    stack<string> paths;

    if (argc != 3){
        cout << "Numeros de argumentos incorreto..." << endl;
        return 3;
    }

    std::string path(argv[1]);
    std::string file(argv[2]);


    paths.push(path);


    while (!paths.empty()) {
        path = paths.top();
        paths.pop();

        cout << "Procurando em: " + path << endl;

        //Cria uma lista de arquivos do 1º item da pilha e verifica com a função checkFile..
        queue<string> files = dir.lista_arquivos(path);
        if (checkFile(files,file)){
            cout << "Caminho do arquivo: " + path + "/" + file << endl;
            return 1;
        } else {
            //Lista os subdiretórios e adiciona a pilha...
            queueToStack(paths,dir, path);
        }
    }
    cout << "Arquivo não encontrado" << endl;
    return 0;
}