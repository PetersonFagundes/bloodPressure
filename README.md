# bloodPressure
Measuring Invasive Blood Pressure

Adição de Medição de pressão sanguínea encontrando retornando pressões Diastólica e a Sistólica de um buffer

## Guia de Instalação

Execute no terminal o comando:

```g++ -fPIC -c pressure.cpp```

Para criar a biblioteca entre com:

```g++ -shared -o *nome_da_biblioteca*.so pressure.o```

E então adicione *nome_da_biblioteca*.so ao seu *projeto.cpp*:

```g++ -o *projeto projeto*.o *nome_da_bibliotexa*.so```

## Uso
### Entrada

Declare a classe ```Pressure pressure;``` e então no execute o método ```pressure.Pressures(int* buffer, int size, int index) ```
Onde:

  ```int *buffer``` - pointeiro para a entrada da onda filtrada dada em mmHg
  
  ```int size ``` - tamanho da onda
  
  ```int index``` - ponto escolhido pelo usuário

### Saida
  Será retornado os valores dos índices do intervalo sistólico e diastólico mais próximo do indice escolhido pelo usuário. 
  
  Para retornar os valores use:
  
  
  ```pressure.GetSystolic()``` - Método que retorna um inteiro para o valor do índice Sistólico
  ```pressure.GetDiastolic()```- Método que retorna um inteiro para o valor do índice Diastólico
  

## Menssagens de erro

Se o buffer de entrada for nulo o seguinte erro será exibido:

```throw nullValue;``` - "NULL Pointer";

Se o indice procurado não estiver no buffer:

``` throw pressureException;``` - "Systolic / Diastolic pressure not found.";

