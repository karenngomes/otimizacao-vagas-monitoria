#include <bits/stdc++.h>

using namespace std;

bool converte_booleano(string str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    istringstream is(str);
    bool b;
    is >> boolalpha >> b;
    return b;
}

struct Disciplina
{
    string cod;
    double score = 0;
    int maiorPesoCriterio = 0; // ver se realmente precisa
    int numeroBolsas = 0;
    bool obrigatoriamenteBolsa = false;

    map<string, double> valores;             // se for booleano, será 0 ou 1
    map<string, double> valoresNormalizados; // se for booleano, será 0 ou 1 // colocar em valores mesmo?
};

struct Criterio
{
    string nome;
    int peso = 1;
    int valor; // ver se realmente precisa (melhor menor valor?)
    bool isBinary = false;
    bool isCriterioPositivo = false; // f(x) = 1 - x
    vector<Disciplina> rankingDisciplinas;
};

vector<Disciplina> normalizar(Criterio c, vector<Disciplina> d)
{
    string nomeCriterio = c.nome;
    cout << "Tratando o criterio: " << nomeCriterio << endl;

    sort(d.begin(), d.end(), [&](Disciplina &d1, Disciplina &d2)
         { return (d1.valores[nomeCriterio] > d2.valores[nomeCriterio]); });

    c.rankingDisciplinas = d;

    double max_value = d[0].valores[nomeCriterio];
    cout << "Maior valor(?): [" << max_value << "] " << endl;

    for (int i = 0; i < d.size(); i++)
    {
        if (c.isBinary)
        {
            cout << "ta considerando binario" << endl;
            d[i].valoresNormalizados[nomeCriterio] = d[i].valores[nomeCriterio];
        }
        else
        {
            d[i].valoresNormalizados[nomeCriterio] =
                (c.isCriterioPositivo ? 1 - d[i].valores[nomeCriterio] : d[i].valores[nomeCriterio]) / max_value;
        }
    }

    if (!c.isBinary)
    {
        for (auto x : d)
        {
            cout << "Valor: [" << x.valores[nomeCriterio] << "] da disciplina " << x.cod;
            cout << " Normalizado: [" << x.valoresNormalizados[nomeCriterio] << "] " << endl;
        }

        cout << "Ranking de disciplinas do criterio " << nomeCriterio << endl;
        for (auto x : (c.rankingDisciplinas))
        {
            cout << " Valor: [" << x.valores[nomeCriterio] << "] da disciplina " << x.cod << endl;
        }
    }

    return d;
}

Disciplina desempatar(Criterio maiorCriterio, Disciplina d1, Disciplina d2)
{
    vector<Disciplina> disciplinas = maiorCriterio.rankingDisciplinas;
    for (int i = 0; i < disciplinas.size(); i++)
    {
        if (disciplinas[i].cod == d1.cod)
        {
            return d1;
        }
        if (disciplinas[i].cod == d2.cod)
        {
            return d2;
        }
    }
}

vector<Disciplina> pontuarDisciplinas(vector<Disciplina> d, vector<Criterio> c)
{
    for (int i = 0; i < c.size(); i++)
    {

        d = normalizar(c[i], d);
        for (int j = 0; j < d.size(); j++)
        {
            //*** calcula o score:
            cout << "score antes " << d[j].score << " da disciplina " << d[j].cod << " valor normalizado " << d[j].valoresNormalizados[c[i].nome] << endl;
            d[j].score += c[i].peso * d[j].valoresNormalizados[c[i].nome];
            cout << "Score da disciplina " << d[j].cod << ": " << d[j].score << endl;
        }
    }

    sort(d.begin(), d.end(), [](Disciplina &d1, Disciplina &d2)
         { return (d1.score > d2.score); });

    return d;
}

vector<Criterio> lerCriterios()
{
    string FILENAME = "criterios.txt";
    int numCriterios = 0, i = 0;
    ifstream file(FILENAME);

    vector<Criterio> criterios;

    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            numCriterios++;
            string criterio;
            Criterio criterioAuxiliar;
            istringstream ss(line);
            i = 0;
            while (getline(ss, criterio, ' '))
            {

                if (i == 0)
                    criterioAuxiliar.nome = criterio.c_str();
                if (i == 1)
                    criterioAuxiliar.peso = atoi(criterio.c_str());
                if (i == 2) 
                    criterioAuxiliar.isCriterioPositivo = converte_booleano(criterio.c_str());

                i++;
            }
            criterios.push_back(criterioAuxiliar);
        }
        file.close();
    }

    sort(criterios.begin(), criterios.end(), [](Criterio &c1, Criterio &c2)
         { return (c1.peso > c2.peso); });

    return criterios;
}

int main()
{
    cout << "Hello, World!" << endl;

    int n = 4, numDisciplinas; // numero de bolsas

    vector<Criterio> criterios;
    criterios = lerCriterios();

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

    d1.valores["disciplinaObrigatoria"] = 0;
    d2.valores["disciplinaObrigatoria"] = 1;
    d3.valores["disciplinaObrigatoria"] = 1;
    d4.valores["disciplinaObrigatoria"] = 0;
    d5.valores["disciplinaObrigatoria"] = 0;

    disciplinas.push_back(d1);
    disciplinas.push_back(d2);
    disciplinas.push_back(d3);
    disciplinas.push_back(d4);
    disciplinas.push_back(d5);

    disciplinas = pontuarDisciplinas(disciplinas, criterios);

    // Em caso de empate:
    if (n >= disciplinas.size() && disciplinas[n - 1].score == disciplinas[n].score)
    {
        Disciplina ultimaDisciplina = desempatar(criterios[0], disciplinas[n - 1], disciplinas[n]), auxiliar;
        if (disciplinas[n].cod == ultimaDisciplina.cod)
        {
            auxiliar = disciplinas[n - 1];
            disciplinas[n - 1] = disciplinas[n];
            disciplinas[n] = auxiliar;
        }
    }

    cout << "\nRanking de disciplinas: " << endl;

    for (int i = 0; i < disciplinas.size(); i++)
    {
        cout << "Disciplina " << disciplinas[i].cod << " com " << disciplinas[i].score << " de score." << endl;
    }

    cout << "\nFim do programa" << endl;

    return 0;
}