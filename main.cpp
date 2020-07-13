

// C++ program to represent undirected and weighted graph
// using STL. The program basically prints adjacency list
// representation of graph
#include <bits/stdc++.h>
#include <iostream>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>

#include <queue>
#include <vector>
#include <string>
# define INF 0x3f3f3f3f
using namespace std;
#define dprint(v) cerr << #v"=" << v << endl //;)
#define forr(i,a,b) for(int i=(a); i<(b); i++)
#define forn(i,n) forr(i,0,n)
#define dforsn(i,a,b) for(int i=(b)-1; i>=a; i--)
#define forall(it,v) for(typeof(v.begin()) it=v.begin();it!=v.end();++it)

#define forall(it, v) for(typeof(v.begin()) it=v.begin();it!=v.end();++it)
#define sz(c) ((int)c.size())
#define zero(v) memset(v, 0, sizeof(v))

int FILAS;
int COLUMNAS;

typedef long long ll;
typedef pair<int,int> ii;
typedef pair<int,pair<int,int>> ip;
const int MAXN=100000;

vector<ii> G[MAXN];
bool taken[MAXN];
priority_queue<ip, vector<ip>, greater<ip> > pq;//min heap

void process(int v){
    taken[v]=true;
    forall(it, G[v])
        if(!taken[it->second]) pq.push(make_pair(it->first,make_pair(v,it->second)));
}

vector<ii> prim(){
    vector<ii> edges;
    zero(taken);
    process(0);
    ll cost=0;
    while(sz(pq)){
        ip e=pq.top(); pq.pop();

        if(!taken[e.second.second]){
            cost+=e.first, process(e.second.second);
            edges.push_back(make_pair(e.second.first,e.second.second));
        }

    }
    /*
    forall(it, edges){
        std::cout << it->first << "," << it->second <<"\n";
    }*/

    return edges;
}

struct UnionFind{
    vector<int> f;//the array contains the parent of each node
    void init(int n){f.clear(); f.insert(f.begin(), n, -1);}
    int comp(int x){
        return (f[x]==-1?x:f[x]=comp(f[x]));
    }//O(1)
    bool join(int i, int j) {
        bool con=comp(i)==comp(j);
        if(!con){
            f[comp(i)] = comp(j);}
        return con;
    }}uf;
int n;


struct Ar{int a,b,w;};
bool operator<(const Ar& a, const Ar &b){return a.w<b.w;}
vector<Ar> E;

void normalizarKruskal(){

    for(int i=0;i<FILAS*COLUMNAS;i++){
        for(int j=0; j<G[i].size();j++){
            Ar a;
            a.a = i;
            a.b = G[i][j].second;
            a.w = G[i][j].first;
            E.push_back(a);
        }
    }
}

int cmp(Ar a1, Ar a2){
    return a1.w < a2.w;
}

vector<ii> kruskal(){
    normalizarKruskal();
    vector<ii> edges;
    ll cost=0;
    sort(E.begin(), E.end());//ordenar aristas de menor a mayor
    uf.init(n);

    forall(it, E){
        if(uf.comp(it->a)!=uf.comp(it->b)){//si no estan conectados

            uf.join(it->a, it->b);//conectar
            cost=cost+it->w;
            edges.push_back(make_pair(it->a,it->b));
        }


    }

    forall(it, edges){
        std::cout << it->first << "," << it->second <<"\n";
    }

    return edges;
}

void addEdge(vector<pair<int, int> > adj[], int nodoIni, int nodoDest, int wt) {


    adj[nodoIni].push_back(make_pair(wt, nodoDest));
    adj[nodoDest].push_back(make_pair(wt, nodoIni));
}

void printGraph(vector<pair<int, int> > adj[], int V) {
    int v, w;
    for (int u = 0; u < V; u++) {
        cout << "Node " << u << " makes an edge with \n";
        for (auto it = adj[u].begin(); it != adj[u].end(); it++) {
            v = it->second;
            w = it->first;
            cout << "\tNode " << v << " with edge weight ="
            << w << "\n";
        }
        cout << "\n";
    }
}

void makeGraph(int filas, int columnas) {

        n = (filas * columnas);

        srand(time(NULL));

        for (int x = 0; x < n; x++) {

            if (x % columnas != x) {
                if (x < (x - columnas))
                    addEdge(G, x, x - columnas, 1+ rand() % 100);

            }

            if (x + columnas <= n - 1) {
                if (x < (x + columnas))
                    addEdge(G, x, x + columnas, 1+ rand() % 100);

            }

            if (x % columnas != columnas - 1) {
                if (x < (x + 1))
                    addEdge(G, x, x + 1, 1 +rand() % 100);
            }

            if (x % columnas != 0) {
                if (x < (x - columnas))
                    addEdge(G, x, x - 1, 1 +rand() % 100);
            }

        }


        //printGraph(G, n);

    };

int verVecinos(int nodoActual,int nodoDestino){

    if(nodoActual%COLUMNAS == nodoDestino || nodoDestino+COLUMNAS==nodoActual){
        return 2;
    }
    else if(nodoActual-1 == nodoDestino || nodoDestino+1 ==nodoActual){

        return 1;
    }


    else
        return 0;}

vector<int> setMascara(vector<ii> edges){

    vector<int> maskTxt;

    int mascara = 0;
    //Nodos
    for(int i= 0; i< FILAS*COLUMNAS;i++){
        //Aristas
        for(int j=0; j < edges.size();j++){
            if(edges[j].first == i){
                mascara = mascara | verVecinos(edges[j].first, edges[j].second);
            }
            else if(edges[j].second == i)  mascara = mascara | verVecinos(edges[j].second, edges[j].first);

        }
        maskTxt.push_back(mascara);
        mascara = 0;

    }
    return maskTxt;

}


void generarTxt(vector<int> mascara) {
    ofstream myfile;
    myfile.open("test.txt");
    int contador = 0;

    for (int i = 0; i < mascara.size(); i++) {
        myfile << mascara[i];
        contador++;
        if (contador % COLUMNAS == 0){ //Puede ser mas eficiente.
            myfile << "\n";
        }
    }
    myfile.close();

}


    //int arg, char **args
    int main() {


        COLUMNAS = 4; //Esto se debe setear por parametros
        FILAS = 4;
        makeGraph(FILAS, COLUMNAS);


        char algoritmo = 'p'; //Por parametro se decide cual algoritmo se utilizará

        if(algoritmo == 'k'){
            generarTxt(setMascara(kruskal()));
            std::cout << "Hice kruskal";
        }
        else if(algoritmo == 'p'){
            generarTxt(setMascara(prim()));
            std::cout << "Hice prim";
        }



    }