#include<stdio.h>
#include<stdlib.h>
#include <string.h>

#define NORTE(a) ((a) & (1<<1))
#define OESTE(a) ((a) & (1<<0))

typedef struct Nodo{
    int valor;
    struct Nodo* siguiente;
};

struct Nodo* cabeza = NULL;
struct Nodo* cola = NULL;
struct Nodo* pila = NULL;

int N;
int* ADJ;
int  COLUMNAS;

void pushP(int valor){

    struct Nodo* nuevo = malloc(sizeof(struct Nodo));
    nuevo->valor = valor;

    if (pila == NULL) {
        pila = nuevo;
        nuevo->siguiente = NULL;
    }
    else{
        nuevo->siguiente = pila;
        pila = nuevo;
    }
}

int pullP(){
    if (pila == NULL) return -1;
    else{
        int valor = pila->valor;
        struct Nodo* tmp = pila;
        pila = pila->siguiente;
        free(tmp);
        return valor;
    }
}

void push(int valor){
    struct Nodo* nuevo =  malloc(sizeof(struct Nodo));
    nuevo -> valor = valor;
    nuevo -> siguiente = NULL;

    if (cabeza == NULL){
        cabeza = nuevo;
        cola = nuevo;
    }
    else{
        cola -> siguiente = nuevo;
        cola = nuevo;
    }
};

int pull(){
    if (cabeza == NULL) return -1;

    else{
        struct Nodo * tmp = cabeza;
        int valor = tmp -> valor;
        cabeza = cabeza -> siguiente;
        free(tmp);
        return valor;
    }
};


int * caminodfs(){

    int* resultado = (int *)calloc(N,sizeof(int));
    int tmp = pullP();
    for (int i=N;tmp != -1;i--){
        printf("%d \n",tmp);
        resultado[i] = tmp;
        tmp = pullP();

    }
    return resultado;
}
int  dfsAux(int ini, int fin,int* visitados){


    visitados[ini] = 1;
    pushP(ini);
    if (ini == fin){
        return 0;
    }
    if (NORTE(ADJ[ini]) && visitados[ini-COLUMNAS] != 1) return dfsAux(ini-COLUMNAS,fin,visitados);
    if (OESTE(ADJ[ini]) && visitados[ini-1] != 1) return dfsAux(ini-1,fin,visitados);
    if (ini%COLUMNAS != COLUMNAS-1 && OESTE(ADJ[ini+1]) && visitados[ini+1] !=1 ) return dfsAux(ini+1,fin,visitados);
    if (ini+COLUMNAS < N && NORTE(ADJ[ini+COLUMNAS]) && visitados[ini+COLUMNAS] != 1) return dfsAux(ini+COLUMNAS,fin,visitados);
    else{
        int n=pullP();
        n=pullP();
        return dfsAux(n,fin,visitados);
    }
}
int* dfs (int ini, int fin){
    int* visitados = (int*)calloc(N,sizeof(int));
    int x = dfsAux(ini,fin,visitados);
    int* camino = caminodfs();
    free(visitados);
    return camino;
}
int* bfs(int ini, int fin){

    int actual= -1;
    int next;
    int cont = 0;
    int* visitados= (int*)calloc(N+1,sizeof(int));
    int camino[N+1];

    push(ini);
    visitados[ini] = 1;



    while (actual != fin){

        actual = pull();
        camino[cont]= actual;
        cont++;


        if (NORTE(ADJ[actual])  && visitados[actual-COLUMNAS] != 1) {
            push(actual-COLUMNAS);
            visitados[actual-COLUMNAS] = 1;


        }

        if (OESTE(ADJ[actual]) && visitados[actual-1] != 1){
            push(actual-1);
            visitados[actual-1]=1;



        }
        if (actual%COLUMNAS != COLUMNAS-1 && OESTE(ADJ[actual+1]) && visitados[actual+1] !=1 ) {
            push(actual+1);
            visitados[actual+1] =1;
        }
        //printf("Es %d + %d < %d   \n",actual,COLUMNAS,N);
        if (actual+COLUMNAS < N && NORTE(ADJ[actual+COLUMNAS]) && visitados[actual+COLUMNAS] != 1) {
            push(actual+COLUMNAS);
            visitados[actual+COLUMNAS]=1;

        }

    }
    camino[cont] = fin;

    return camino;
}



int elementoXY(int x, int y){
    int resultado;

    if (x == 0) return y;

    else{

        resultado = ((COLUMNAS) * (x)) +y;
        return resultado;
    }
}

// Grafo = [[1,2],[4,5],[6,7]]
int main()
{
    FILE *archivo;
    COLUMNAS = 0;

    N = 0;
    char caracteres[100];
    int valor;


    archivo = fopen("hh.txt","r");
    fgets(caracteres,100,archivo);
    while (caracteres[COLUMNAS]!= '\n'){
        COLUMNAS++;
    }
    int colum = COLUMNAS;
    fseek(archivo,0,SEEK_END);
    int tamanno = ftell(archivo);
    fseek(archivo,0,SEEK_SET);
    ADJ= (int*) calloc(tamanno,sizeof(int *));



    while (feof(archivo) == 0)
    {
        fgets(caracteres,100,archivo);

        for (int i = 0; caracteres[i] != '\n' && caracteres[i] != '\0'; i++){

            valor = (int)caracteres[i]-48;
            ADJ[N] = valor;
            //printf("%d valor \n",valor);
            N++;

        }



    }
    //LLAMADAS
    //int* camino = bfs(4,0);
    //int o = elementoXY(2,1); // Este muestra que posicion de ADJ estan en un (x,y)
    //int * camino = dfs(11,0);



    fclose(archivo);
    return 0;
}



