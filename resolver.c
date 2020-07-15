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

int N;
int* ADJ;
int  COLUMNAS;

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



int* bfs(int ini, int fin){

    int actual, next;
    int cont = 0;
    int* visitados= (int*)calloc(N,sizeof(int));
    int camino[N];

    push(ini);
    visitados[ini] = 1;



    while (actual != fin){

        actual = pull();
        camino[cont]= actual;
        cont++;
        //printf("Tudo bem %d  \n ", actual);

        if (NORTE(ADJ[actual]) && visitados[actual-COLUMNAS] != 1) {
            push(actual-COLUMNAS);
            visitados[actual-COLUMNAS] = 1;

        }

        if (OESTE(ADJ[actual]) && visitados[actual-1] != 1){
            push(actual-1);
            visitados[actual-1];


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
    for (int j = 0; j < cont; ++j) {
        printf("%d \n",camino[j]);
    }
    return camino;
}



int elementoXY(int x, int y){
    int resultado;

    if (x == 0) return y;

    else{

        resultado = ((COLUMNAS ) * x) +y;
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
            N++;
        }



    }

    int* camino = bfs(0,2);



    fclose(archivo);
    return 0;
}

