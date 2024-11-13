#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include <string>
using namespace std;

// Enum for expenditure categories
enum ExpenditureCategory {
    FOOD,
    UTILITIES,
    ENTERTAINMENT,
    TRANSPORTATION,
    OTHER,
};

// Class representing a bank account with income and expenditures
class BankAccount {
protected:
    double income;
    double expenditures;
    double categoryExpenditures[5];


public:
    /*
     * Constructor to initialize a BankAccount object with a given income.
     * Requires: income to be a valid double value.
     * Modifies: income, expenditures, categoryExpenditures
     * Effects: Starts income, sets expenditures to 0, and all categoryExpenditures to 0.
     */
    BankAccount(double income = 0.0);

    /*
     * Gets the current income.
     * Requires: nothing
     * Modifies: nothing
     * Effects: Returns the value of income.
     */
    double getIncome() const;

    /*
     * Gets the total expenditures.
     * Requires: nothing
     * Modifies: nothing
     * Effects: Returns the value of expenditures.
     */
    double getExpenditures() const;

    /*
     * Sets the monthly income.
     * Requires: income to be a valid double value.
     * Modifies: income
     * Effects: Updates the income to the specified value.
     */
    void setIncome(double income);

    /*
     * Sets the expenditure for a specific category.
     * Requires: category to be a valid ExpenditureCategory and amount to be a non-negative double.
     * Modifies: categoryExpenditures, expenditures
     * Effects: Updates the categoryExpenditures array and recalculates total expenditures.
     */
    void setExpenditure(ExpenditureCategory category, double amount);

    /*
     * Calculates the savings as the difference between income and expenditures.
     * Requires: nothing
     * Modifies: nothing
     * Effects: Returns the savings amount.
     */
    double calculateSavings() const;

    /*
     * Percentage of income used for expenditures.
     * Requires: cant be negative number
     * Modifies: nothing
     * Effects: Returns the expenditure percent
     */
    double calculateExpenditurePercentage() const;

    /*
     * Displays a summary of the financial status.
     * Requires: nothing
     * Modifies: output
     * Effects: Prints income, expenditures, savings, expenditure percentage
     */
    virtual void displaySummary() const;

    /*
     * Getter for category name
     * Requires: ExpenditureCategory
     * Modifies: nothing
     * Effects: Gives back name of category in string form
     */
    string getCategoryName(ExpenditureCategory category) const;

    /*
    * Saves the data to a file.
   * Requires: A  filename and date .
   * Modifies: Makes or updates the file with the financial data.
   * Effects: Writes income, expenditures, and the date into the file.
     * */
    void saveToFile(const string& filename, const string& date) const;

    /*
    * Loads  data from a file.
   * Requires: A  filename .
   * Modifies: Nothing.
   * Effects: Prints contents of the file to the console
   */
    void loadFromFile(const string& filename);

    /*
   * Resets all expenditures to zero.
   * Requires: nothing
   * Modifies: Sets all category expenditures to 0.
    * Effects: Clears all current expenditure values.
    */
    void resetExpenditures();

};


// is a relationship for Savings account
class SavingsAccount : public BankAccount {
public:
    //adds interest rate to bank account
    SavingsAccount(double income, double interestRate);

    /*
     * Applies interest to the savings account balance.
     * Requires: nothing
     * Modifies: Updates the balance based on the interest rate.
    * Effects: Increases the account balance by the interest amount.
    */
    void applyInterest();

    /*
     * Displays everything in the savings account.
    * Requires: nothing
    * Modifies: all of bankaccount as well as the interset rate.
    * Effects: Shows the account balance, income, expenditures, and savings, interest rate.
    */
    void displaySummary() const override;

      /*
     * Gets the current interest rate for the savings account.
    * Requires: nothing
     * Modifies: nothing
     * Effects: Returns the interest rate as a double.
    */
    double getInterestRate() const;

   /*
    * Sets the interest rate for the savings account.
    * Requires: takes in a double value for interest.
    * Modifies: updates interest rate based on that value.
    * Effects: changes the interest rate .
    */
    void setInterestRate(double rate);

private:
    double interestRate;
};

class CheckingAccount : public BankAccount {
public:
    CheckingAccount(double income, double overdraftLimit);

    /*
    * Charges the specified amount against the overdraft limit.
    * Requires: amount to be a valid double value.
    * Modifies: Updates the balance based on the overdraft charge.
    * Effects: Decreases the account balance by the charged amount.
    */
    void chargeOverdraft(double amount);

    /*
    * Displays everything in the checking account.
    * Requires: nothing
    * Modifies: all of BankAccount as well as the overdraft limit.
    * Effects: Shows the account balance, income, expenditures, savings, and overdraft limit.
    */
    void displaySummary() const override;

    /*
    * Gets the current overdraft limit for the checking account.
    * Requires: nothing
    * Modifies: nothing
    * Effects: Returns the overdraft limit as a double.
    */
    double getOverdraftLimit() const;

    /*
    * Sets the overdraft limit for the checking account.
    * Requires: takes in a double value for the limit.
    * Modifies: updates the overdraft limit based on that value.
    * Effects: changes the overdraft limit for future transactions.
    */
    void setOverdraftLimit(double limit);

private:
    double overdraftLimit;
};

#endif