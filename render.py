import csv
import matplotlib.pyplot as plt
import sys
from datetime import datetime
from itertools import accumulate


# Check if the CSV file is provided as an argument
if len(sys.argv) < 2:
    sys.exit(1)

# Read CSV file from the command-line argument
csv_file = sys.argv[1]



# Function to read the CSV file and process data
def read_csv(filename):
    dates = []
    income = []
    expenditures = []
    savings = []

    with open(filename, newline='') as csvfile:
        reader = csv.reader(csvfile)
        next(reader)
        date, inc, exp, sav = None, 0, 0, 0
        for row in reader:
            if row and row[0].startswith("Date"):
                if date:
                    dates.append(date)
                    income.append(inc)
                    expenditures.append(exp)
                    savings.append(sav)
                date = datetime.strptime(row[1], "%m/%d/%Y")
                inc, exp, sav = 0, 0, 0
            elif row and row[0] == "Income":
                inc = float(row[1])
            elif row and row[0] == "Total Expenditures":
                exp = float(row[1])
            elif row and row[0] == "Savings":
                sav = float(row[1])
        if date:
            dates.append(date)
            income.append(inc)
            expenditures.append(exp)
            savings.append(sav)

    return dates, income, expenditures, savings

# Function to plot cumulative data
def plot_cumulative(dates, income, expenditures, savings):
    cumulative_income = list(accumulate(income))
    cumulative_expenditures = list(accumulate(expenditures))
    cumulative_savings = list(accumulate(savings))

    plt.figure(figsize=(10, 6))

    plt.plot(dates, cumulative_income, label='Cumulative Income', color='green', marker='o')
    plt.plot(dates, cumulative_expenditures, label='Cumulative Expenditures', color='red', marker='o')
    plt.plot(dates, cumulative_savings, label='Cumulative Savings', color='blue', marker='o')

    plt.title('Cumulative Financial Data Over Time')
    plt.xlabel('Date')
    plt.ylabel('Amount ($)')
    plt.legend()
    plt.grid(True)
    plt.xticks(rotation=45)
    plt.tight_layout()

    plt.show()

if __name__ == "__main__":
    csv_file = sys.argv[1] + ".csv"
    dates, income, expenditures, savings = read_csv(csv_file)
    print(expenditures)
    print(income)
    print(savings)
    plot_cumulative(dates, income, expenditures, savings)