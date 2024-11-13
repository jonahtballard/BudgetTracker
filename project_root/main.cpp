#include <iostream>
#include "Bank.h"
#include <string>
#include <sstream>
#include <regex>
#include <fstream>
#include <chrono>
#include <thread>





using namespace std;

// Function to check if file exists
bool fileExists(const std::string& filename) {
    std::ifstream file(filename);
    return file.good();
}


//helper functiion
string getAccountTypeInput()
{
    string accountType;
    while (true)
    {
        cout << "Enter account type (Savings/Checking): ";
        getline(cin, accountType);

        if (accountType == "Savings" || accountType == "Checking")
        {
            return accountType;
        }
        else
        {
            cout << "Invalid input. Please enter either 'Savings' or 'Checking'." << endl;
        }
    }
}

// Helper function to get positive input
double getPositiveInput(const string prompt)
{
    string input;
    double num;

    while (true)
    {
        cout << prompt;
        getline(cin, input);

        stringstream ss(input);
        if (ss >> num && ss.eof() && num > 0) // Validate if the number is positive
        {
            return num;
        }
        else
        {
            cout << "Invalid input. Please enter a positive number." << endl;
        }
    }
}

// Helper function to get a valid filename from the user
string getFilenameInput(const string& prompt)
{
    string filename;
    cout << prompt;
    getline(cin, filename);
    return filename;
}

// Helper function to get a valid date in MM/DD/YYYY format
string getDateInput()
{
    string date;
    regex datePattern(R"((\d{2})\/(\d{2})\/(\d{4}))");  // Match MM/DD/YYYY format

    while (true)
    {
        cout << "Enter the current date (MM/DD/YYYY): ";
        getline(cin, date);

        if (regex_match(date, datePattern))
        {
            return date;
        }
        else
        {
            cout << "Invalid date format. Please use MM/DD/YYYY." << endl;
        }
    }
}

// Get int from 1 to 5
int getMenuChoice()
{
    int choice;
    string input;
    bool valid = false;

    while (!valid)
    {
        cout << "Choose an option (1-5): ";
        getline(cin, input);

        stringstream ss(input);

        if (ss >> choice && ss.eof() && choice >= 1 && choice <= 5)
        {
            valid = true;
        }
        else
        {
            cout << "Invalid input. Please enter a number between 1 and 5: ";
        }
    }

    return choice;
}

int main()
{
    // get the date when the app starts
    string currentDate = getDateInput();

    // see what account type they wanted
    string accountType = getAccountTypeInput();

    // Bank account initialization based on the account type
    SavingsAccount savingsAccount(0, 0.0);
    CheckingAccount checkingAccount(0, 0.0);

    bool isSavingsAccount = false;

    if (accountType == "Savings")
    {
        double interestRate = getPositiveInput("Enter the interest rate for the savings account: ");
        savingsAccount = SavingsAccount(0, interestRate);
        isSavingsAccount = true;
    }
    else if (accountType == "Checking")
    {
        double overdraftLimit = getPositiveInput("Enter the overdraft limit for the checking account: ");
        checkingAccount = CheckingAccount(0, overdraftLimit);
    }

    bool incomeAndExpendituresEntered = false;  // Track if income and expenditures are entered

    int choice;
    do
    {
        cout << "\n=== Banking App Menu ===\n";
        cout << "1. Enter Income and Expenditures\n";
        cout << "2. Display Financial Summary\n";
        cout << "3. Save to File (only available after entering income and expenditures)\n";
        cout << "4. Load from File\n";
        cout << "5. Exit\n";

        // Get a valid menu choice
        choice = getMenuChoice();

        switch (choice)
        {
            case 1:
                // Get income from user
                if (isSavingsAccount)
                    savingsAccount.setIncome(getPositiveInput("Enter your monthly income: "));
                else
                    checkingAccount.setIncome(getPositiveInput("Enter your monthly income: "));

                // Loop through each expenditure category and get input
                for (int i = 0; i < 5; ++i)
                {
                    ExpenditureCategory category = static_cast<ExpenditureCategory>(i);
                    double amount = getPositiveInput("Enter expenditures for " + (isSavingsAccount ? savingsAccount.getCategoryName(category) : checkingAccount.getCategoryName(category)) + ": ");
                    if (isSavingsAccount)
                        savingsAccount.setExpenditure(category, amount);
                    else
                        checkingAccount.setExpenditure(category, amount);
                }

                incomeAndExpendituresEntered = true;  // Mark that income and expenditures have been entered
                break;

            case 2:
                // Display summary of financials
                if (isSavingsAccount)
                    savingsAccount.displaySummary();
                else
                    checkingAccount.displaySummary();
                break;

            case 3:
                // Save data to file (only if income and expenditures were entered)
                if (incomeAndExpendituresEntered)
                {
                    //ADJUST BASHPATH TO YOUR DIRECTORY
                    string basePath = "project_root";
                    string filename = getFilenameInput("Enter the filename to save to: ");
                    string fullPath = basePath + filename;


                    if (isSavingsAccount)
                        savingsAccount.saveToFile(filename, currentDate);  // Pass the date to save
                    else
                        checkingAccount.saveToFile(filename, currentDate);  // Pass the date to save

                    string command = "python project_root/sort_csv.py " + fullPath;
                    system(command.c_str());


                    string command1 = "python project_root/render.py " + fullPath;
                    system(command1.c_str());



                    // Prompt for a new date and reset income and expenditures
                    currentDate = getDateInput();  // Get new date
                    if (isSavingsAccount)
                    {
                        savingsAccount.resetExpenditures();  // Reset expenditures to 0
                        savingsAccount.setIncome(0);         // Reset income to 0
                    }
                    else
                    {
                        checkingAccount.resetExpenditures();  // Reset expenditures to 0
                        checkingAccount.setIncome(0);         // Reset income to 0
                    }
                    incomeAndExpendituresEntered = false;  // Reset the flag

                    // Ask for account type again
                    accountType = getAccountTypeInput();

                    // Reinitialize account based on new account type
                    if (accountType == "Savings")
                    {
                        double interestRate = getPositiveInput("Enter the interest rate for the savings account: ");
                        savingsAccount = SavingsAccount(0, interestRate);
                        isSavingsAccount = true;
                    }
                    else if (accountType == "Checking")
                    {
                        double overdraftLimit = getPositiveInput("Enter the overdraft limit for the checking account: ");
                        checkingAccount = CheckingAccount(0, overdraftLimit);
                        isSavingsAccount = false;
                    }
                }
                else
                {
                    cout << "You must enter income and expenditures before saving to a file." << endl;
                }
                break;

            case 4:
                // Load data from file
            {
                string filename = getFilenameInput("Enter the filename to load from: ");
                if (isSavingsAccount)
                    savingsAccount.loadFromFile(filename);
                else
                    checkingAccount.loadFromFile(filename);
            }
                break;

            case 5:
                // Quit the program
                cout << "Exiting the program.\n";
                break;
        }
    }
    while (choice != 5);

    return 0;
}
