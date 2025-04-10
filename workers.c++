#include <iostream>
#include <fstream>
#include <windows.h>
#include <conio.h>
#include <iomanip>
#include <limits>
#include <cmath>
#include <sstream>

using namespace std;

// Move the Worker struct definition here, before function declarations
struct Worker {
    string name;
    string id;
    string address;
    int age;
    char gender;
    double wage;
    double rate;
    double grossSalary;
    double netSalary;
    int hours;

    Worker() {
        grossSalary = 0;
        netSalary = 0;
        hours = 0;
    }

    void addWorker(string generatedId) {
        HANDLE consoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(consoleColor, 8);
        id = generatedId;
        cout << "Enter ID: " << id << endl;
        cin.ignore();
        cout << "Enter name: ";
        getline(cin, name);
        cout << "Enter age: ";
        cin >> age;
        cout << "Enter gender (M/F): ";
        cin >> gender;
        cout << "Enter address: ";
        cin.ignore();
        getline(cin, address);
        cout << "Enter wage ($): ";
        cin >> wage;
        cout << "Enter hours worked in a month: ";
        cin >> hours;
        calculateSalary();
    }

    void calculateSalary() {
        grossSalary = wage * hours;
        if (grossSalary > 1000) {
            if (gender == 'M' || gender == 'm') {
                rate = 15;
            } else if (gender == 'F' || gender == 'f') {
                rate = 10;
            }
        } else {
            if (gender == 'M' || gender == 'm') {
                rate = 10;
            } else if (gender == 'F' || gender == 'f') {
                rate = 5;
            }
        }
        netSalary = grossSalary - (grossSalary * (rate / 100));
    }

    void displayWorker() {
        HANDLE consoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(consoleColor, 7);
        cout << "ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Gender: " << gender << endl;
        cout << "Address: " << address << endl;
        cout << "Wage: $" << wage << endl;
        cout << "Tax Rate: " << rate << "% = $" << grossSalary * (rate / 100) << endl;
        cout << "Hours Worked: " << hours << " hours/month" << endl;
        cout << "Gross Salary: $" << fixed << setprecision(2) << grossSalary << endl;
        cout << "Net Salary: $" << fixed << setprecision(2) << netSalary << endl;
    }

    void updateWorker() {
        HANDLE consoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(consoleColor, 6);
        cout << "Enter new name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter new age: ";
        cin >> age;
        cout << "Enter new gender (M/F): ";
        cin >> gender;
        cout << "Enter new address: ";
        cin.ignore();
        getline(cin, address);
        cout << "Enter new wage ($): ";
        cin >> wage;
        cout << "Enter new hours worked in a month: ";
        cin >> hours;
        calculateSalary();
    }
};

// Function declarations can now use Worker without issues
void logo();
int mainMenu();
void pressEnterToContinue();
void systemProcessing();
bool noWorkersFound(int);
string generateWorkerId(int);
int sortWorkerMenu(); 
void sortBySalary(Worker workers[], int count);
void sortByWage(Worker workers[], int count);
void sortByAge(Worker workers[], int count);
void sortByHours(Worker workers[], int count);

// Rest of the code remains the same
void initializeWorkers(Worker workers[]) {
    workers[0].name = "Ally";
    workers[0].id = "W001";
    workers[0].address = "789 Pine Rd";
    workers[0].age = 23;
    workers[0].gender = 'F';
    workers[0].wage = 22.5;
    workers[0].hours = 150;
    workers[0].calculateSalary();

    workers[1].name = "Bob";
    workers[1].id = "W002";
    workers[1].address = "456 Oak Ave";
    workers[1].age = 28;
    workers[1].gender = 'M';
    workers[1].wage = 18.0;
    workers[1].hours = 140;
    workers[1].calculateSalary();
}

void deleteWorker(Worker workers[], int count, string id) {
    HANDLE consoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(consoleColor, 9);
    for (int i = 0; i < count; i++) {
        if (workers[i].id == id) {
            for (int j = i; j < count - 1; j++) {
                workers[j] = workers[j + 1];
            }
            count--;
            cout << "Worker with ID " << id << " deleted." << endl;
            return;
        }
    }
    cout << "Worker not found." << endl;
}

void searchWorker(Worker workers[], int count, string searchId) {
    HANDLE consoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(consoleColor, 3);
    for (int i = 0; i < count; i++) {
        if (workers[i].id == searchId) {
            workers[i].displayWorker();
            return;
        }
    }
    cout << "Worker " << searchId << " not found." << endl;
}

int main() {
    system("cls");
    systemProcessing();
    return 0;
}

void logo() {
    HANDLE consoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
    fstream file("logo1.txt");
    string line;
    while (getline(file, line)) {
        SetConsoleTextAttribute(consoleColor, 5);
        cout << right << line << endl;
        Sleep(120);
    }
}

int mainMenu() {
    logo();
    int choice;
    HANDLE consoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(consoleColor, 4);
    cout << endl;
    cout << "============[ Worker Menu ]============" << endl;
    cout << "[1]. Add Worker" << endl;
    cout << "[2]. View Worker" << endl;
    cout << "[3]. Update Worker" << endl;
    cout << "[4]. Delete Worker" << endl;
    cout << "[5]. Search Worker" << endl;
    cout << "[0]. Exit" << endl;
    cout << "==========================================" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    cin.clear();
    return choice;
}

int sortWorkerMenu() {
    int choice;
    HANDLE consoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(consoleColor, 4);
    cout << endl;
    cout << "============[ Display Worker Ordering ]============" << endl;
    cout << "[1]. Display original Order" << endl;
    cout << "[2]. Show Ascending Order by Wage" << endl;
    cout << "[3]. Show Ascending Order by Age" << endl;
    cout << "[4]. Show Ascending Order by Hours" << endl;
    cout << "[5]. Show Ascending Order by Salary" << endl;
    cout << "[0]. Exit" << endl;
    cout << "==========================================" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    cin.clear();
    return choice;
}

void pressEnterToContinue() {
    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get();
}

string generateWorkerId(int count) {
    stringstream ss;
    ss << "W" << setw(3) << setfill('0') << (count + 1);
    return ss.str();
}

void sortBySalary(Worker workers[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (workers[j].netSalary > workers[j + 1].netSalary) {
                Worker temp = workers[j];
                workers[j] = workers[j + 1];
                workers[j + 1] = temp;
            }
        }
    }
}

void sortByWage(Worker workers[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (workers[j].wage > workers[j + 1].wage) {
                Worker temp = workers[j];
                workers[j] = workers[j + 1];
                workers[j + 1] = temp;
            }
        }
    }
}

void sortByAge(Worker workers[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (workers[j].age > workers[j + 1].age) {
                Worker temp = workers[j];
                workers[j] = workers[j + 1];
                workers[j + 1] = temp;
            }
        }
    }
}

void sortByHours(Worker workers[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (workers[j].hours > workers[j + 1].hours) {
                Worker temp = workers[j];
                workers[j] = workers[j + 1];
                workers[j + 1] = temp;
            }
        }
    }
}

void systemProcessing() {
    int choice;
    int n = 5;
    Worker workers[5];
    initializeWorkers(workers);
    int count = 2;

    do {  
        system("cls");
        choice = mainMenu();
        system("cls");
        switch (choice) {
            case 1:
                cout << "==========[Enter Worker Information]===========" << endl;
                if (count < n) {
                    workers[count].addWorker(generateWorkerId(count));
                    count++;
                } else {
                    cout << "Worker array is full!" << endl;
                }
                break;
            case 2:
                if (noWorkersFound(count)) break;
                cout << "==========[View Worker Information]===========" << endl;
                {
                    int sortChoice;
                    bool exitSort = false;
                    while (!exitSort) {
                        system("cls");
                        sortChoice = sortWorkerMenu();
                        switch (sortChoice) {
                            case 5:
                                sortBySalary(workers, count);
                                for (int i = 0; i < count; i++) {
                                    workers[i].displayWorker();
                                    cout << "----------------------------------------" << endl;
                                }
                                pressEnterToContinue();
                                break;
                            case 2:
                                sortByWage(workers, count);
                                for (int i = 0; i < count; i++) {
                                    workers[i].displayWorker();
                                    cout << "----------------------------------------" << endl;
                                }
                                pressEnterToContinue();
                                break;
                            case 3:
                                sortByAge(workers, count);
                                for (int i = 0; i < count; i++) {
                                    workers[i].displayWorker();
                                    cout << "----------------------------------------" << endl;
                                }
                                pressEnterToContinue();
                                break;
                            case 4:
                                sortByHours(workers, count);
                                for (int i = 0; i < count; i++) {
                                    workers[i].displayWorker();
                                    cout << "----------------------------------------" << endl;
                                }
                                pressEnterToContinue();
                                break;
                            case 1:
                            for (int i = 0; i < count; i++) {
                                workers[i].displayWorker();
                                cout << "----------------------------------------" << endl;
                            }
                            pressEnterToContinue();
                            break;
                            case 0:
                                exitSort = true;
                                break;
                            default:
                                cout << "Invalid choice! Try again." << endl;
                                pressEnterToContinue();
                        }
                    }
                }
                break;
            case 3:
                if (noWorkersFound(count)) break;
                cout << "==========[Update Worker Information]===========" << endl;
                {
                    string id;
                    cout << "Enter Worker ID to update: ";
                    cin >> id;
                    bool found = false;
                    for (int i = 0; i < count; i++) {
                        if (workers[i].id == id) {
                            workers[i].updateWorker();
                            found = true;
                            break;
                        }
                    }
                    if (!found) {
                        cout << "Worker not found!" << endl;
                    }
                }
                break;
            case 4:
                if (noWorkersFound(count)) break;
                cout << "==========[Delete Worker]===========" << endl;
                {
                    string id;
                    cout << "Enter Worker ID to delete: ";
                    cin >> id;
                    deleteWorker(workers, count, id);
                }
                break;
            case 5:
                if (noWorkersFound(count)) break;
                cout << "==========[Search Worker]===========" << endl;
                {
                    string id;
                    cout << "Enter Worker ID to search: ";
                    cin >> id;
                    cout << "----------------------------------------" << endl;
                    searchWorker(workers, count, id);
                }
                break;
            case 0:
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
        if (choice != 2) { 
            pressEnterToContinue();
        }
    } while (choice != 0);
}

bool noWorkersFound(int count) {
    if (count == 0) {
        cout << "No workers found!" << endl;
        return true;
    }
    return false;
}