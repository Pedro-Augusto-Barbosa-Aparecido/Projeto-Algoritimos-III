#include <iostream>

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

int main() {
    int nCompra = 0;
    int nEntregadores = 0;
    int nCasas = 0;
    int localSaida = 0;

    int casas[100][100];
    
    Compra compras[100];
    Entregadores entregadores[100];

    cout << "Entre com o numero de compras: ";
    cin >> nCompra;
    cout << "\nEntre com o numero de entregadores: ";
    cin >> nEntregadores;
    cout << "Entre com o numero de casas, incluindo o supermercado:  ";
    cin >> nCasas;
    cout << "\nEntre com o numero do supermercado:  ";
    cin >> localSaida;

    initMatrix(casas);

    for (int i = 0; i < nCompra; i++) {
        cout << endl;
        cout << "Entre com o numero da compra: ";
        cin >> compras[i].id;
        cout << "Entre com o peso da compra: ";
        cin >> compras[i].peso;

    }

    for (int i = 0; i < nEntregadores; ++i) {
        cout << "\nEntre com a distancia do entregador " << (i + 1) << " esta da loja: ";
        cin >> entregadores[i].distanciaDaLoja;

        entregadores[i].caminhoParaEntregas = new int[100];
        entregadores[i].comprasParaEntrega = new int[100];

    }

    return 0;

}
