#include <iostream>
#include <climits>

using namespace std;

struct Compra {
    int id;
    int peso;

};

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

void updateComprasLista (Compra compras[], int &qtdCompras, int idsJaUtilizados[], int &qtdIds, Compra compraListaParaUpdate[]) {
    int j = 0;
    for (int i = 0; i < qtdCompras; i++) {
        int compra = buscaIDS(idsJaUtilizados, 0, qtdIds, compras[i].id);

        if (compra == -1) {
            compraListaParaUpdate[j] = compras[i];
            ++j;

        }

    }

}

// seleciona as compras para cada entregador
int manageComprasToEntregadores (Compra compras[],
                                  int &qtdCompras,
                                  Entregadores entregador,
                                  int &capacidadeMax) {
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

            if (pega > naoPega) {
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

    while (i != qtdCompras) {
        if(caminhoComprasSelecionadas[i][j] == 0)
            i++;
        else {
            entregador.comprasParaEntrega[posCompraEntregador] = compras[i].id;
            posCompraEntregador++;
            j-= compras[i].peso;
            i++;

        }
    }

    return posCompraEntregador;

}

int main() {
    int nCompra = 0;
    int nEntregadores = 0;
    int nCasas = 0;
    int localSaida = 0;

    int casas[100][100];

    int capacidadeEntregador = 0;
    
    Compra compras[100];
    Compra comprasAux[100];
    Entregadores entregadores[100];

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

    for (int i = 0; i < (nCompra - 1); i++) {
        cout << endl;
        cout << "Entre com o numero da compra: ";
        cin >> compras[i].id;
        cout << "Entre com o peso da compra: ";
        cin >> compras[i].peso;

    }

    for (int i = 0; i < nEntregadores; i++) {
        cout << "\nEntre com a distancia do entregador " << (i + 1) << " esta da loja: ";
        cin >> entregadores[i].distanciaDaLoja;

        entregadores[i].caminhoParaEntregas = new int[10];
        entregadores[i].comprasParaEntrega = new int[10];

    }

//    initMatrix(casas);
//
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

    int qtdCompra = nCompra;
    int idsSelecionados[100];
    int ini = 0;
    for (int i = 0; i < nCompra; i++)
        comprasAux[i] = compras[i];

    for (int i = 0; i < nEntregadores; i++) {
        int qtdCompraSelecionada = manageComprasToEntregadores(comprasAux, qtdCompra, entregadores[i], capacidadeEntregador);
        for (int j = ini; j < (qtdCompraSelecionada + ini); j++) {
            idsSelecionados[j] = entregadores[i].comprasParaEntrega[j];

        }

        ini += qtdCompraSelecionada;
        qtdCompra = (nCompra - qtdCompraSelecionada);

        updateComprasLista(compras, nCompra, idsSelecionados, ini, comprasAux);

    }

    int c = 0;
    for (int i = 0; i < nEntregadores; i++) {
        do {
            cout << "\nCompra Entregador " << (i + 1) << " " << entregadores[i].comprasParaEntrega[c] << " ";
            ++c;
        } while (c < 10);
        c = 0;

    }

    for (int i = 0; i < nEntregadores; i++) {
        delete [] entregadores[i].comprasParaEntrega;
        delete [] entregadores[i].caminhoParaEntregas;

    }

    return 0;

}
