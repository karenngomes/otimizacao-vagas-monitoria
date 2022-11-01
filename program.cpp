// #include <map>
// #include <iostream>
// #include <vector>
#include <bits/stdc++.h>

using namespace std;

struct Criterio {
    string nome;
    int peso;
    int valor; // ver se realmente precisa
};

struct Disciplina {
    string cod;
    int score = 0;
    // Criterio* criterios_disciplina;
    int maiorPesoCriterio = 0;
    map<string, double> valores;
};

int taxaDeDesistencia(struct Disciplina d, int pesoCriterio, int valorCriterio) {
    // codigo pra avaliar o criterio e somar no score da disciplina
    printf("taxaDeDesistencia\n");
    return 1;
}

int numeroDeAlunos(struct Disciplina d, int pesoCriterio, int valorCriterio) {
    // codigo pra avaliar o criterio e somar no score da disciplina
    printf("numeroDeAlunos\n");
    return 1;
}

map<string, int (*)(struct Disciplina, int, int)> hashExecCriterio;
map<string, vector<double>> valoresNoramlizados;


// void pontuarDisciplinas(vector<Disciplina> d, vector<Criterio> c) {
//     // preciso normalizar antes
//     for (int i = 0; i < d.size(); ++i) {
//         d[i].score = 0;
//         for (int j = 0; j < c.size(); ++j) {
//             d[i].score += hashExecCriterio[c[j].nome](d[i], c[j].peso, c[j].valor);
//         }
//     }
//     for (int i = 0; i < d.size(); i++) {
//         printf("Olhe %d\n", d[i].score);
//     }
    
// }

bool ordena(Interval i1, Interval i2)
{
    return (i1.start < i2.start);
}

void normalizar(Criterio c, vector<Disciplina> d) {
    sort(d.begin(), d.end());
    // int max_value = d[i].valores[c.nome][d[i].valores[c.nome]];
        // int max_value = d[i].valores[c.nome][d[i].valores[c.nome]];
}

void pontuarDisciplinas(vector<Disciplina> d, vector<Criterio> c) {
    for (int i = 0; i < c.size(); ++i) {
        
    }
    
}

int main() {
    hashExecCriterio["numeroDeAlunos"] = numeroDeAlunos;
    hashExecCriterio["taxaDeDesistencia"] = taxaDeDesistencia;
    // criar as disciplinas e criterios
    // ...

    // pontuarDisciplinas(disciplinas, criterios)

    // ordenar as disciplinas pelo score delas *sobrescrever a funcao de comparacao do algoritmo de ordenacao (levar em conta o caso das desistencias da disciplina)
    
    cout << "Hello, World!" << endl;

    vector<Disciplina> disciplinas;
    Disciplina d1, d2;
    d1.cod = "d1";
    d2.cod = "d2";
    disciplinas.push_back(d1);
    disciplinas.push_back(d2);

    // cout << "Digite o número de critérios: ";
    // cin >> numCriterios;

    // Criterio* criterios = new Criterio[numCriterios]; // ver vector de criteiro
    vector<Criterio> criterios;
    Criterio c1, c2;
    c1.nome = "numeroDeAlunos";
    c2.nome = "taxaDeDesistencia";
    criterios.push_back(c1);
    criterios.push_back(c2);

    // cout << "Quantidade de critérios: " << criterios[0].nome << endl ;

    pontuarDisciplinas(disciplinas, criterios);

    cout << "Fim do programa" << endl;    


    return 0;
}