#include <cstring>
#include <ctype.h>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <vector>

using namespace std;

typedef struct {
    string numeroCelular;
    string dadosSessao;
} Telefone;

string *split(string frase, string delimitador = " ")
{
    string *vetor = new string[3]; //alocando um vetor de string com 3 posições
    int inicio = 0;
    int fim = frase.find(delimitador);
    int i = 0;
    while (fim != -1) {
        vetor[i] = frase.substr(inicio, fim - inicio);
        inicio = fim + delimitador.size();
        fim = frase.find(delimitador, inicio);
        i++;
    }
    vetor[i] = frase.substr(inicio, fim - inicio);

    return vetor;
}

//método que carrega a base de telefonia e armazena numero de celular e dados de sessao no vector
vector<Telefone> carregarBase()
{
    vector<Telefone> lista;
    ifstream arquivo("telephony_sessions.txt");
    string linha;

    while (getline(arquivo, linha)) {
        string *partes = split(linha, ";");

        Telefone t;
        t.numeroCelular = partes[0];
        t.dadosSessao = partes[1];

        lista.push_back(t);
    }
    arquivo.close();

    return lista;
}

//metodo que lista somente os numeros de celular um abaixo do outro e no final mostra a quantidade de celulares exibidos
void listarTelefones(vector<Telefone> lista)
{
    for (int i = 0; i < lista.size(); i++) {
        cout << lista[i].numeroCelular << "\n";
    }
    cout << "Quantidade de celulares: " << lista.size() << "\n";
}

//metodo que o usuario digita um numero de celular, o sistema o localiza e se localizado, mostra seus dados de sessao
void pesquisarTelefone(vector<Telefone> lista)
{
    string numero;
    bool encontrado = false;

    cout << "Digite o numero do celular: ";
    cin >> numero;
    cin.ignore();

    for (int i = 0; i < lista.size(); i++) {
        if (lista[i].numeroCelular == numero) {
            cout << "Dados da sessao: " << lista[i].dadosSessao << "\n";
            encontrado = true;
        }
    }

    if (encontrado == false) {
        cout << "Telefone nao encontrado!\n";
    }
}

int main() {
    vector<Telefone> listaSessoes;
    string opcao;

    listaSessoes = carregarBase();

    do {
        cout << "MENU\n";
        cout << "1 - Listar telefones\n";
        cout << "2 - Pesquisar telefone e dados de sessao\n";
        cout << "3 - Finalizar\n";
        cout << "Opcao: ";
        cin >> opcao;
        cin.ignore();

        if (opcao == "1") {
            listarTelefones(listaSessoes);
        } else if (opcao == "2") {
            pesquisarTelefone(listaSessoes);
        } else if (opcao == "3") {
            cout << "Obrigado por usar o sistema\n";
        } else {
            cout << "Opcao invalida!\n";
        }
    } while (opcao != "3");

    return 0;
}
