#include <bits/stdc++.h>

using namespace std;

struct Criterio
{
    string nome;
    int peso;
    int valor; // ver se realmente precisa (melhor menor valor?)
};

struct Disciplina
{
    string cod;
    double score = 0;
    int maiorPesoCriterio = 0; // ver se realmente precisa
    /*  map<string, double, bool, bool> valores: nome, valor, isBoolean, isCriterioPositivo */
    map<string, double> valores;             // se for booleano, será 0 ou 1
    map<string, double> valoresNormalizados; // se for booleano, será 0 ou 1
};

map<string, vector<double>> valoresNormalizadosTotais;

bool ordena(Disciplina d1, Disciplina d2, string nomeCriterio)
{
    return (d1.valores[nomeCriterio] < d2.valores[nomeCriterio]);
}

vector<Disciplina> normalizar(Criterio c, vector<Disciplina> d)
{
    string nomeCriterio = c.nome; 
    cout << "Tratando o criterio: " << nomeCriterio << endl;
    sort(d.begin(), d.end(), [&](Disciplina &d1, Disciplina &d2)
         { return (d1.valores[nomeCriterio] > d2.valores[nomeCriterio]); });
    /* só faz o sort se não for um booleano */
    // pegar maior valor daquela disciplina daquele criterio
    double max_value = d[0].valores[nomeCriterio];
    cout << "Maior valor(?): [" << max_value << "] " << endl;
    for (int i = 0; i < d.size(); i++)
    {
        // pega o map valoresNormalizados: valores[nomeCriterio] / max_value
        d[i].valoresNormalizados[nomeCriterio] = d[i].valores[nomeCriterio] / max_value;
    }

    for (auto x : d)
    {
        cout << "Valor: [" << x.valores[nomeCriterio] << "] ";
        cout << "Normalizado: [" << x.valoresNormalizados[nomeCriterio] << "] " << endl;
    }
    return d;
}

vector<Disciplina> pontuarDisciplinas(vector<Disciplina> d, vector<Criterio> c)
{
    for (int i = 0; i < c.size(); i++)
    {
        d = normalizar(c[i], d);
        for (int j = 0; j < d.size(); j++)
        {
            /* code */
            //*** calcula o score:
            cout << "score antes " << d[j].score << " valor normalizado " << d[j].valoresNormalizados[c[i].nome] << endl;
            d[j].score += c[i].peso * d[j].valoresNormalizados[c[i].nome];
            cout << "Score da disciplina " << d[j].cod << ": " << d[j].score << endl;
        }
    }

    return d;
}

int main()
{
    cout << "Hello, World!" << endl;

    // pegar de arquivo o nome dos criterios

    vector<Disciplina> disciplinas;
    Disciplina d1, d2, d3, d4, d5;
    d1.cod = "d1";
    d2.cod = "d2";
    d3.cod = "d3";
    d4.cod = "d4";
    d5.cod = "d5";

    d1.valores["numeroDeAlunos"] = 30;
    d2.valores["numeroDeAlunos"] = 40;
    d3.valores["numeroDeAlunos"] = 35;
    d4.valores["numeroDeAlunos"] = 38;
    d5.valores["numeroDeAlunos"] = 20;

    d1.valores["taxaDeDesistencia"] = 0.4;
    d2.valores["taxaDeDesistencia"] = 0.1;
    d3.valores["taxaDeDesistencia"] = 0.8;
    d4.valores["taxaDeDesistencia"] = 0.3;
    d5.valores["taxaDeDesistencia"] = 0.5;
    disciplinas.push_back(d1);
    disciplinas.push_back(d2);
    disciplinas.push_back(d3);
    disciplinas.push_back(d4);
    disciplinas.push_back(d5);

    vector<Criterio> criterios;
    Criterio c1;
    Criterio c2;
    c1.nome = "numeroDeAlunos";
    c1.peso = 2;
    c2.nome = "taxaDeDesistencia";
    c2.peso = 3;
    criterios.push_back(c1);
    criterios.push_back(c2);

    disciplinas = pontuarDisciplinas(disciplinas, criterios);

    sort(disciplinas.begin(), disciplinas.end(), [](Disciplina &d1, Disciplina &d2)
         { return (d1.score > d2.score); });

    cout << "Ranking de disciplinas: " << endl;

    for (int i = 0; i < disciplinas.size(); i++)
    {
        cout << "Disciplina " << disciplinas[i].cod << " com " << disciplinas[i].score << " de score." << endl;
    }
    

    cout << "\nFim do programa" << endl;

    return 0;
}