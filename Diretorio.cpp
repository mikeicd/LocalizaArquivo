/* 
 * File:   Diretorio.cpp
 * Author: msobral
 * 
 * Created on 18 de Agosto de 2016, 09:10
 */

#include "Diretorio.h"
#include <sys/types.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>
#include <cstdlib>

ostream& operator<<(ostream & out, Tipo & t) {
    switch (t) {
        case Tipo::Arquivo:
            out << "Arquivo";
            break;
        case Tipo::Blockdev:
            out << "Blockdev";
            break;
        case Tipo::Chardev:
            out << "Chardev";
            break;
        case Tipo::Diretorio:
            out << "Diretorio";
            break;
        case Tipo::Link:
            out << "Link";
            break;
        case Tipo::Programa:
            out << "Programa";
            break;
        case Tipo::Nenhum:
            out << "Nenhum";
            break;
    }

    return out;
}

Entrada::Entrada(const string & basedir, const string& name) {
    nome = name;
    string path = basedir + '/' + name;
    struct stat st;
    
    if (lstat(path.c_str(), &st) < 0) throw errno;

    bytes = st.st_size;
    if (S_ISREG(st.st_mode)) {        
        if (st.st_mode & (S_IXOTH | S_IXGRP | S_IXUSR)) tipo = Tipo::Programa;
        else tipo = Tipo::Arquivo;
    }
    else if (S_ISDIR(st.st_mode)) tipo = Tipo::Diretorio;
    else if (S_ISCHR(st.st_mode)) tipo = Tipo::Chardev;
    else if (S_ISBLK(st.st_mode)) tipo = Tipo::Blockdev;
    else if (S_ISLNK(st.st_mode)) tipo = Tipo::Link;
    else tipo = Tipo::Nenhum;

}

Diretorio::Diretorio() : dir(nullptr), dent(nullptr), path(".") {    
}

Diretorio::Diretorio(const string & pathname) : path(pathname), dir(nullptr), dent(nullptr) {
    Entrada teste(path, ".");
}

Diretorio::Diretorio(const string & pathname, bool criar) : path(pathname), dir(nullptr), dent(nullptr) {
    try {
        Entrada teste(path, ".");
    } catch (int err) {
        if (not criar) throw err;
        if (mkdir(path.c_str(), 0700) < 0) throw errno;
    }
    
}

Diretorio::Diretorio(const Diretorio& orig) {
    *this = orig;
}

Diretorio::~Diretorio() {
    if (dir != nullptr) closedir(dir);
}

Diretorio& Diretorio::operator =(const Diretorio& orig) {
    if (dir != nullptr) closedir(dir);
    path = orig.path;
    dir = nullptr;
    dent = nullptr;
}

void Diretorio::muda(const string& pathname) {
    if (dir != nullptr) closedir(dir);
    if (pathname[0] == '/') path = pathname;
    else {
        path += '/'+pathname;
    }
    dir = nullptr;
    dent = nullptr;
}

unsigned int Diretorio::entradas() const {
    DIR * dp = opendir(path.c_str());
    if (dp == nullptr) return 0;
    
    unsigned int n = 0;
    dirent * ptr;
    while ((ptr = readdir(dp)) != nullptr) n++;
    closedir(dp);
    
    return n;    
}

void Diretorio::inicia_listagem() {
    if (dir != nullptr) closedir(dir);
    dir = opendir(path.c_str());
    if (dir == nullptr) throw -1;
    dent = readdir(dir);
}

Entrada Diretorio::proximo() {
    if (dir == nullptr or dent == nullptr) throw -1;
    dirent * ptr = dent;
    dent = readdir(dir);
    if (dent == nullptr) {
        closedir(dir);
        dir = nullptr;
    }
    
    return Entrada(path, ptr->d_name);
}

bool Diretorio::fim_listagem() const {
    return dent == nullptr;
}

string Diretorio::caminho_absoluto() const {
    char abspath[PATH_MAX];
    
    char * ptr = realpath(path.c_str(), abspath);
    if (ptr != nullptr) return string(ptr);
    throw errno;
}

queue<Entrada> Diretorio::obtem_listagem(const string &subpath) const {
    DIR * subdir = opendir(subpath.c_str());
    queue<Entrada> q;

    if (subdir != nullptr) {
        dirent * d_ent;

        while (d_ent = readdir(subdir)) {
            try {
                Entrada entry(subpath, d_ent->d_name);
                if (entry.nome != "." && entry.nome != "..") q.push(entry);
            } catch(...) {}
        }

        closedir(subdir);
    }

    return q;
}

queue<string> Diretorio::lista_subdiretorios(const string &subpath) const {
    queue<string> r;

    lista_por_tipo(subpath, Tipo::Diretorio, r);

    return r;
}

queue<string> Diretorio::lista_arquivos(const string &subpath) const {
    queue<string> r;

    lista_por_tipo(subpath, Tipo::Arquivo, r);
    lista_por_tipo(subpath, Tipo::Programa, r);

    return r;
}

void Diretorio::lista_por_tipo(const string &subdir, Tipo tipo, queue<string> &r) const {
    auto q = obtem_listagem(subdir);

    while (! q.empty()) {
        auto e = q.front();
        q.pop();
        if (e.tipo == tipo) r.push(e.nome);
    }
}

ostream& operator<<(ostream &out, Entrada &e) {
    out << e.nome << " (tipo=" << e.tipo << ", tamanho=" << e.bytes << ")";
    return out;
}
