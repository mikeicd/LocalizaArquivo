# Manual
O programa deve ser executado em sitemas operacionais Linux. Baixe o arquivo **creatForm** e utilizando o terminal inicie ele conforme o codigo a baixo (certifique-se que o formulário está na raiz onde o programa foi salvo):

`./creatForm form.txt fruta="cebola" legume="tomate"`

O formulário também segue um padrão onde palavras chaves que serão substituidas devem ser escritas com o simbolo $ na frente, ex: Estamos em falta de `$fruta` no estoque.



# Sobre o código
O programa verfica os argumentos inseridos pelo usuário, e os sepera em dois vetores de strigs, o keyWord e o subWord.

É realizado um find para achar a posição do **"="** e assim feito a separação do argumento para savar nos vetores keyWord e subWord.

Após isso é feito a leitura do do formulário e usando o find e replace para achar as palavras no formulário e substituir keyWord por subWord.

No final é feito o print na tela do formulário já alterado.

# Resolução
Creio ter atendido todos os requisitos propostos.