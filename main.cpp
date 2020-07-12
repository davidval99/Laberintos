

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
const int MAXN=100000;

vector<ii> G[MAXN];
bool taken[MAXN];

priority_queue<ii, vector<ii>, greater<ii> > pq;//min heap

void process(int v){
    taken[v]=true;
    forall(e, G[v])
        if(!taken[e->second]) pq.push(*e);
}

ll prim(){
    vector<ii> edges;
    zero(taken);
    process(0);
    ll cost=0;
    while(sz(pq)){
        ii e=pq.top(); pq.pop();
        if(!taken[e.second]) cost+=e.first, process(e.second);
        edges.push_back(make_pair(e.first,e.second)); // revisar si funciona

    }
    std::cout << cost; //return edges;
    return cost;
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
    vector<ii> edges;
    ll cost=0;
    sort(E.begin(), E.end());//ordenar aristas de menor a mayor
    uf.init(n);
    forall(it,E){
        std::cout << it->a << ", " << it->b << ", " << ", " << it->w << "\n";
    }

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

    //std::cout << cost;
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

    /*
    void primMST(vector<pair<int, int> > adj[], int V) {

        priority_queue<ii, vector<ii>, greater<ii> > pq;
        int src = 0;
        vector<int> key(V, INF);
        vector<int> parent(V, -1);
        vector<bool> inMST(V, false);
        pq.push(make_pair(0, src));
        key[src] = 0;

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();
            inMST[u] = true; // Include vertex in MST

            for (auto x : adj[u]) {

                int v = x.first;
                int weight = x.second;

                if (inMST[v] == false && key[v] > weight) {

                    key[v] = weight;
                    pq.push(make_pair(key[v], v));
                    parent[v] = u;
                }
            }
        }

        for (int i = 1; i < V; ++i)
            printf("%d - %d\n", parent[i], i);
    }*/

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

    void crearTxt(vector<ii> edges){

        int mascara;

        for(int i= 0; i<= FILAS*COLUMNAS;i++){
            for(int j=0; i <=edges.size();i++){
                if(edges[j].first = i){
                    mascara = mascara | verVecinos(edges[j].first, edges[j].second);
                }

            }
            std::cout <<"mask: " << mascara;

        }

    }


    //int arg, char **args
    int main() {




/*
        ofstream myfile;
        myfile.open("test.txt");
        myfile << "This is a test\n";
        myfile.close();*/



        COLUMNAS = 3;
        FILAS = 3;
        //int respuesta = verVecinos(8,7);
        //std:cout << respuesta;

        makeGraph(3, 3);

        //n=sizeof(G);
        normalizarKruskal();
        //prim();
        crearTxt(kruskal());

    }