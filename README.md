# Diagnóstico de catarata
Projeto busca detectar através de uma imagem se um olho possui ou não catarata. 

## Executando projeto
### Como compilar
 * make
 * ./catarata​ ​-i​ images/NomeImage.ppm​ -f​ ppm​ -o​​ diagnostico.txt 

### Apagar arquivos gerados pela execução
* make clean

## Funcionalidades básicas
* Transformação da imagem colorida para tons de cinza.
* Aplicação do filtro gaussiano e do sobel e a binarização.
* Transformação de Hough
* Classificação

## Funcionalidades extras
* Classificação é feita utilizando imagem colorida. 

## Observações
Todos os processos estão bem separados para uma melhor compreenção do código.
Algumas partes poderiam ser unidas, diminuindo o tempo de execução.  
Exemplo: transformação de Hough e a classificação. 