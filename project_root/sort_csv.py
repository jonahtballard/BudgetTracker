import csv
import sys
from datetime import datetime

# function to sort csv by date
def sort_csv_by_date(filename):
    data = []

    # read csv file
    with open(filename, 'r') as csvfile:
        reader = csv.reader(csvfile)
        entry = {}

        for row in reader:
            if row and row[0].startswith("Date"):
                if entry:
                    data.append(entry)
                entry = {"Date": row[1]}
            elif row and row[0] == "Income":
                entry["Income"] = float(row[1])
            elif row and row[0] == "Total Expenditures":
                entry["Total Expenditures"] = float(row[1])
            elif row and row[0] == "Savings":
                entry["Savings"] = float(row[1])
            elif row and row[0] == "Food":
                entry["Food"] = float(row[1])
            elif row and row[0] == "Utilities":
                entry["Utilities"] = float(row[1])
            elif row and row[0] == "Entertainment":
                entry["Entertainment"] = float(row[1])
            elif row and row[0] == "Transportation":
                entry["Transportation"] = float(row[1])
            elif row and row[0] == "Other":
                entry["Other"] = float(row[1])
            elif row and row[0] == "Expenditure Percentage":
                entry["Expenditure Percentage"] = row[1]
            elif row and row[0] == "Interest Rate":
                entry["Interest Rate"] = float(row[1])

        if entry:  # make sure to add last entry
            data.append(entry)

    print(data)
    sorted_data = sorted(data, key=lambda x: datetime.strptime(x['Date'], "%m/%d/%Y"))

    # put the sorted data back to
    with open(filename, 'w', newline='') as csvfile:
        writer = csv.writer(csvfile)
        for entry in sorted_data:
            writer.writerow([])
            writer.writerow(["Date", entry.get("Date")])
            writer.writerow(["Category", "Expenditure ($)"])
            writer.writerow(["Food", entry.get("Food")])
            writer.writerow(["Utilities", entry.get("Utilities")])
            writer.writerow(["Entertainment", entry.get("Entertainment")])
            writer.writerow(["Transportation", entry.get("Transportation")])
            writer.writerow(["Other", entry.get("Other")])
            writer.writerow(["Income", entry.get("Income")])
            writer.writerow(["Total Expenditures", entry.get("Total Expenditures")])
            writer.writerow(["Savings", entry.get("Savings")])
            writer.writerow(["Expenditure Percentage", entry.get("Expenditure Percentage")])
            writer.writerow(["Interest Rate", entry.get("Interest Rate")])

#main function to start the sorting
if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python3 sort_csv.py <csv_filename>")
        sys.exit(1)

    csv_file = sys.argv[1] + ".csv"
    sort_csv_by_date(csv_file)
    print(f"CSV file {csv_file} sorted by date.")