#include <bits/stdc++.h>

using namespace std;

bool convert_boolean(string str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    istringstream is(str);
    bool b;
    is >> boolalpha >> b;
    return b;
}

struct Discipline
{
    string code;
    double score = 0;
    map<string, double> values;             
    map<string, double> normalizedValues; 
};

struct Criteria
{
    string name;
    int weight = 1;
    // int valor; 
    bool isPositiveCriteria = false; // f(x) = 1 - x
    vector<Discipline> rankingDisciplines;
};

vector<Discipline> normalize(Criteria c, vector<Discipline> d)
{
    string nameCriterion = c.name;
    cout << "Tratando o criteria: " << nameCriterion << endl;

    sort(d.begin(), d.end(), [&](Discipline &d1, Discipline &d2)
         { return (d1.values[nameCriterion] > d2.values[nameCriterion]); });

    c.rankingDisciplines = d;

    double max_value = d[0].values[nameCriterion];

    for (int i = 0; i < d.size(); i++)
    {
        d[i].normalizedValues[nameCriterion] =
                (c.isPositiveCriteria ? 1 - d[i].values[nameCriterion] : d[i].values[nameCriterion]) / max_value;
        
    }

    
        for (auto x : d)
        {
            cout << "Valor: [" << x.values[nameCriterion] << "] da discipline " << x.code;
            cout << " Normalizado: [" << x.normalizedValues[nameCriterion] << "] " << endl;
        }

        cout << "Ranking de disciplines do criteria " << nameCriterion << endl;
        for (auto x : (c.rankingDisciplines))
        {
            cout << " Valor: [" << x.values[nameCriterion] << "] da discipline " << x.code << endl;
        }
    

    return d;
}

Discipline desempatar(Criteria c, Discipline d1, Discipline d2)
{
    vector<Discipline> disciplines = c.rankingDisciplines;
    for (int i = 0; i < disciplines.size(); i++)
    {
        if (disciplines[i].code == d1.code)
        {
            return d1;
        }
        if (disciplines[i].code == d2.code)
        {
            return d2;
        }
    }
}

vector<Discipline> calculateDisciplinesScore(vector<Discipline> d, vector<Criteria> c)
{
    for (int i = 0; i < c.size(); i++)
    {

        d = normalize(c[i], d);
        for (int j = 0; j < d.size(); j++)
        {
            //*** calcula o score: ***//
            d[j].score += c[i].weight * d[j].normalizedValues[c[i].name];
        }
    }

    sort(d.begin(), d.end(), [](Discipline &d1, Discipline &d2)
         { return (d1.score > d2.score); });

    return d;
}

vector<Criteria> readCriteria()
{
    string FILENAME = "criteria.txt";
    int numCriterias = 0, i = 0;
    ifstream file(FILENAME);

    vector<Criteria> criterias;

    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            numCriterias++;
            string criteria;
            Criteria criteriaAuxiliar;
            istringstream ss(line);
            i = 0;
            while (getline(ss, criteria, ' '))
            {

                if (i == 0)
                    criteriaAuxiliar.name = criteria.c_str();
                if (i == 1)
                    criteriaAuxiliar.weight = atoi(criteria.c_str());
                if (i == 2) 
                    criteriaAuxiliar.isPositiveCriteria = convert_boolean(criteria.c_str());

                i++;
            }
            criterias.push_back(criteriaAuxiliar);
        }
        file.close();
    }

    sort(criterias.begin(), criterias.end(), [](Criteria &c1, Criteria &c2)
         { return (c1.weight > c2.weight); });

    return criterias;
}

int main()
{
    cout << "Hello, World!" << endl;

    int n = 4; // numero de bolsas

    vector<Criteria> criterias;
    criterias = readCriteria();

    vector<Discipline> disciplines;

    Discipline d1, d2, d3, d4, d5;
    d1.code = "d1";
    d2.code = "d2";
    d3.code = "d3";
    d4.code = "d4";
    d5.code = "d5";

    d1.values["numeroDeAlunos"] = 30;
    d2.values["numeroDeAlunos"] = 40;
    d3.values["numeroDeAlunos"] = 35;
    d4.values["numeroDeAlunos"] = 38;
    d5.values["numeroDeAlunos"] = 20;

    d1.values["taxaDeDesistencia"] = 0.4;
    d2.values["taxaDeDesistencia"] = 0.1;
    d3.values["taxaDeDesistencia"] = 0.8;
    d4.values["taxaDeDesistencia"] = 0.3;
    d5.values["taxaDeDesistencia"] = 0.5;

    d1.values["disciplinaObrigatoria"] = 0;
    d2.values["disciplinaObrigatoria"] = 1;
    d3.values["disciplinaObrigatoria"] = 1;
    d4.values["disciplinaObrigatoria"] = 0;
    d5.values["disciplinaObrigatoria"] = 0;

    disciplines.push_back(d1);
    disciplines.push_back(d2);
    disciplines.push_back(d3);
    disciplines.push_back(d4);
    disciplines.push_back(d5);

    disciplines = calculateDisciplinesScore(disciplines, criterias);

    // Em caso de empate:
    if (n >= disciplines.size() && disciplines[n - 1].score == disciplines[n].score)
    {
        Discipline ultimaDiscipline = desempatar(criterias[0], disciplines[n - 1], disciplines[n]), auxiliar;
        if (disciplines[n].code == ultimaDiscipline.code)
        {
            auxiliar = disciplines[n - 1];
            disciplines[n - 1] = disciplines[n];
            disciplines[n] = auxiliar;
        }
    }

    cout << "\nRanking de disciplines: " << endl;

    for (int i = 0; i < disciplines.size(); i++)
    {
        cout << "Discipline " << disciplines[i].code << " com " << disciplines[i].score << " de score." << endl;
    }

    cout << "\nFim do programa" << endl;

    return 0;
}