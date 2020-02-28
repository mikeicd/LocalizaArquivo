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