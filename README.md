# Logistics-C
Sistema de logística em C: Simulações de criação, organização e movimentação de caminhões, paletes e produtos. Recursos incluem geração aleatória de caminhões, filas, ordenação, arquivo de log e inspeção de produtos.


# Introdução
Este projeto tem como objetivo simular o gerenciamento logístico de um centro de distribuição, modelando caminhões, produtos, e operações de carga e descarga.
O sistema gerencia a fila de caminhões, produtos em paletes, realiza estatísticas e gera um arquivo de log com informações relevantes.

## Estruturas de Dados
1. **Produtos**
   - Cada produto é representado pela estrutura `Product`, contendo os seguintes campos:
     - `id`: Identificador único do produto.
     - `price`: Preço do produto.
     - `name`: Nome do produto.
     - `pickupPoint`: Ponto de partida do produto.
     - `destination`: Destino do produto.
2. **Palete**
   - A estrutura `Pallet` representa um palete e contém um array de até 10 produtos.
3. **Pedidos**
   - A estrutura `Order` representa um pedido contendo a cidade de destino.
4. **Caminhão**
   - A estrutura `Truck` representa um caminhão e inclui:
     - `number`: Número de identificação do caminhão.
     - `pallets`: Array de paletes transportados pelo caminhão.
     - `order`: Pedido associado ao carregamento do caminhão.
     - `loading_time`: Tempo de carregamento do caminhão.
     - `total`: Valor total transportado pelo caminhão.
     - `loading_dock`: Doca de carregamento utilizada.
     - `operationType`: Tipo de operação (Carga - 'C' ou Descarga - 'D').
     - `departureTime`: Horário de partida do caminhão.
     - `arrivalTime`: Horário de chegada do caminhão.

## Filas e Pilhas
O projeto utiliza uma fila de caminhões (`Queue`) e uma pilha de produtos (`Stack`) para gerenciar a carga e descarga.

1. **Fila de Caminhões**
   - A fila de caminhões (`Queue`) é uma estrutura que mantém a ordem dos caminhões na fila. Contém métodos para inicialização, verificação de vazia ou cheia, adição e remoção de caminhões.
2. **Pilha de Produtos**
   - A pilha de produtos (`Stack`) gerencia a ordem de produtos durante a inspeção. Possui métodos para inicialização, verificação de vazia ou cheia, adição e remoção de produtos.

## Funções Principais
O código implementa funções principais para o gerenciamento da fila de caminhões, pilha de produtos e cálculos relacionados ao tempo e valores.

1. **Gerenciamento da Fila de Caminhões**
   - `initQueue(Queue *queue)`: Inicializa uma fila de caminhões.
   - `isEmpty(Queue *queue)`: Verifica se a fila de caminhões está vazia.
   - `isFull(Queue *queue)`: Verifica se a fila de caminhões está cheia.
   - `addToQueue(Queue *queue, Truck truck)`: Adiciona um caminhão à fila.
   - `removeFromQueue(Queue *queue)`: Remove um caminhão da fila.
2. **Gerenciamento da Pilha de Produtos**
   - `startStack(Stack *stack)`: Inicializa uma pilha de produtos.
   - `isEmptyStack(Stack *stack)`: Verifica se a pilha de produtos está vazia.
   - `isFullStack(Stack *stack)`: Verifica se a pilha de produtos está cheia.
   - `addToStack(Stack *stack, Product product)`: Adiciona um produto à pilha.
   - `removeFromStack(Stack *stack)`: Remove um produto da pilha.
3. **Estatísticas e Geração de Log**
   - `calculateTotalDockTime(Truck truck)`: Calcula o tempo total gasto na doca por um caminhão.
   - `countHighValueProducts(Truck truck)`: Conta produtos de alto valor em um caminhão.
   - `findProductToInspect(Truck trucks[10], int inspectProductIndex)`: Encontra o produto a ser inspecionado.
   - `createLog(Truck trucks[10], int inspectProductIndex)`: Cria um arquivo de log com informações sobre os caminhões.

## Funcionalidades
1. **Simulação**
   - O programa simula a criação de 10 caminhões com produtos aleatórios, tempo de carregamento, doca de carga, horários de partida e chegada. Os produtos são organizados em paletes e ordenados por preço.
2. **Estatísticas**
   - Caminhão com Maior Tempo na Doca: Registra o caminhão que passou mais tempo na doca.
   - Produtos de Alto Valor: Identifica caminhões com mais de 10 produtos de valor acima de R$ 900,00.
   - Produto para Inspeção: Seleciona aleatoriamente um produto para inspeção, registrado no arquivo de log.
3. **Arquivo de Log**
   - Os resultados da simulação são registrados em um arquivo de log chamado `log.txt`, incluindo informações sobre cada caminhão, produtos transportados e estatísticas.

## Compilação e Execução
O projeto pode ser compilado utilizando um compilador C padrão.