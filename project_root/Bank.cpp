#include "Bank.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;



BankAccount::BankAccount(double income) : income(income), expenditures(0),
                                          categoryExpenditures{0, 0, 0, 0, 0} {}
// Getters
double BankAccount::getIncome() const
{
    return income;
}

double BankAccount::getExpenditures() const
{
    return expenditures;
}

// Setters
void BankAccount::setIncome(double income)
{
    this->income = income;
}


void BankAccount::setExpenditure(ExpenditureCategory category, double amount)
{

    categoryExpenditures[category] = amount;
    expenditures = 0;
    for (int i = 0; i < 5; ++i)
    {
        expenditures += categoryExpenditures[i];
    }
}


double BankAccount::calculateSavings() const
{
    return income - expenditures;
}

double BankAccount::calculateExpenditurePercentage() const
{
    return (expenditures / income) * 100;
}

void BankAccount::displaySummary() const {
    cout << "Income: $" << income << endl;
    cout << "Expenditures: $" << expenditures << endl;
    cout << "Savings: $" << calculateSavings() << endl;
    cout << "Expenditure Percentage: " << calculateExpenditurePercentage() << "%" << endl;

    // Display breakdown by category
    for (int i = 0; i < 5; ++i)
    {

        double categoryPercentage = (categoryExpenditures[i] / income) * 100;

        cout << "Category " << getCategoryName(ExpenditureCategory(i))
             << ": $" << categoryExpenditures[i]
             << " (" << categoryPercentage << "%)" << endl;

    }
}


void BankAccount::saveToFile(const string& filename, const string& date) const
{
    ofstream outFile("/Users/jonahballard/Documents/M3OEP-jtballar/" + filename + ".csv", ios::app);
    if (outFile.is_open())
    {
        // Save the date with a new section
        outFile << "\nDate," << date << endl;  // Add a newline for separation

        // Write header for categories and expenditures
        outFile << "Category,Expenditure ($)" << endl;

        // Save each category and corresponding expenditure
        for (int i = 0; i < 5; ++i)
        {
            outFile << getCategoryName(ExpenditureCategory(i)) << ","
                    << fixed << setprecision(2) << categoryExpenditures[i] << endl;
        }

        // Add total income and expenditures at the end
        outFile << "Income," << income << endl;
        outFile << "Total Expenditures," << expenditures << endl;
        outFile << "Savings," << calculateSavings() << endl;
        outFile << "Expenditure Percentage," << calculateExpenditurePercentage() << "%" << endl;

        // Check if the account is a SavingsAccount and save interest rate
        const SavingsAccount* savings = dynamic_cast<const SavingsAccount*>(this);
        if (savings) {
            outFile << "Interest Rate," << savings->getInterestRate() << endl;
        }

        // Check if the account is a CheckingAccount and save overdraft limit
        const CheckingAccount* checking = dynamic_cast<const CheckingAccount*>(this);
        if (checking) {
            outFile << "Overdraft Limit," << checking->getOverdraftLimit() << endl;
        }

        outFile.close();
        cout << "Data saved successfully to " << filename + ".csv" << endl;
    }
    else
    {
        cout << "Error opening file for saving." << endl;
    }
}

void BankAccount::loadFromFile(const string& filename)
{
    ifstream inFile(filename + ".csv");
    if (inFile.is_open())
    {
        string line;
        while (getline(inFile, line))
        {

             // Read the date
            if (line.find("Date") != string::npos)
            {
                cout << endl;
                string date = line.substr(line.find(",") + 1);
                cout << "Loaded Date: " << date << endl;
                continue; // Move to the next line
            }

            // Read the header (Category, Expenditure ($))
            if (line.find("Category") != string::npos)
            {
                // Skip the header line
                continue;
            }

            // Read expenditures
            string categoryName;
            double expenditure;
            if (line.find(",") != string::npos)
            {
                stringstream ss(line);
                getline(ss, categoryName, ','); // Read the category name
                ss >> expenditure; // Read the expenditure value


                for (int i = 0; i < 5; ++i)
                {
                    if (categoryName == getCategoryName(static_cast<ExpenditureCategory>(i)))
                    {
                        setExpenditure(static_cast<ExpenditureCategory>(i), expenditure);
                        cout << categoryName << ": " << fixed << setprecision(2) << expenditure << endl; // Print expenditure info
                    }
                }
            }

            // Read income
            if (line.find("Income") != string::npos)
            {
                stringstream ss(line);
                getline(ss, categoryName, ',');
                ss >> expenditure;

                setIncome(expenditure);
                cout << categoryName << ": " << fixed << setprecision(2) << expenditure << endl;
            }
            else if (line.find("Total Expenditures") != string::npos)
            {
                cout << line << endl;
            }
            else if (line.find("Savings") != string::npos)
            {
                cout << line << endl;
            }
            else if (line.find("Expenditure Percentage") != string::npos)
            {
                cout << line << endl;
            }

            // Read interest rate
            else if (line.find("Interest Rate") != string::npos) {
                stringstream ss(line);
                getline(ss, categoryName, ',');
                ss >> expenditure;

                cout << "Interest Rate: " << fixed << setprecision(2) << expenditure << "%" << endl;  // Display interest rate
            }

            // Read overdraft limit
            else if (line.find("Overdraft Limit") != string::npos) {
                stringstream ss(line);
                getline(ss, categoryName, ',');  // Read "Overdraft Limit"
                ss >> expenditure;  // Read the overdraft limit value

                cout << "Overdraft Limit: $" << fixed << setprecision(2) << expenditure << endl;  // Display overdraft limit
            }
        }

        inFile.close();
    }
    else
    {
        cout << "Error opening file for loading." << endl;
    }
}

string BankAccount::getCategoryName(ExpenditureCategory category) const
{

    switch (category)
    {
        case FOOD: return "Food";
        case UTILITIES: return "Utilities";
        case ENTERTAINMENT: return "Entertainment";
        case TRANSPORTATION: return "Transportation";
        case OTHER: return "Other";
    }
}

void BankAccount::resetExpenditures() {
    for (int i = 0; i < 5; ++i) {
        categoryExpenditures[i] = 0; // Assuming categoryExpenditures is an array or vector
    }
}

SavingsAccount::SavingsAccount(double income, double interestRate)
        : BankAccount(income), interestRate(interestRate) {}

void SavingsAccount::applyInterest() {
    double interest = income * interestRate;
    income += interest;
    cout << "Interest of $" << interest << " applied to savings." << endl;
}

void SavingsAccount::displaySummary() const {
    BankAccount::displaySummary();
    cout << "Interest Rate: " << interestRate * 100 << "%" << endl;
}

CheckingAccount::CheckingAccount(double income, double overdraftLimit)
        : BankAccount(income), overdraftLimit(overdraftLimit) {}

void CheckingAccount::chargeOverdraft(double amount) {
    if ((expenditures + amount) > (income - overdraftLimit)) {
        cout << "Overdraft limit exceeded. Transaction denied." << endl;
    } else {
        expenditures += amount;
        cout << "Overdraft charge of $" << amount << " applied." << endl;
    }
}

void CheckingAccount::displaySummary() const {
    BankAccount::displaySummary();
    cout << "Overdraft Limit: $" << overdraftLimit << endl;
}


// SavingsAccount getters and setters
double SavingsAccount::getInterestRate() const {
    return interestRate;
}

void SavingsAccount::setInterestRate(double rate) {
    interestRate = rate;
}

// CheckingAccount getters and setters
double CheckingAccount::getOverdraftLimit() const {
    return overdraftLimit;
}

void CheckingAccount::setOverdraftLimit(double limit) {
    overdraftLimit = limit;
}

