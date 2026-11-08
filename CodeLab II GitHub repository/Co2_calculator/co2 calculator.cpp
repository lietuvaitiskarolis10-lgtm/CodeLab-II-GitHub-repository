#include <iostream>
using namespace std;

// get the distance from the user
double getDistance()
{
    double miles;
    cout << "Enter distance travelled in miles: ";
    cin >> miles;
    return miles;
}

// get the fuel type from the user
char getFuelType()
{
    char fuel;
    cout << "Enter fuel type (D for diesel, P for petrol): ";
    cin >> fuel;
    return fuel;
}

// work out the co2
double calculateCO2(double miles, char fuel)
{
    double litres = miles * 9.66 / 100;

    if (fuel == 'D' || fuel == 'd')
        return litres * 2.68;
    else
        return litres * 2.31;
}

int main()
{
    double miles = getDistance();
    char fuel = getFuelType();
    double co2 = calculateCO2(miles, fuel);

    cout << "Your journey produced " << co2 << " kg of CO2" << endl;

    return 0;
}