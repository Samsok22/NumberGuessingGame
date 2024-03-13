#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include <limits> // wykorzystane do utworzenia limitów

using namespace std;
class NumberGuesser {
private:
    int secretNumber;
    vector<int> guessedNumbers;

public:
    NumberGuesser() {
        random_device rd;
        uniform_int_distribution<int> dist(0, 100);
        secretNumber = dist(rd);
    }

    void guessNumber() {  // funkcja realizujaca zgadywanie
        int guess;
        cout << "Podaj dowolna liczbe z przedzialu od 0 do 100: " << endl;

        while (true) {
            if (!(cin >> guess)) {
                // nie wprowadzono int
                cin.clear(); // czyszczenie flagi błedow
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // zignoruj nieodpowiedni argument
                cout << "Blad! Wprowadz poprawna liczbe." << endl;
                continue;
            }

            guessedNumbers.push_back(guess);

            if (guess == secretNumber) {
                cout << "ZGADLES LICZBE! GRATULACJE!" << endl;
                saveToFile();
                break;
            }
            else {
                if (guess < secretNumber) {
                    cout << "Za niska liczba ";
                }
                else {
                    cout << "Za wysoka liczba ";
                }
                cout << "Sprobuj ponownie :)" << endl;
            }
        }
    }

    void saveToFile() { //funkcja zapisywania
        ofstream file("guessed_numbers.txt");

        if (file.is_open()) {
            for (int number : guessedNumbers) {
                file << number << " ";
            }

            file.close();
            cout << "Zapisano zgadniete liczby do pliku." << endl;
        }
        else {
            cerr << "Blad przy zapisie do pliku." << endl;
        }
    }

    void loadFromFile() {  // funkcja wczytywania
        ifstream file("guessed_numbers.txt");

        if (file.is_open()) {
            int number;
            while (file >> number) {
                guessedNumbers.push_back(number);
            }

            file.close();
            cout << "Wczytano zgadniete liczby z pliku." << endl;
        }
        else {
            cerr << "Plik nie istnieje. Bedzie utworzony przy zapisie." << endl;
        }
    }
};

int main() {
    NumberGuesser guesser;

    guesser.loadFromFile(); // zaladuj poprzednio zgadniete liczby

    while (true) {
        cout << "1. Zgadnij liczbe" << endl;
        cout << "2. Zakoncz program" << endl;

        int choice;
        cin >> choice;

        switch (choice) {
        case 1:
            guesser.guessNumber();
            break;
        case 2:
            guesser.saveToFile(); // zapisz zgadniete liczby przed wyjściem z programu
            return 0;
        default:
            cout << "Nieprawidlowy wybor. Sprobuj ponownie." << endl;
        }
    }

    return 0;
}
