#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char name[20];
    int starting_time;
    int remaining_time;
}Process;

typedef struct Node{
    Process data;
    struct Node *next;
}Node;

typedef struct{
    Node *front, *rear;
}Queue;

Queue* init(){
    Queue* Q = (Queue*)malloc(sizeof(Queue));
    Q->front = NULL;                                // set the front to null because no nodes has been added yet
    Q->rear = NULL;
    return Q;                                       // return the initialized queue
}

int isEmpty(Queue* Q){
    if(Q->front == NULL)     return 1;
    else                     return 0;
}

Node* newNode (Process P){
    Node* N = (Node*)malloc(sizeof(Node));
    N->data = P;
    N->next = NULL;
    return N;
}

void enqueue(Queue* Q, Process P){
    Node* tempNode = newNode(P);
    if (isEmpty(Q))         Q->front = Q->rear = tempNode;
    else{
        Q->rear->next = tempNode;
        Q->rear = tempNode;
    }
}

Process* dequeue(Queue* Q){
    if (!isEmpty(Q)){
        Process* dequeuedProcess = (Process*)malloc(sizeof(Process));
        Node* TempNode = Q->front;
        *dequeuedProcess = TempNode->data;
        Q->front = TempNode->next;
        free(TempNode);
        if (Q->front)           Q->rear = NULL;
        return dequeuedProcess;
    }
    else                printf("The queue is empty!!!\n");
}

void destroyQueue(Queue* Q){
    Node* temporaryNode;
    if(isEmpty(Q)){
        free(Q);
        return;
    }
    while (!isEmpty(Q)){
        temporaryNode = Q->front;
        Q->front = Q->front->next;
        free(temporaryNode);
    }
    free(Q);
    return;
}

int lineCounter(char* filename){
    char characterCounter;
    int numberOfLines = 0;
    FILE* filePointer;
    filePointer = fopen(filename, "r");
    if (filePointer == NULL){
        printf ("The text file is corrupted");
        return 0;
    }
    else if (filePointer != NULL){
        for (characterCounter= getc(filePointer); characterCounter != EOF; characterCounter = getc(filePointer))
        if (characterCounter == '\n')               numberOfLines++;
        fclose(filePointer);
        return numberOfLines;
    }
}

Process* Load(char* fileName, int* timeSlots, int* sizeOfArray){
    *sizeOfArray = lineCounter(fileName);
    *timeSlots = 0;
    int i = 0;
    char tempString[100];
    Process *arrayOfProcesses = (Process *) malloc(sizeof(Process) **sizeOfArray);
    FILE *filePointer;
    filePointer = fopen(fileName, "r");
    fscanf(filePointer, "%[^=]=", tempString);
    fscanf(filePointer, "%[^\n]\n", tempString);
    *timeSlots = atoi(tempString);
    while (!feof(filePointer)){
        fscanf(filePointer, "%[^ ] ", tempString);
        strcpy(arrayOfProcesses[i].name, tempString);
        fscanf(filePointer, "%[^ ] ", tempString);
        arrayOfProcesses[i].starting_time = atoi(tempString);
        fscanf(filePointer, "%[^\n]\n", tempString);
        arrayOfProcesses[i].remaining_time = atoi(tempString);
        i++;
    }
    fclose(filePointer);
    return arrayOfProcesses;
}

void printing (Queue* Q, int counter){
    for (int i= 0 ;i <counter ; i++ ) {
        Process *temp;
        temp = dequeue(Q);
        if (strcmp(temp->name, "idle") == 0 )     printf("idle\t(%d-->%d)\n",i,(i+1));
        else {
            printf("%s\t(%d-->%d)",temp->name,i,(i+1));
            if(temp->remaining_time>1)              printf("\n");
            else if(temp->remaining_time == 1)      printf("\t\t%s aborts\n", temp->name);
        }
    }
    printf("stop");
}

void roundRobin(char* fileName) {
    int sizeOfArray;
    int timeSlots ;
    int i = 0, j = 0;
    int flag = 0;
    Process* arrayOfProcesses = Load(fileName, &timeSlots, &sizeOfArray);
    Queue *q = init();
    int counter = 0;
    Process temp;
    for (i = 0; i < timeSlots && counter < timeSlots; i++, flag = 0) {
        for (j = 0; j < sizeOfArray; j++) {
            if (arrayOfProcesses[j].starting_time == i && arrayOfProcesses[j].remaining_time > 0) {
                enqueue(q, arrayOfProcesses[j]);
                flag = 1;
                arrayOfProcesses[j].remaining_time--;
                arrayOfProcesses[j].starting_time++;
                counter++;
                continue;
            }
        }
        if (flag == 0){
            strcpy(temp.name, "idle");
            enqueue(q, temp);
            counter++;
        }
    }
    printing(q,counter);
}

int main() {
    char filename[261];
    puts("Enter file name or Ctrl+Z to exit:");
    puts("----------------------------------");
    while(fgets(filename, 260, stdin) != NULL)
    {
        filename[strlen(filename)-1]='\0';
        if(fopen(filename,"r"))
            roundRobin(filename);
        else
        {
            puts("File Not Found!");
            puts("----------------------------------");
        }
        puts("Enter file name or Ctrl+Z to exit:");
        puts("----------------------------------");
    }
    return 0;
}
