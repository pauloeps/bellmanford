#include <iostream>

using namespace std;

#define MAX_NOS 4 // NUMERO MAXIMO DE NOS
#define INF 9999 // REPRESENTACAO DE INFINITO

void imprimeVetor(int vetor[], int tam) {

    cout << "{";
    int i;
    for (i = 0; i < tam - 1; i++) {
        cout << vetor[i] << ", ";
    }
    cout << vetor[i] << "}" << endl;
}

// Estrutura que representa uma aresta
struct arco {
    int origem;
    int destino;
    int peso;
};

bool bellmanFord(int G[][MAX_NOS], int ordem, int s, int Custo[]) {
    
    // Aloca memoria dinamicamente para o vetor "A"
    arco* A = NULL;
    A = new arco[ordem * ordem];

    // Preenche o vetor de arcos com todos os arcos do grafo
    int n_Arcos = 0;
    for (int i = 0; i < ordem; i++) {
        for (int j = 0; j < ordem; j++) {
            if (G[i][j]) {
                A[n_Arcos].origem = i;
                A[n_Arcos].destino = j;
                A[n_Arcos].peso = G[i][j];
                n_Arcos++;
            }
        }
    }

    // Inicializa o vetor "Custo" com infinito
    for (int i = 0; i < ordem; i++) {
        Custo[i] = INF;
    }
    
    // O custo ate o no de origem eh zero
    Custo[s] = 0;

    bool trocou;

    // Preenche o vetor "Custo" com o custo para visitar cada vertice
    for (int i = 0; i < ordem; i++) {
        trocou = false;
        for (int j = 0; j < n_Arcos; j++) {
            if (Custo[A[j].destino] > Custo[A[j].origem] + A[j].peso) {
                Custo[A[j].destino] = Custo[A[j].origem] + A[j].peso;
                trocou = true;
            }
        }
        if (!trocou) break;
    }

    // Descobre se existe um ciclo com peso negativo, que a cada vez que
    // eh percorrido, diminui o custo do percurso. Caso exista a funcao
    // retorna "false".
    for (int i = 0; i < n_Arcos; i++) {
        if (Custo[A[i].destino] > Custo[A[i].origem] + A[i].peso)
            return false;
    }
    return true;
}

int main()
{
    int Custo1[MAX_NOS];
    int Custo2[MAX_NOS];
    bool grafo1;
    bool grafo2;

    int G[MAX_NOS][MAX_NOS]{
        {0, 100, 1, 0 },
        {100, 0, 0, 200},
        {1, 0, 0, 2},
        {0, 200, 2, 0},
    };

    int G2[MAX_NOS][MAX_NOS]{
        {0, 100, -1, 0 },
        {100, 0, 0, 200},
        {-1, 0, 0, 2},
        {0, 200, 2, 0},
    };

    grafo1 = bellmanFord(G, MAX_NOS, 0, Custo1);
    grafo2 = bellmanFord(G2, MAX_NOS, 0, Custo2);

    cout << "Vetor Custo do grafo 1: ";
    imprimeVetor(Custo1, MAX_NOS);

    if (!grafo1)
        cout << "Existe ciclo negativo no grafo 1" << endl;
    else
        cout << "Nao existe ciclo negativo no grafo 1" << endl;

    cout << "\n";

    cout << "Vetor Custo do grafo 2: ";
    imprimeVetor(Custo2, MAX_NOS);

    if (!grafo2)
        cout << "Existe ciclo negativo no grafo 2" << endl;
    else
        cout << "Nao existe ciclo negativo no grafo 2" << endl;

    return 0;
}
