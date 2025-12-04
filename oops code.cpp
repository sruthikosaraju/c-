#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

/* -----------------------------
   Base Class : Parking
   Demonstrates: Inheritance, Polymorphism, Abstraction
--------------------------------*/
class Parking {
protected:
    float ratePerHour;

public:
    Parking() { 
        ratePerHour = 20.0;           // Default parking charge
    }

    // Virtual function (Polymorphism)
    virtual float calculateFee(float hours) {
        return hours * ratePerHour;
    }
};

/* -------------------------------------------------------
   Derived Class : Vehicle
   Demonstrates: Encapsulation, Constructors, File Handling
--------------------------------------------------------*/
class Vehicle : public Parking {
private:
    string vehicleNumber;
    string entryTime;
    string exitTime;
    float totalHours;
    float fee;

public:

    // Constructor
    Vehicle(string vNo, string en, string ex, float hrs) {
        vehicleNumber = vNo;
        entryTime = en;
        exitTime = ex;
        totalHours = hrs;
        fee = calculateFee(totalHours);        // Polymorphism
    }

    // Function to save record to text file
    void saveToTextFile() {
        ofstream fout("parking_log.txt", ios::app);
        fout << "Vehicle Number : " << vehicleNumber << endl;
        fout << "Entry Time     : " << entryTime << endl;
        fout << "Exit Time      : " << exitTime << endl;
        fout << "Total Hours    : " << totalHours << endl;
        fout << "Parking Fee    : Rs." << fee << endl;
        fout << "-----------------------------------------------" << endl;
        fout.close();
    }

    // Save to CSV
    void saveToCSV() {
        ofstream csv("parking_log.csv", ios::app);
        csv << vehicleNumber << "," << entryTime << "," << exitTime << "," 
            << totalHours << "," << fee << endl;
        csv.close();
    }

    // Display data (Abstraction)
    void showDetails() {
        cout << "\n--------- Parking Receipt ---------\n";
        cout << "Vehicle Number : " << vehicleNumber << endl;
        cout << "Entry Time     : " << entryTime << endl;
        cout << "Exit Time      : " << exitTime << endl;
        cout << "Total Hours    : " << totalHours << endl;
        cout << "Parking Fee    : Rs." << fee << endl;
        cout << "-----------------------------------\n";
    }

    // Destructor
    ~Vehicle() {
        // Optional message for demonstration
        // cout << "Record saved successfully!\n";
    }
};

/* ------------------------------
   MAIN MENU BASED CUI PROGRAM
--------------------------------*/
int main() {
    int choice;
    string vNo, entry, exit;
    float hours;

    while (true) {
        cout << "\n=========================================\n";
        cout << "     VEHICLE PARKING MANAGEMENT SYSTEM   \n";
        cout << "=========================================\n";
        cout << "1. Enter New Vehicle\n";
        cout << "2. View All Records\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            cout << "\nEnter Vehicle Number: ";
            cin >> vNo;

            cout << "Enter Entry Time (HH:MM): ";
            cin >> entry;

            cout << "Enter Exit Time  (HH:MM): ";
            cin >> exit;

            cout << "Enter Total Hours Parked: ";
            cin >> hours;

            // Object created ? OOPS in action
            Vehicle v(vNo, entry, exit, hours);

            v.showDetails();
            v.saveToTextFile();
            v.saveToCSV();

            cout << "\nRecord saved successfully!\n";
        }

        else if (choice == 2) {
            ifstream fin("parking_log.txt");
            if (!fin) {
                cout << "No records found!\n";
            } else {
                cout << "\n=========== All Parking Records ===========\n\n";
                string line;
                while (getline(fin, line)) {
                    cout << line << endl;
                }
                fin.close();
            }
        }

        else if (choice == 3) {
            cout << "\nThank you for using the system!\n";
            break;
        }

        else {
            cout << "Invalid choice! Try again.\n";
        }
    }

    return 0;
}
