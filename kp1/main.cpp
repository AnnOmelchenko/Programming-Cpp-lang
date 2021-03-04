#include <iostream>
#include <cmath>


float enterValue(char array[], float min, float max){
    float x;
    char issue;
    std::cout << array;
    do {
        scanf("%f", &x);
        issue = getchar();
        if (issue != '\n')
            std::cout <<"No symbols. Please, try again: ";
        else if (x > max)
            std::cout <<"Too large number! Please, try again: ";
        else if (x < min)
            std::cout <<"Too small number. Please, try again: ";

    }while (issue != '\n' || x > max || x < min);
    return x;
}


float Calculation(float arg, float step){
    float exact, sum = 0, last, factorial = 1, iteration = 0, difference, calculation = 0;
    for (int i = 0; i < 10 ; i++) {
        exact = cos(arg) * cos(arg);

        int n = 1;
        last = 1;
        while (fabs(last) >= 0.001){
            for (int c = 1; c <= 2.0 * n; c++) {
                factorial = factorial * c;
            }

            last = (pow(-1.0, n) * pow(2.0 * arg, 2.0 * n)) / factorial;
            sum += last;
            iteration += 1;
            n++;
        }
        calculation = 1.0 + (sum / 2.0);

        difference = fabs(calculation - exact);
        printf("\n     %.4lf     |      %.4lf     |     %.4lf     |      %.4lf       |    %.4lf    \n", arg, exact, calculation, iteration, difference);
        arg += step;
        sum = 0;
        factorial = 1;
        iteration = 0;
    }
};


int main() {
    float x1, x2, step, arg;

    std::cout << "Calculating an approximate value for a function cos(x)^2\nx = [-1, 1]\n\n";

    do {
        do {
            x1 = enterValue("Enter x1: ", -1, 1);
            x2 = enterValue("Enter x2: ", -1, 1);

            if (x1 == x2) {
                std::cout <<"Incorrect. Please, try again.\n";
            }
        } while (x1 == x2);

        if (x1 < x2)
            arg = x1;
        else
            arg = x2;

        step = fabs(x2 - x1) / 10.0;

        std::cout << "\n    Argument    |     cos(x)^2    |    calculation    |     iteration      |   difference   \n";
        Calculation(arg, step);
        std::cout << "Press ENTER to continue or enter any key to exit: ";
    } while (getchar() == '\n');
    return 0;
}
