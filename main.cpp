#include <iostream>
#include <tuple>
#include <math.h>
#include <vector>

#define valori

using std::cout;
using std::endl;
using std::get;
using std::make_tuple;
using std::tie;
using std::tuple;
using std::vector;

#define double_size(x) sizeof(x) / sizeof(double)

tuple<double, double> ricavaRetta(double X1, double X2, double Y1, double Y2);
double errore_percentuale(double m, double c, double x, double y);

int main()
{
    const double peso[]{1, 5, 10, 20, 40};
    const double misure[]{0.2, 0.9, 1.9, 4.2, 8.5};

    if (double_size(peso) != double_size(misure))
    { // controlla sei i dati sono pari
        cout << "il numero di misure non corrisponde al numero dei campioni" << endl;
        return 1;
    }

    double coef_angolare;
    double term_noto;
    double errore_totale = 0;
    vector<tuple<int, int, double>> errore_medio;

    for (int i = 0; i < double_size(peso) - 1; i++) //-1 perche le combinazioni con l'ultimo numero sono gia calcolate
    {
        for (int j = i + 1; j < double_size(peso); j++)
        {

            tie(coef_angolare, term_noto) = ricavaRetta(peso[i], peso[j], misure[i], misure[j]);

            for (int l = 0; l < double_size(peso); l++) // applico a tutti i punti
            {
                if (l != i && l != j) // diversi dai punti che formano la retta
                {
                    errore_totale += errore_percentuale(coef_angolare, term_noto, peso[l], misure[l]);
                }
            }

            errore_medio.push_back(make_tuple(i, j, errore_totale / (double_size(peso) - 2)));
            errore_totale = 0;
        }
    }

    tuple<int, int, double> min = errore_medio[0];
    for (int i = 0; i < errore_medio.size(); i++) // compara ogni retta per trovare quella con errore medio minore
    {
        if (get<2>(errore_medio[i]) < get<2>(min))
        {
            min = errore_medio[i];
        }

#ifdef valori
        cout << get<0>(errore_medio[i]) + 1 << "   ";
        cout << get<1>(errore_medio[i]) + 1 << "   ";
        cout << get<2>(errore_medio[i]) << " %   ";
        cout << endl;
#endif
    }

    cout << endl;
    cout << get<0>(min) + 1 << "   ";
    cout << get<1>(min) + 1 << "   ";
    cout << get<2>(min) << " %   ";
    
    std::cin.get();

    return 0;
}

tuple<double, double> ricavaRetta(double X1, double X2, double Y1, double Y2)
{
    double m = (Y1 - Y2) / (X1 - X2);
    double c = Y2 - m * X2;
    return make_tuple(m, c);
}

double errore_percentuale(double m, double c, double x, double y)
{
    double y_calcolata = x * m + c;
    double delta = y - y_calcolata;
    return (fabs(delta) / y) * 100;
}
