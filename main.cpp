#include <iostream>
#include <list>
#include <climits>
#include <cmath>
using namespace std;
// Struct para compras
struct Compra {
    int id;
    int peso;
    bool selected;
};
// Struct para entregadores
struct Entregadores {
    int id;
    int *comprasParaEntrega;
    int *caminhoParaEntregas;
    int distanciaOrigem;
    int numeroDeCompras;
    int tempo;
};
// Struct para o algoritmo Dijkstra
struct no{
    int v;          // Vertice adjacente
    float p;        // Peso da aresta
};
// Verifica se todas as compras foram selecionadas
bool verificaCompras(Compra compras[], int &qtdCompra) {
    for (int i = 0; i < qtdCompra; i++)
        if (!compras[i].selected)
            return true;
    return false;
}
// Verifica o melhor caminho
void dijkstra(list<no>adj[], int nVertices, int start, int end, Entregadores &entregador, int &c)
{
    // Declaração de variáveis
    int u = 0;
    int v = 0;
    list<no>::iterator p;
    int destino = 0;
    float weight = 0;
    float dist = 0;
    bool intree[nVertices];
    float distance[nVertices];
    int parent[nVertices];
    // Inicializa os valores
    for(u = 0; u < nVertices; u++)
    {
        intree[u] = false;
        distance[u] = INT_MAX;
        parent[u] = -1;
    }
    distance[start] = 0;
    v = start;
    // Verifica o melhor caminho
    while(intree[v] == false)
    {
        intree[v] = true;
        for(p = adj[v].begin(); p != adj[v].end(); p++)
        {
            destino = p->v;
            weight = p->p;
            if(distance[destino] > distance[v] + weight)
            {
                distance[destino] = distance[v] + weight;
                parent[destino] = v;
            }
        }
        v = 0;
        dist = INT_MAX;
        for(u = 0; u < nVertices; u++)
        {
            if(intree[u] == false && dist > distance[u])
            {
                dist = distance[u];
                v = u;
            }
        }
    }
    // Variáveis auxiliares
    list<int> pilha;
    int cont = end;
    int pai = 0;
    pilha.push_front(end);
    pai = parent[end];
    for (int i = 0; i < nVertices; i++) {
        pilha.push_front(pai);
        pai = parent[pai];
        if (pai == -1) break;
    }
    // Manda o melhor caminho para o entregador
    for(list<int>::iterator p = pilha.begin(); p != pilha.end(); p++)
    {
        entregador.caminhoParaEntregas[c] = *p + 1;
        c++;
    }
    // Manda o tempo do melhor caminho para o entregador
    entregador.tempo += distance[end];
}
// Cria as arestas para serem usadas na função dijkstra
void cria_aresta(list<no>adj[], int u, int v, float p, int orientado)
{
    // Var aux para inserir arestas em adj
    no aux;
    aux.v = v;
    aux.p = p;
    adj[u].push_back(aux);
    if(orientado == 0)
    {
        aux.v = u;
        adj[v].push_back(aux);
    }
}
// Seleciona as compras para cada entregador
int selecionaComprasParaEntregadores (Compra compras[], int qtdCompras, Entregadores entregador, int capacidadeMax) {
    // Declaração de variáveis
    int pd[100][100];
    int caminhoComprasSelecionadas[100][100];
    // Inicializa os valores como 0
    for (int j = 0; j < capacidadeMax; j++)
        pd[qtdCompras][j] = 0;
    for (int i = 0; i < qtdCompras; i++)
        pd[i][0] = 0;
    // Seleciona por método guloso as compras
    for (int i = (qtdCompras - 1); i >= 0; i--) {
        for (int j = 1; j <= capacidadeMax; j++) {
            int pega, naoPega;
            naoPega = pd[i + 1][j];
            if ((j >= compras[i].peso) && !(compras[i].selected))
                pega = pd[i + 1][j - compras[i].peso] + compras[i].id;
            else
                pega = 0;
            if ((pega > naoPega) /*&& (buscaIDS(ignoreIndex, 0, (tamIgnoreIndex - 1), compras[i].id) != -1)*/) {
                pd[i][j] = pega;
                caminhoComprasSelecionadas[i][j] = 1;
            } else {
                pd[i][j] = naoPega;
                caminhoComprasSelecionadas[i][j] = 0;
            }
        }
    }
    // Variáveis auxiliares
    int i = 0;
    int j = capacidadeMax;
    int posCompraEntregador = 0;
    int nCompras = 0;
    // Manda as compras para o entregador
    while (i != qtdCompras) {
        if(caminhoComprasSelecionadas[i][j] == 0)
            i++;
        else {
            entregador.comprasParaEntrega[posCompraEntregador] = compras[i].id;
            nCompras++;
            posCompraEntregador++;
            compras[i].selected = true;
            j-= compras[i].peso;
            i++;
        }
    }
    return nCompras;
}
//Função que organiza a Struct pela distância até o supermercado
void quickSort(Entregadores vetor[], int i, int j)
{
    Entregadores trab, pivo;
    int esq = i;
    int dir = j;
    pivo.distanciaOrigem = vetor[(int)round((esq + dir) / 2.0)].distanciaOrigem;
    do
    {
        while (vetor[esq].distanciaOrigem < pivo.distanciaOrigem)
            esq++;
        while (vetor[dir].distanciaOrigem > pivo.distanciaOrigem)
            dir--;
        if (esq <= dir)
        {
            trab = vetor[esq];
            vetor[esq] = vetor[dir];
            vetor[dir] = trab;
            vetor[dir].id = trab.id;
            esq++;
            dir--;
        }
    }
    while (esq <= dir);
    if (dir - i >= 0)
        quickSort(vetor, i, dir);
    if (j - esq >= 0)
        quickSort(vetor, esq, j);
}
int main() {
    // ----- Declaração das variáveis -----
    bool more = true;                         // Se restou alguma compra sem ser entregue
    int nCompra = 0;                          // número de compras
    int nEntregadores = 0;                    // número de entregadores
    int cEntregador = 0;                      // capacidade de cada entregador
    int nCasas = 0;                           // números de casas
    int localSaida = 0;                       // local que será a saída do entregador
    int vOrigem = 0;                          // vertice de origem
    int vDestino = 0;                         // vertice de destino
    float pAresta = 0;                        // Peso da aresta
    Compra *compras = NULL;                // vetor para compra
    Entregadores *entregadores = NULL;     // vetor para entregador
    // ------ Leitura dos dados ------
    // Lê o número de compras
    cout << "Entre com o numero de compras: ";
    cin >> nCompra;
    compras = new Compra[nCompra];
    // Lê o número de entregadores
    cout << "\nEntre com o numero de entregadores: ";
    cin >> nEntregadores;
    entregadores = new Entregadores[nEntregadores];
    // Lê a capacidade dos entregadores
    cout << "\nEntre com a capacidade maxima dos entregadores:  ";
    cin >> cEntregador;
    // Lê o número de casas
    cout << "\nEntre com o numero de casas, incluindo o supermercado:  ";
    cin >> nCasas;
    list<no> adj[nCasas + 1];
    // Lê o ID da casa que o entregador sai
    cout << "\nEntre com o local de saída:  ";
    cin >> localSaida;
    // Lê o ID e Peso de cada compra
    for (int i = 0; i < nCompra; i++) {
        cout << "\nEntre com o ID da compra: ";
        cin >> compras[i].id;
        cout << "Entre com o peso da compra: ";
        cin >> compras[i].peso;
        compras[i].selected = false;
    }
    // Lê a distância de cada entregador ao supermercado
    for (int i = 0; i < nEntregadores; i++) {
        cout << "\nEntre com a distancia que o entregador " << (i + 1) << " esta da loja: ";
        cin >> entregadores[i].distanciaOrigem;
        // Cria os vetores para compras e caminhos de cada entregador
        entregadores[i].id = i + 1;
        entregadores[i].caminhoParaEntregas = new int[(2 * nCasas)];
        entregadores[i].comprasParaEntrega = new int[nCompra];
        entregadores[i].numeroDeCompras = 0;
        entregadores[i].tempo = 0;
        // Inicializa os vetores com 0
        for (int j = 0; j < nCompra; j++)
            entregadores[i].comprasParaEntrega[j] = 0;
        for (int j = 0; j < (2 * nCasas); j++)
            entregadores[i].caminhoParaEntregas[j] = 0;
    }
    // Lê o a casa de origem, a casa de destino e o peso da aresta - dijkstra
    cout << "\nEntre com o id da casa de origem, destino e peso: " << endl;
    cin >> vOrigem >> vDestino >> pAresta;
    while ((vOrigem != -1) && (vDestino != -1) && (pAresta != -1)) {
        //Cria uma aresta com os dados lidos
        cria_aresta(adj, (vOrigem - 1), (vDestino - 1), pAresta, 0);
        cin >> vOrigem >> vDestino >> pAresta;
    }
    // Faz a verificação e exibição do melhor caminho, tempo e compras de cada entregador
    do{
        //Organiza os entregadores pela distância do supermercado
        quickSort(entregadores, 0, (nEntregadores - 1));
        // Divide as compras entre os entregadores
        for (int i = 0; i < nEntregadores; i++) {
            entregadores[i].numeroDeCompras = selecionaComprasParaEntregadores(compras, nCompra, entregadores[i],cEntregador);
        }
        // Variáveis auxiliares
        int saida = localSaida;
        int cont = 0;
        // Verifica o tempo para ir ao supermercado e até a última entrega
        for (int i = 0; i < nEntregadores; i++) {
            if(entregadores[i].comprasParaEntrega[0] != 0)
                for (int j = 0; j < entregadores[i].numeroDeCompras; ++j) {
                    // Chama a função dijkstra com o ponto de partida e o destino
                    dijkstra(adj, nCasas, (saida - 1), entregadores[i].comprasParaEntrega[j] - 1, entregadores[i], cont);
                    saida = entregadores[i].comprasParaEntrega[j];
                }
            cont = 0;
            saida = localSaida;
        }
        //Variáveis auxiliares
        int z = 0;
        int aux = 0;
        // Exibe os dados
        for (int i = 0; i < nEntregadores; ++i) {
            if(entregadores[i].comprasParaEntrega[0] != 0) {
                // Exibe o tempo gasto
                cout << "Tempo que o entregador " << entregadores[i].id << " gastou: " << entregadores[i].tempo + entregadores[i].distanciaOrigem << endl;
                // Exibe o caminho percorrido
                cout << "Caminho que o entregador " << entregadores[i].id << " percorreu: ";
                for (z = 0; z < (2 * nCasas); z++) {
                    if (entregadores[i].caminhoParaEntregas[z] == 0)
                        break;
                    if(entregadores[i].caminhoParaEntregas[z] != entregadores[i].caminhoParaEntregas[z + 1]){
                        cout << entregadores[i].caminhoParaEntregas[z] << " ";
                        aux = entregadores[i].caminhoParaEntregas[z];
                    }
                    else {
                        cout << entregadores[i].caminhoParaEntregas[z + 1] << " ";
                        aux = entregadores[i].caminhoParaEntregas[z + 1];
                        z++;
                    }
                }
                // Exibe as compras que o entregador entregou
                cout << "\nCompras entregues pelo entregador " << entregadores[i].id << " : ";
                for (int j = 0; j < entregadores[i].numeroDeCompras; ++j) {
                    cout << entregadores[i].comprasParaEntrega[j] << " ";
                }
                // Seta o novo tempo de ir de volta para o supermercado baseado no último ponto de entrega
                for (list<no>::iterator p = adj[aux - 1].begin(); p != adj[aux - 1].end(); p++) {
                    if(p->v == (localSaida - 1)){
                        entregadores[i].distanciaOrigem = p->p;
                        break;
                    }
                }
                cout << "\n===========================================" << endl;
            }
        }
        // Verifica se restou alguma compra sem ser entregue
        more = verificaCompras(compras, nCompra);
        // Limpa as variáveis para a inserção das novas compras caso tenho sobrado alguma
        if(more)
            for (int i = 0; i < nEntregadores; ++i) {
                for (int j = 0; j < z; ++j) {
                    entregadores[i].caminhoParaEntregas[j] = 0;
                }
                for (int j = 0; j < entregadores[i].numeroDeCompras; ++j) {
                    entregadores[i].comprasParaEntrega[j] = 0;
                }
                entregadores[i].numeroDeCompras = 0;
                entregadores[i].tempo = 0;
            }
    }while(more);
    // Limpa a memória
    for (int i = 0; i < nEntregadores; i++) {
        delete [] entregadores[i].comprasParaEntrega;
        delete [] entregadores[i].caminhoParaEntregas;
    }
    delete[] compras;
    delete[] entregadores;
    return 0;
}