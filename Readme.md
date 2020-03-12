# Manual
O programa deve ser executado em sitemas operacionais Linux.

Deve-se passar 2 argumentos para o programa, o primeiro deve ser o diretório que será feito a procura e o segundo argumento é o arquivo que deseja localizar.

Ex:  './main /home teste.txt'

# Sobre o código
O programa recebe dois argumentos o primeiro é a raiz onde começa a procura do arquivo e o segundo é o nome do arquivo a ser encontrado. É utilizado um sistema de pilha para varrer os diretórios, a cada diretório é criado uma fila com todos os arquivos deste diretório e é verificado se algum deles é o arquivo desejado. Ao final o programa mostra se, e onde o arquivo foi encontrado.

# Perguntas
O que foi efetivamente realizado ?
- Verificação se foi passados os 2 argumentos;
- Criação de pilha para armazenamento dos diretórios;
- Criação de uma fila de arquivos de cada diretório;
- Verificação se a fila possui o arquivo desejado;
  - Se verdadeiro: Mostra o caminho do arquivo;
  - Se falso: Adiciona os subdiretórios adjacentes a pilha;
- Caso não encontrar o arquivo é notificado;

O que faltou realizar ?
- Nada;

O que o impediu de realizar plenamente o exercício ?
- Nada.
