#include <stdio.h>
#include <stdlib.h>


typedef struct Fila{
  int processId;
  int remainingTime;
  int totalTime;
  struct Fila* next;
} Fila;

Fila* f;

void Enfileira(int processId, int remainingTime, int totalTime){
  if (!f){
    f = malloc(sizeof(Fila));

    f->processId = processId;
    f->remainingTime = remainingTime;
    f->totalTime = totalTime;
    f->next = NULL;
    
    return;
  }
  
  Fila* temp = f;
  while (temp->next)  temp = temp->next;

  temp->next = malloc(sizeof(Fila));
  temp->next->processId = processId;
  temp->next->remainingTime = remainingTime;
  temp->next->totalTime = totalTime;
  temp->next->next = NULL;
}

int Desenfileira(){
  int tempID;
  if (!f->next){
    tempID = f->processId;
    free(f);
    
    return tempID;
  }

  Fila* temp = f->next;
  tempID = f->processId;
  free(f);
  f = temp;

  return tempID;
}

void moveToEnd() {
  if (!f || !f->next) return;

  Enfileira(f->processId, f->remainingTime, f->totalTime);
  Desenfileira();
}

int main() {
  int numProcesses, currentTime = 0, totalRemainingTime = 0;

  scanf("%d", &numProcesses);
  
  int* numInstructions = malloc(numProcesses * sizeof(int));
  int** instructionMatrix = malloc(numProcesses * sizeof(int *));

  for(int i = 0; i < numProcesses; i++){
    scanf("%d", &numInstructions[i]);

    Enfileira(i, numInstructions[i] * 10, numInstructions[i] * 10);
    totalRemainingTime += numInstructions[i] * 10;
    instructionMatrix[i] = malloc(numInstructions[i] * sizeof(int));
  }

  for(int i = 0; i < numProcesses; i++){
    for(int j = 0; j < numInstructions[i]; j++){
      scanf("%d", &instructionMatrix[i][j]);
    }
  }

  while (totalRemainingTime > 0){
    if (f->remainingTime == 0){
      int finishedProcess = Desenfileira();
      printf("%d (%d)\n", finishedProcess + 1, currentTime);
    }

    int procX = f->processId;
    int procY = (f->totalTime - f->remainingTime) / 10;

    if (instructionMatrix[procX][procY] == 0){
      currentTime += 10;
      totalRemainingTime -= 10;
      f->remainingTime -= 10;
    } else if (instructionMatrix[procX][procY] == 1){
      instructionMatrix[procX][procY] = 0;
      moveToEnd();
    }
  }

  int finishedProcess = Desenfileira();
  
  printf("%d (%d)\n", finishedProcess + 1, currentTime);

  return 0;
}
