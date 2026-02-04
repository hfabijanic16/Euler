// Euler_1.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

// Ableitung x' = x / (t + 1)
static double derivative(double t, double x) {
    return x / (t + 1);
}

// Euler-Methode (number = Anzahl der kleinen Schritte)
static double euler(double t_old, double x_old, double step, int number) {
    double temp_x = x_old;
    for (int i = 0; i < number; i++) {
        temp_x = temp_x + step * derivative(t_old + step * i, temp_x);
    }
    return temp_x;
}

// Exakte Lösung des ODE: x' = x/(t+1)
static double exact_solution(double t, double t0, double x0) {
    double c = -log(t0 + 1) + 1.0 / x0;
    return 1.0 / (c - log(t + 1));
}

int main() {
    double initial_time = 0.0;
    double final_time = 1.0;
    double initial_x = 1.0;
    double initial_x2 = 1.0;
    double step = 0.1;

    double t = initial_time;
    double x1 = initial_x;
    double x2 = initial_x2;
    double h1 = step;
    double h2 = step / 2.0;

    cout << fixed << setprecision(6);
    cout << "t\t 	x1(h)\t	 x2(h/2)\t exact\t\t|x - x1|\t|x - x2|\t ratio\n";

    while (t <= final_time + 1e-12) {
        double x_exact = exact_solution(t, initial_time, initial_x);

        cout << t << "\t"
            << x1 << "\t"
            << x2 << "\t"
            << x_exact << "\t"
            << fabs(x_exact - x1) << "\t"
            << fabs(x_exact - x2) << "\t";

        if (fabs(x_exact - x1) > 0)
            cout << fabs((x_exact - x2) / (x_exact - x1));
        else
            cout << " - ";

        cout << endl;

        // Nächster Schritt
        x1 = euler(t, x1, h1, 1);  // grober Schritt
        x2 = euler(t, x2, h2, 2);  // zwei halbe Schritte

        t += step;
    }
    return 0;
}