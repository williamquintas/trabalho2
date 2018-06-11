# Script para testes de unidade automaticos

# A variavel dirtestes indica onde os arquivos teste (.jpg) estao
dirtestes=./imgs_test

# Essas variaveis de contagem devem ser inicializadas com zero
ntestes=0
program=$1

# tests sera inicializada com o resultado da expressao find,
# encontrando todos os arquivos .jpg do diretorio dirtestes
tests=`find $dirtestes -name '*.jpg'`

# Para cada teste...
for t in $tests
do
  # Adiciona 1 no contador de testes
  ntestes=`echo $ntestes + 1 | bc`

  # Executa o programa que foi compilado usando o arquivo de .jpg como
  # entrada
  $program $t $ntestes
done
