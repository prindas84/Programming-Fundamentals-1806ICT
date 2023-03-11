#include <stdio.h>
#include <math.h>

// DECLARE A STRUCTURE
struct fract
{
    int numerator;
    int denominator;
};
typedef struct fract Fraction;

Fraction add_fraction(Fraction f_one, Fraction f_two);
Fraction subtract_fraction(Fraction f_one, Fraction f_two);
Fraction multiply_fraction(Fraction f_one, Fraction f_two);
Fraction divide_fraction(Fraction f_one, Fraction f_two);
Fraction scalar_multiply_fraction(Fraction f_one, int scalar);
int highest_common_divisor(int a, int b);

int main()
{
    Fraction f_one;
    Fraction f_two;

    printf("FRACTION ONE (NUMERATOR / DENOMINATOR): ");
    scanf("%d %d", &f_one.numerator, &f_one.denominator);
    printf("FRACTION TWO (NUMERATOR / DENOMINATOR): ");
    scanf("%d %d", &f_two.numerator, &f_two.denominator);

    Fraction sum = add_fraction(f_one, f_two);
    Fraction subtract = subtract_fraction(f_one, f_two);
    Fraction multiply = multiply_fraction(f_one, f_two);
    Fraction divide = divide_fraction(f_one, f_two);
    Fraction scalar = scalar_multiply_fraction(f_one, 2);

    printf("SUM: %d / %d\n", sum.numerator, sum.denominator);
    printf("SUBTRACT: %d / %d\n", subtract.numerator, subtract.denominator);
    printf("MULTIPLY: %d / %d\n", multiply.numerator, multiply.denominator);
    printf("DIVIDE: %d / %d\n", divide.numerator, divide.denominator);
    printf("SCALAR: %d / %d\n", scalar.numerator, scalar.denominator);
    
    return 0;
}

Fraction add_fraction(Fraction f_one, Fraction f_two)
{
    Fraction sum;
    sum.numerator = (f_one.numerator * f_two.denominator) + (f_two.numerator * f_one.denominator);
    sum.denominator = f_one.denominator * f_two.denominator;
    int reduce = highest_common_divisor(sum.numerator, sum.denominator);
    sum.numerator /= reduce;
    sum.denominator /= reduce;
    return sum;
}


Fraction subtract_fraction(Fraction f_one, Fraction f_two)
{
    Fraction subtract;
    subtract.numerator = (f_one.numerator * f_two.denominator) - (f_two.numerator * f_one.denominator);
    subtract.denominator = f_one.denominator * f_two.denominator;
    int reduce = highest_common_divisor(subtract.numerator, subtract.denominator);
    subtract.numerator /= reduce;
    subtract.denominator /= reduce;
    return subtract;
}


Fraction multiply_fraction(Fraction f_one, Fraction f_two)
{
    Fraction multiply;
    multiply.numerator = f_one.numerator * f_two.numerator;
    multiply.denominator = f_one.denominator * f_two.denominator;
    int reduce = highest_common_divisor(multiply.numerator, multiply.denominator);
    multiply.numerator /= reduce;
    multiply.denominator /= reduce;
    return multiply;
}


Fraction divide_fraction(Fraction f_one, Fraction f_two)
{
    Fraction divide;
    divide.numerator = f_one.numerator * f_two.denominator;
    divide.denominator = f_one.denominator * f_two.numerator;
    int reduce = highest_common_divisor(divide.numerator, divide.denominator);
    divide.numerator /= reduce;
    divide.denominator /= reduce;
    return divide;
}

Fraction scalar_multiply_fraction(Fraction f_one, int scalar)
{
    Fraction multiply;
    multiply.numerator = f_one.numerator * scalar;
    multiply.denominator = f_one.denominator * 1;
    int reduce = highest_common_divisor(multiply.numerator, multiply.denominator);
    multiply.numerator /= reduce;
    multiply.denominator /= reduce;
    return multiply;
}

int highest_common_divisor(int a, int b)
{
    int h = a;
    if (b > a)
    {
        h = b;
    }
    for (int i = h; i > 0; i--)
    {
        if (a % i == 0 && b % i == 0)
        return i;
    }
    return 1;
}


