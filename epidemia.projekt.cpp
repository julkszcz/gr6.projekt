#include <iostream>
#include <cmath> 
using namespace std;

void showPopulation(int day, int susceptible, int infected, int recovered);
bool checkPopulation(int susceptible, int infected, int recovered);
void simulateDay(int &susceptible, int &infected, int &recovered, int &day, double infectionRate, double recoveryRate);
void changeParameters(double &infectionRate, double &recoveryRate);

int main() {
    int susceptible = 80;
    int infected = 10;
    int recovered = 10;
    int day = 0;

    double infectionRate = 0.20;
    double recoveryRate = 0.10;

    int choice = 0;

    do {
        showPopulation(day, susceptible, infected, recovered);

        cout << "\n=== Epidemic Simulator ===" << endl;
        cout << "1. Simulate next day" << endl;
        cout << "2. Change model parameters" << endl;
        cout << "3. Exit" << endl;
        cout << "Your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                simulateDay(susceptible, infected, recovered, day, infectionRate, recoveryRate);
                if (!checkPopulation(susceptible, infected, recovered)) {
                    cout << "BŁĄD: Niepoprawny stan populacji! Suma nie wynosi 100 lub wystąpiły wartości ujemne." << endl;
                }
                break;
            }
            case 2: {
                changeParameters(infectionRate, recoveryRate);
                break;
            }
            case 3: {
                cout << "Zamykanie programu..." << endl;
                break;
            }
            default: {
                cout << "Nieprawidłowy wybór! Wybierz opcję od 1 do 3." << endl;
                break;
            }
        }
        cout << endl;

    } while (choice != 3);

    return 0;
}

void showPopulation(int day, int susceptible, int infected, int recovered) {
    cout << "\nDay: " << day << endl;
    cout << "Susceptible: " << susceptible << endl;
    cout << "Infected: " << infected << endl;
    cout << "Recovered: " << recovered << endl;
    cout << "Total: " << (susceptible + infected + recovered) << endl;
}


bool checkPopulation(int susceptible, int infected, int recovered) {
    if (susceptible < 0 || infected < 0 || recovered < 0) {
        return false;
    }
    if ((susceptible + infected + recovered) != 100) {
        return false;
    }
    return true;
}

void simulateDay(int &susceptible, int &infected, int &recovered, int &day, double infectionRate, double recoveryRate) {
    int oldInfected = infected;

    int newInfections = static_cast<int>(floor(oldInfected * infectionRate));
    int newRecoveries = static_cast<int>(floor(oldInfected * recoveryRate));

    if (newInfections > susceptible) {
        newInfections = susceptible;
    }

    if (newRecoveries > infected) {
        newRecoveries = infected;
    }

    susceptible = susceptible - newInfections;
    infected = infected + newInfections - newRecoveries;
    recovered = recovered + newRecoveries;

    day++;
}

void changeParameters(double &infectionRate, double &recoveryRate) {
    double tempInfection, tempRecovery;

    cout << "Enter infection rate (0-1): ";
    cin >> tempInfection;

    cout << "Enter recovery rate (0-1): ";
    cin >> tempRecovery;

    if (tempInfection >= 0.0 && tempInfection <= 1.0 && tempRecovery >= 0.0 && tempRecovery <= 1.0) {
        infectionRate = tempInfection;
        recoveryRate = tempRecovery;
        cout << "Parameters updated." << endl;
    } else {
        cout << "Błąd: Współczynniki muszą należeć do przedziału [0, 1]. Parametry nie zostały zmienione." << endl;
    }
}