#include <iostream>
#include <climits>

using namespace std;

// Struct para compras
struct Compra {
    int id;
    int peso;

};

// Struct para entregadores
struct Entregadores {
    int *comprasParaEntrega;
    int *caminhoParaEntregas;
    int distanciaDaLoja;
    
};

// Inicia a matrix colocando todos os valores como -2 por padrão
void initMatrix(int mat[100][100]) {
    for (int i = 0; i < 100; i++)
        for (int j = 0; j < 100; j++) {
            if (j == i)
                mat[i][j] = 0;
            else
                mat[i][j] = -1;

        }

}

// busca binária
int buscaIDS (int compras[], int ini, int tam, int &id) {
    int meio = (ini + tam) / 2;
    if (ini <= tam) {
        if (compras[meio] == id)
            return meio;
        else if (compras[meio] > id)
            return buscaIDS(compras, (meio + 1), tam, id);
        else
            return buscaIDS(compras, ini, (tam - 1), id);

    }

    return -1;

}

// seleciona as compras para cada entregador
int manageComprasToEntregadores (Compra compras[],
                                  int qtdCompras,
                                  Entregadores entregador,
                                  int capacidadeMax,
                                  int ignoreIndex[],
                                  int &tamIgnoreIndex) {
    int pd[100][100];
    int caminhoComprasSelecionadas[100][100];

    for (int j = 0; j < capacidadeMax; j++)
        pd[qtdCompras][j] = 0;

    for (int i = 0; i < qtdCompras; i++)
        pd[i][0] = 0;

    for (int i = (qtdCompras - 1); i >= 0; i--) {
        for (int j = 1; j <= capacidadeMax; j++) {
            int pega, naoPega;

            naoPega = pd[i + 1][j];

            if (j >= compras[i].peso)
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

    int i = 0, j = capacidadeMax;
    int posCompraEntregador = 0;
    int posIgnore = tamIgnoreIndex;

    while (i != qtdCompras) {
        if(caminhoComprasSelecionadas[i][j] == 0)
            i++;
        else {
            entregador.comprasParaEntrega[posCompraEntregador] = compras[i].id;
            ignoreIndex[posIgnore] = compras[i].id;
            posIgnore++;
            posCompraEntregador++;
            j-= compras[i].peso;
            i++;

        }
    }

    tamIgnoreIndex = posIgnore + 1;

    return posCompraEntregador;

}

int main() {
    int nCompra = 0; // número de compras
    int nEntregadores = 0; // número de entregadores
    int nCasas = 0; // números de casas
    int localSaida = 0; // local que será o supermercado e saída do entregador

    int casas[100][100]; // matrix para armazenar o tempo do caminho para cada cidade/casa

    int capacidadeEntregador = 0; // capacidade de cada entregador
    
    Compra compras[100]; // vetor para compra
    Entregadores entregadores[100]; // vetor para entregador

    // Pega as variaveis de tamanho dos vetores e capacidade dos entregadores
    cout << "Entre com o numero de compras: ";
    cin >> nCompra;
    cout << "\nEntre com o numero de entregadores: ";
    cin >> nEntregadores;
    cout << "\nEntre com a capacidade maxima dos entregadores:  ";
    cin >> capacidadeEntregador;
//    cout << "\nEntre com o numero de casas, incluindo o supermercado:  ";
//    cin >> nCasas;
//    cout << "\nEntre com o numero do supermercado:  ";
//    cin >> localSaida;

    // Pega o ID e Peso de cada compra
    for (int i = 0; i < (nCompra - 1); i++) {
        cout << endl;
        cout << "Entre com o numero da compra: ";
        cin >> compras[i].id;
        cout << "Entre com o peso da compra: ";
        cin >> compras[i].peso;

    }

    // Pega a distância de cada entregador ao supermercado
    for (int i = 0; i < nEntregadores; i++) {
        cout << "\nEntre com a distancia do entregador " << (i + 1) << " esta da loja: ";
        cin >> entregadores[i].distanciaDaLoja;

        // Cria os vetores para compras e caminhos de cada entregador
        entregadores[i].caminhoParaEntregas = new int[10];
        entregadores[i].comprasParaEntrega = new int[10];

    }

    // Inicia Matrix de casas
//    initMatrix(casas);
    // Preenche a matrix de casas
//    for (int i = 1; i <= nCasas; i++) {
//        for (int j = 1; j <= nCasas; j++) {
//            if (i == j) {
//                casas[i][j] = 0;
//            } else {
//                cout << "Custo cidade " << i << " para " << j << endl;
//                cin >> casas[i][j];
//                casas[j][i] = casas[i][j];
//            }
//        }
//    }

    // Variáveis auxiliares para separação das compras
    int idsSelecionados[100];
    int tamIgnore = 0;

    // Divide as compras entre os entregadores
    for (int i = 0; i < nEntregadores; i++) {
        manageComprasToEntregadores(compras, nCompra, entregadores[i], capacidadeEntregador, idsSelecionados, tamIgnore);

    }

    // Mostra as compras de cada entregador ( SOMENTE TESTE )
    int c = 0;
    for (int i = 0; i < nEntregadores; i++) {
        do {
            cout << "\nCompra Entregador " << (i + 1) << " " << entregadores[i].comprasParaEntrega[c] << " ";
            ++c;
        } while (c < 10);
        c = 0;

    }

    // Delete os vetores de cada entregador
    for (int i = 0; i < nEntregadores; i++) {
        delete [] entregadores[i].comprasParaEntrega;
        delete [] entregadores[i].caminhoParaEntregas;

    }

    return 0;

}
