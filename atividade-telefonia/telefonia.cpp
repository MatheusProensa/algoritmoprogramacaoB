#include <cstring>
#include <ctype.h>
#include <fstream>  // pra abrir arquivo
#include <iostream> // cout e cin
#include <stdlib.h>
#include <string>   // texto
#include <time.h>
#include <vector>   // vector

using namespace std;

typedef struct {          // ficha do telefone
    string numeroCelular; // numero
    string dadosSessao;   // dados da sessao
} Telefone;

string *split(string frase, string delimitador = " ") // metodo que separa a string
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
    vector<Telefone> lista;                     // vector vazio
    ifstream arquivo("telephony_sessions.txt"); // abre o arquivo
    string linha;

    while (getline(arquivo, linha)) {           // le linha por linha
        string *partes = split(linha, ";");     // separa no ;

        Telefone t;                             // ficha nova
        t.numeroCelular = partes[0];            // antes do ; = numero
        t.dadosSessao = partes[1];              // depois do ; = dados

        lista.push_back(t);                     // bota no vector
    }
    arquivo.close();                            // fecha o arquivo

    return lista;                               // devolve o vector cheio
}

//metodo que lista somente os numeros de celular um abaixo do outro e no final mostra a quantidade de celulares exibidos
void listarTelefones(vector<Telefone> lista)
{
    for (int i = 0; i < lista.size(); i++) {    // passa por todos
        cout << lista[i].numeroCelular << "\n"; // mostra so o numero
    }
    cout << "Quantidade de celulares: " << lista.size() << "\n"; // total
}

//metodo que o usuario digita um numero de celular, o sistema o localiza e se localizado, mostra seus dados de sessao
void pesquisarTelefone(vector<Telefone> lista)
{
    string numero;
    bool encontrado = false;                    // ainda nao achou

    cout << "Digite o numero do celular: ";
    cin >> numero;                              // le o numero digitado
    cin.ignore();

    for (int i = 0; i < lista.size(); i++) {    // passa por todos
        if (lista[i].numeroCelular == numero) { // é igual ao digitado?
            cout << "Dados da sessao: " << lista[i].dadosSessao << "\n";
            encontrado = true;                  // achou
        }
    }

    if (encontrado == false) {                  // nao achou nenhum
        cout << "Telefone nao encontrado!\n";
    }
}

int main() {
    vector<Telefone> listaSessoes;              // vector principal
    string opcao;

    listaSessoes = carregarBase();              // carrega antes do menu

    do {                                        // repete o menu
        cout << "MENU\n";
        cout << "1 - Listar telefones\n";
        cout << "2 - Pesquisar telefone e dados de sessao\n";
        cout << "3 - Finalizar\n";
        cout << "Opcao: ";
        cin >> opcao;                           // le a opcao
        cin.ignore();

        if (opcao == "1") {                     // if pq switch nao aceita string
            listarTelefones(listaSessoes);
        } else if (opcao == "2") {
            pesquisarTelefone(listaSessoes);
        } else if (opcao == "3") {
            cout << "Obrigado por usar o sistema\n";
        } else {
            cout << "Opcao invalida!\n";
        }
    } while (opcao != "3");                     // ate escolher 3

    return 0;
}


// Matheus Proensa - Algoritmos e Programacao B - UFN