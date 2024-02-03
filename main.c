#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


// Definindo a estrutura para Produtos
typedef struct {
  int id;
  float price;
  char name[50];
  char pickupPoint[3];
  char destination[3];
} Product;


// Definindo a estrutura para Paletes (10 produtos)
typedef struct {
  Product products[10];
} Pallet;

// Definindo a estrutura para Pedidos
typedef struct {
  char city[50];
} Order;

// Definindo a estrutura para um caminhão
typedef struct {
  int number;
  Pallet pallets[10];
  Order order;
  int loading_time;
  float total;
  int loading_dock;
  char operationType;
  char departureTime[6];
  char arrivalTime[6];
} Truck;

// Tamanho da fila de caminhões
#define QUEUE_SIZE 10

// Definindo a estrutura de uma fila de caminhões
typedef struct {
  Truck elements[QUEUE_SIZE];
  int front, back;
} Queue;

// Inicializa uma fila de caminhões
void initQueue(Queue *queue) {
  queue->front = -1;
  queue->back = -1;
}

Truck longestDockTimeTruck;

// Verifica se a fila de caminhões está vazia
int isEmpty(Queue *queue) { return (queue->front == -1); }

// Verifica se a fila de caminhões está cheia
int isFull(Queue *queue) {
  return ((queue->back + 1) % QUEUE_SIZE == queue->front);
}

// Adiciona um caminhão à fila
void addToQueue(Queue *queue, Truck truck) {
  if (!isFull(queue)) {
    if (isEmpty(queue)) {
      queue->front = 0;
    }
    queue->back = (queue->back + 1) % QUEUE_SIZE;
    queue->elements[queue->back] = truck;
  } else {
    printf("Fila Cheia, não será possível adicionar mais caminhões.\n");
  }
}

// Remove um caminhão da fila
Truck removeFromQueue(Queue *queue) {
  Truck truck;
  if (!isEmpty(queue)) {
    truck = queue->elements[queue->front];
    if (queue->front == queue->back) {
      queue->front = -1;
      queue->back = -1;
    } else {
      queue->front = (queue->front + 1) % QUEUE_SIZE;
    }
    return truck;
  } else {
    printf("Fila Vazia, não será possível remover Caminhões.\n");
    Truck emptyTruck = {0};
    return emptyTruck;
  }
}

// Função de comparação para ordenar produtos por preço
int checkprices(const void *a, const void *b) {
  Product *productA = (Product *)a;
  Product *productB = (Product *)b;
  if (productA->price < productB->price) {
    return -1;
  } else if (productA->price > productB->price) {
    return 1;
  } else {
    return 0;
  }
}

// Encontra um produto pelo nome em um caminhão
Product findProductByName(Truck truck, const char *name) {
  Product notFoundProduct = {0};  // Produto vazio para indicar que não foi encontrado

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      if (strcmp(truck.pallets[i].products[j].name, name) == 0) {
        return truck.pallets[i].products[j];
      }
    }
  }
  
  return notFoundProduct;  // Retorna um produto vazio indicando que não foi encontrado
}

// Tamanho da pilha de produtos
#define STACK_SIZE 10

// Definindo a estrutura de uma pilha de produtos
typedef struct {
  Product elements[STACK_SIZE];
  int top;
} Stack;

// Inicializa uma pilha de produtos
void startStack(Stack *stack) { stack->top = -1; }

// Verifica se a pilha de produtos está vazia
int isEmptyStack(Stack *stack) { return (stack->top == -1); }

// Verifica se a pilha de produtos está cheia
int isFullStack(Stack *stack) { return (stack->top == STACK_SIZE - 1); }

// Adiciona um produto à pilha
void addToStack(Stack *stack, Product product) {
  if (!isFullStack(stack)) {
    stack->top++;
    stack->elements[stack->top] = product;
  } else {
    printf(
        "Pilha cheia, não será possível adicionar mais produtos na Pilha.\n");
  }
}

// Remove um produto da pilha
Product removeFromStack(Stack *stack) {
  Product product;
  if (!isEmptyStack(stack)) {
    product = stack->elements[stack->top];
    stack->top--;
    return product;
  } else {
    printf("Pilha vazia, não será possível remover produtos da Pilha.\n");
    Product emptyProduct = {0};
    return emptyProduct;
  }
}

// Registra a remoção de um caminhão da fila em um arquivo de log
void logRemoveTruckFromQueue(FILE *logFile, int number) {
  fprintf(logFile, "Caminhão removido da Fila: %d\n", number);
}

// Gera um produto com valores aleatórios
Product generateProduct(int id, char cities[5][3]) {
  Product product;
  product.id = rand() % 1000 + 1;

  float min_price = 10.0;
  float max_price = 1000.0;
  float price_range = max_price - min_price;
  float step = price_range / 10.0;
  product.price = min_price + step * (rand() % 10);

  int cityOriginIndex = rand() % 5;
  int cityDestinationIndex;

  do {
    cityDestinationIndex = rand() % 5;
  } while (cityDestinationIndex == cityOriginIndex);

  char productNames[10][20] = {
      "Televisão",  "Placa Mãe AMD",   "Placa Mãe Intel",  "WaterCooler",
      "Headset",    "Cabo USB Tipo-C", "Memória RAM DDR4", "Memória RAM DDR5",
      "RTX 4090Ti", "RX 7900 XTX"};
  int nameIndex = rand() % 10;
  strcpy(product.name, productNames[nameIndex]);
  strcpy(product.pickupPoint, cities[cityOriginIndex]);
  strcpy(product.destination, cities[cityDestinationIndex]);

  return product;
}

// Preenche um palete com produtos gerados aleatoriamente
void fillPallets(Pallet *pallets, char cities[5][3]) {
  for (int i = 0; i < 10; i++) {
    pallets->products[i] = generateProduct(i + 1, cities);
  }
}

// Gera uma ordem com uma cidade aleatória
Order generateOrder(char cities[5][3]) {
  Order order;
  int cityIndex = rand() % 5;
  strcpy(order.city, cities[cityIndex]);
  return order;
}

// Função para calcular o tempo total gasto na doca por um caminhão
int calculateTotalDockTime(Truck truck) {
  int totalDockTime = 0;
  for (int j = 0; j < 10; j++) {
    totalDockTime +=
        truck.loading_time; // Adiciona o tempo de carregamento do caminhão

    if (totalDockTime >= 100) {
      break; // Encerra o loop se o valor total for maior que ou igual a 100
    }
  }
  return totalDockTime;
}

// Função para encontrar produtos com preço acima de R$ 900,00 em um caminhão
int countHighValueProducts(Truck truck) {
  int count = 0;
  for (int j = 0; j < 10; j++) {
    for (int k = 0; k < 10; k++) {
      if (truck.pallets[j].products[k].price > 900.0) {
        count++;
      }
    }
  }
  return count;
}

// Função para encontrar o produto a ser inspecionado
Product findProductToInspect(Truck trucks[10], int inspectProductIndex) {
  int currentProductIndex = 0;
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      for (int k = 0; k < 10; k++) {
        if (currentProductIndex == inspectProductIndex) {
          return trucks[i].pallets[j].products[k];
        }
        currentProductIndex++;
      }
    }
  }
  Product emptyProduct = {0};
  return emptyProduct;
}

// Cria um arquivo de log com informações sobre os caminhões
void createLog(Truck trucks[10], int inspectProductIndex) {
  FILE *logFile = fopen("log.txt", "w");

  if (logFile == NULL) {
    printf("Erro ao abrir arquivo 'log.txt'.\n");
    return;
  }

  fprintf(logFile, "Informações:\n\n");

  // Caminhão que passou mais tempo na doca
  fprintf(logFile, "Caminhão que passou mais tempo na doca:\n");
  fprintf(logFile, "Caminhão: %d\n", longestDockTimeTruck.number);
  fprintf(logFile, "Tempo total na doca: %d minutos\n",
          calculateTotalDockTime(longestDockTimeTruck));
  fprintf(logFile, "\n");

  int totalProducts = 0; // Variável para rastrear o número total de produtos

  for (int i = 0; i < 10; i++) {
    fprintf(logFile, "\nCaminhão: %d\n", trucks[i].number);
    fprintf(logFile, "Tempo de Carregamento: %d minutos\n",
            calculateTotalDockTime(trucks[i]));
    fprintf(logFile, "Doca responsável pela carga: %d\n",
            trucks[i].loading_dock);
    fprintf(logFile, "Tipo de Operação - Carga (C) / Descarga (D): %c\n",
            trucks[i].operationType);
    fprintf(logFile, "Partida: %s\n", trucks[i].departureTime);
    fprintf(logFile, "Chegada: %s\n", trucks[i].arrivalTime);

    for (int j = 0; j < 10; j++) {
      for (int k = 0; k < 10; k++) {
        totalProducts++; // Incrementa o número total de produtos
        fprintf(logFile, "Produto %d:\n", totalProducts);
        fprintf(logFile, "Nome: %s\n", trucks[i].pallets[j].products[k].name);
        fprintf(logFile, "ID: %d\n", trucks[i].pallets[j].products[k].id);
        fprintf(logFile, "Preço: R$%.2f\n",
                trucks[i].pallets[j].products[k].price);
        fprintf(logFile, "Ponto de Partida: %s\n",
                trucks[i].pallets[j].products[k].pickupPoint);
        fprintf(logFile, "Destino: %s\n",
                trucks[i].pallets[j].products[k].destination);
        fprintf(logFile, "\n");
      }
    }
    fprintf(logFile, "Valor Total transportado: R$%.2f\n", trucks[i].total);
    fprintf(logFile, "Tempo gasto na Doca: %d minutos\n",
            calculateTotalDockTime(trucks[i]));
    fprintf(logFile, "\n");
  }

  fprintf(logFile, "Produto à ser inspecionado:\n");
  Product productToInspect = findProductToInspect(trucks, inspectProductIndex);
  fprintf(logFile, "Produto %d:\n", totalProducts + 1);
  fprintf(logFile, "Nome: %s\n", productToInspect.name);
  fprintf(logFile, "ID: %d\n", productToInspect.id);
  fprintf(logFile, "Preço: R$%.2f\n", productToInspect.price);
  fprintf(logFile, "Ponto de Partida: %s\n", productToInspect.pickupPoint);
  fprintf(logFile, "Destino: %s\n", productToInspect.destination);
  fprintf(logFile, "\n");

  fprintf(logFile, "\nCaminhões com cargas acima de R$ 900.00:\n");
  for (int i = 0; i < 10; i++) {
    int highValueProductsCount = countHighValueProducts(trucks[i]);
    if (highValueProductsCount >= 10) {
      fprintf(logFile, "\nCaminhão: %d\n", trucks[i].number);
      fprintf(logFile, "Produtos acima de R$ 900.00: %d\n",
              highValueProductsCount);
      fprintf(logFile, "\n");
    }
  }

  fclose(logFile);
  printf("Arquivo de log 'log.txt' criado com sucesso.\n");
}

// Função de comparação para ordenar caminhões por valor total transportado
int compareTrucksByTotal(const void *a, const void *b) {
  const Truck *truckA = (const Truck *)a;
  const Truck *truckB = (const Truck *)b;

  if (truckA->total > truckB->total) {
    return -1;
  } else if (truckA->total < truckB->total) {
    return 1;
  } else {
    return 0;
  }
}

int main() {
  srand(time(NULL));
  int compareTrucksByTotal(const void *a, const void *b);
  char cities[5][3] = {"SP", "MG", "SC", "BA", "ES"};

  Truck trucks[10];
  Queue truckQueue;
  initQueue(&truckQueue);

  // Simulação de criação e adição de caminhões à fila
  for (int i = 0; i < 10; i++) {
    trucks[i].number = i + 1;
    trucks[i].loading_time =
        rand() % 60 + 30; // Tempo de carregamento entre 30 e 89 minutos
    trucks[i].loading_dock = rand() % 2 + 1; // Doca de carregamento entre 1 e 2

    // Gere horários de partida e chegada aleatórios entre 08:00 e 18:00
    int departureHour = rand() % 11 + 8; // Entre 8 e 18
    int departureMinute = rand() % 60;
    int arrivalHour = rand() % 11 + 8; // Entre 8 e 18
    int arrivalMinute = rand() % 60;

    sprintf(trucks[i].departureTime, "%02d:%02d", departureHour,
            departureMinute);
    sprintf(trucks[i].arrivalTime, "%02d:%02d", arrivalHour, arrivalMinute);

    // Adicionar a lógica para atribuir o tipo de operação
    if (trucks[i].loading_dock == 1) {
      trucks[i].operationType = 'C'; // Carga
    } else {
      trucks[i].operationType = 'D'; // Descarga
    }

    // Preencher paletes e ordem para o caminhão
    for (int j = 0; j < 10; j++) {
      fillPallets(&trucks[i].pallets[j], cities);
    }

    // Ordenar produtos nos paletes por preço
    for (int j = 0; j < 10; j++) {
      qsort(trucks[i].pallets[j].products, 10, sizeof(Product), checkprices);
    }

    trucks[i].order = generateOrder(cities);

    // Calcular o valor total transportado pelo caminhão
    for (int j = 0; j < 10; j++) {
      for (int k = 0; k < 10; k++) {
        trucks[i].total += trucks[i].pallets[j].products[k].price;
      }
    }

    // Adicionar caminhão à fila
    addToQueue(&truckQueue, trucks[i]);
  }

  // Simulação de remoção de caminhões da fila e geração do arquivo de log
  int inspectProductIndex = rand() % (10 * 10 * 10);
  int logCreated = 0;

  // Ordenar os caminhões pelo valor total transportado
  qsort(trucks, 10, sizeof(Truck), compareTrucksByTotal);

  while (!isEmpty(&truckQueue)) {
    Truck currentTruck = removeFromQueue(&truckQueue);

    // Verifica se o caminhão atual passou mais tempo na doca que o registrado
    if (calculateTotalDockTime(currentTruck) >
        calculateTotalDockTime(longestDockTimeTruck)) {
      longestDockTimeTruck = currentTruck;
    }
    /*
    printf("Caminhão %d removido da fila.\n", currentTruck.number);
    printf("Doca responsável pela carga: %d\n", currentTruck.loading_dock);
    printf("Tempo de carregamento total: %d minutos\n",
           calculateTotalDockTime(currentTruck));
    printf("Total transportado: R$%.2f\n", currentTruck.total);

    // Inspeção do produto
    Product productToInspect =
        findProductToInspect(trucks, inspectProductIndex);
    printf("Produto à ser inspecionado:\n");
    printf("Nome: %s\n", productToInspect.name);
    printf("ID: %d\n", productToInspect.id);
    printf("Preço: R$%.2f\n", productToInspect.price);
    printf("Ponto de Partida: %s\n", productToInspect.pickupPoint);
    printf("Destino: %s\n", productToInspect.destination);
    */
  }

  // Geração do arquivo de log
  if (!logCreated) {
    createLog(trucks, inspectProductIndex);
    logCreated = 1;
  }
  return 0;
}