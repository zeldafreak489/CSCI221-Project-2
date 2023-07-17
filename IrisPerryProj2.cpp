// Author: Iris Perry
// Version: 06-19-2023


#include <iostream>
#include <fstream>
using namespace std;

class CDAccount {
    public:
        CDAccount();
        // pre-condition: An object of type CDAccount is being declared with no arguments
        // post-condition: Sets balance, interest rate, and term to 0.
        CDAccount(double new_balance, double new_interest_rate, int new_term);
        // pre-condition: An object of type CDAccount is being declared with 3 arguements
        // post-condition: Sets balance to first argument, interest rate to second, and 
        // term to third.
        double get_initial_balance() const;
        // pre-condition: balance (dollar and cent) has been initialized.
        // post-condition: returns the inital balance.
        double get_balance_at_maturity() const;
        // pre-condition: balance (dollar and cent), interest_rate, and term have been intialized.
        // post-condition: returns the balance at maturity.
        double get_interest_rate() const;
        // pre-condition: interest_rate has been initialized.
        // post-condition: returns the current interest rate as a percentage.
        int get_term() const;
        // pre-condition: term has been initialized.
        // post-condition: returns the term of maturity in months.
        void input(istream& in);
        // pre-condition: An object of type CDAccount has been declared.
        // post-condition: Receives input from the user or a file and initializes dollar, cent, interest_rate, and balance.
        void output(ostream& out);
        // pre-condition: If out is a file output stream, then out
        // has already been connected to a file
        // post-condition: Interest rate, initial account balance, term, and balance at maturity
        // have been written to the stream out.

    private:
        int dollar;
        int cent;
        double interest_rate;
        int term; // months until maturity
};

void menu();
// pre-condition: none
// post-condition: prints a menu to the screen for selection

int main() {
    int choice;
    
    do {
        menu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                CDAccount account;
                account.output(cout);
                break;
            }
            case 2: {
                CDAccount account2(100.0, 10.0, 6);
                account2.output(cout);
                break;
            }
            case 3: {
                CDAccount account3;
                cout << "Please enter the CD initial balance, interest rate, and term: " << endl;
                account3.input(cin);
                account3.output(cout);
                break;
            }
            case 4: {
                CDAccount account4;
                ofstream file_out;
                cout << "Please enter the CD initial balance, interest rate, and term: " << endl;
                account4.input(cin);
                file_out.open("Account_Information.txt");
                if (file_out.fail()) {
                    cout << "Could not open file." << endl;
                    exit(1);
                }
                account4.output(file_out);
                file_out.close();
                break;
            }
        }

    } while (choice != 5);

    return 0;
}

// Constructors:

// Default constructor:
CDAccount::CDAccount() { 
    dollar = 0;
    cent = 0;
    interest_rate = 0;
    term = 0;
}

// Constructor for initialization:
CDAccount::CDAccount(double new_balance, double new_interest_rate, int new_term) { 
    dollar = static_cast<int>(new_balance);
    cent = static_cast<int>((new_balance - dollar) * 100);
    interest_rate = new_interest_rate;
    term = new_term;
}

// Accessor functions:

// Access initial balance, convert to double
double CDAccount::get_initial_balance() const {
    double balance;
    balance = static_cast<double>(dollar + (cent / 100));
    return balance;
}

// Balance after maturity
double CDAccount::get_balance_at_maturity() const {
    double balance;
    balance = static_cast<double>(dollar + (cent / 100));
    double interest = balance * (interest_rate / 100.0) * (term / 12.0);
    return balance + interest;
}

// Access interest rate
double CDAccount::get_interest_rate() const {
    return interest_rate;
}

// Access term
int CDAccount::get_term() const {
    return term;
}

// Input and convert balance to dollars and cents, both in integers
void CDAccount::input(istream& in) {
    double balance;
    in >> balance; // get initial balance from user

    // convert balance to dollars and cents since this is how balance is stored
    dollar = (int)balance; // dollar is the integer part of balace
    cent = (int)((balance - dollar) * 100); // cent is the fraction part * 100

    in >> interest_rate; // get interest rate from user
    in >> term; // get term from user
}

// Output
void CDAccount::output(ostream& out) {
    out.setf(ios::fixed);
    out.setf(ios::showpoint);
    out.precision(2);
    out << "CD Account interest rate: " << get_interest_rate() << endl;
    out << "CD Account initial balance: " << get_initial_balance() << endl;
    out << "When your CD matures in " << get_term() << " months " << endl;
    out << "it will have a balance of " << get_balance_at_maturity() << " dollars." << endl;
    out << endl;
}

// Menu for main function:
void menu() {
    cout << "\n\t************************************************************************";
    cout << "\n\t*                   Menu                                               *";
    cout << "\n\t* 1. Use default constructor and output to screen                      *";
    cout << "\n\t* 2. Use constructor with predetermined amounts and output to screen   *";
    cout << "\n\t* 3. Input own amounts and output to screen                            *";
    cout << "\n\t* 4. Input own amounts and output to file                              *";
    cout << "\n\t* 5. Quit                                                              *";
    cout << "\n\t************************************************************************";
    cout << endl;
}