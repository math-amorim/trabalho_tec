O objetivo deste trabalho é trabalhar a simulação entre modelos de máquina de Turing, mais especificamente a tradução de Máquinas de Turing definidas por Sipser para Máquinas de Turing Duplamente Infinitas, e vice-versa.
Para isso, implementamos em C++ um tradutor que realiza essas funções pegando um aquivo .in, em que o caminho é definido pelo usuário pela variável de entrada chamada "caminho".

A simulação da execução da MT é realizada no site http://morphett.info/turing/turing.html, portanto o formato da função programa vai ser definido da seguinte maneira:
<br> 
<estado `atual`> <símbolo lido> <novo símbolo> <direção> <novo `estado`>

Para fazer o armazenamento dessas informações, primeiro recebemos o input e realizamos uma função de conversão com base na primeira linha do arquivo.<br> Se a primeira linha for ";S", a tradução será feita de MT Sipser -> MT Duplamente Infinita. Caso primeira linha seja
";I", a tradução é de MT Duplamente Infinita -> MT Sipser.
Após a conversão, o armazenamento é feito em um map<pair<string, string>>, T>. O pair<string,string> é o par de {<estado `atual`>, <símbolo lido>} e vai ser usado como chave para o mapa. Já o T é uma struct composta por 
{string newsy (<novo símbolo>), char d (<direção>), newst (<novo `estado`>)}.

Durante a conversão, adotamos o seguinte padrão:
* § é o símbolo indicador inicial da entrada.
* £ é o símbolo inidicador final da entrada.

Explicação da tradução de MT S -> MT I:<br>
Para essa conversão, seguimos os seguintes passos: <br>
1 - Inicialmente, colocamos o símbolo § no início da entrada, o qual é feito no estado inicial "0". <br>
2 - Substituímos o estado "0" para o novo estado reservado "old0" para cada transição da antiga função onde o estado era presente para que, após o pré-processamento, a MT processo a função programa definida anteriormente normalmente. <br>
3 - Além disso, para todo estado que possuir pelo menos uma transição que realiza um movimento para a esquerda, adicionamos uma nova transição para aquele estado, verificando se ele está lendo o marcador inicial. Caso essa verificação for feita durante uma simulação, 
dizemos que ele escreve o mesmo símbolo, permanece no mesmo estado e realiza um movimento para a direita (simulando um movimento estacionário). <br>
4 - Após conversão, retorna-se a nova função programa. 

Explicação da tradução de MT I -> MT S: <br>
Para essa conversão, seguimos os seguintes passos: <br>
1 - Inicialmente, inserimos o símbolo § e deslocamos todo o conteúdo da fita um espaço a direita. Durante esse processo, utilizamos os novos estados reservados "shift1" e "shift0" para deslocar os 1's e 0's
respectivamente, "set£" para alocar o símbolo £ e "reset" para colocar o cabeçote novamente no início da entrada. Também substituímos o estado "0" por "old0", de forma similiar a tradução MT S -> MT I. <br>
2 - Durante a tradução, caso um estado possua pelo menos uma transição que realize um movimento para a direita, criamos um estado reservado "aux" que é concatenado com o nome do estado que desejo alcançar após a transição.
Nas transições relacionadas ao estado em que se deseja alcançar, também é adicionada uma transição para verificar se o símbolo de final de entrada é lido para que se possa adicionar um espaço em seu lugar e empurrá-lo para direita, sem perder a informação de execução do fluxo do programa. <br>
3 - Caso um estado possua uma transição com movimento para esquerda dentro do seu conjunto de transições, cria-se e adiciona-se novos estados auxiliares que verificam se o símbolo lido é §, adicionam um espaço à sua direita e realizam a lógica de deslocamento do conteúdo da fita para a direita, através dos estados de "shift_" concatenado com o estado que se deseja alcançar concatenado com o símbolo que se deseja deslocar para a direita. 
Os estados reservados  "to_" + "nome do estado", servem para manter a informação para qual estado deve-se retornar após a realização do shift para continuar o processamento da função programa normalmente. <br>
4 - Após a conversão, retorna-se a nova função programa. <br>


A função de output gera um arquivo .out através da nova função programa recebida como parâmetro pelo resultado das funções de tradução e o salva no caminho definido pela variável global chamada "saida" definida juntamente com a variável global "caminho".
