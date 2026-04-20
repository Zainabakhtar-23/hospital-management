#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

// -------------------- Doctor --------------------
class Doctor {
public:
    int id;
    string name, specialization;

    Doctor(int i=0, string n="", string s="") {
        id = i;
        name = n;
        specialization = s;
    }

    string toString() {
        return to_string(id) + "," + name + "," + specialization;
    }
};

// -------------------- Patient --------------------
class Patient {
public:
    int id;
    string name, condition, priority;

    Patient(int i=0, string n="", string c="", string p="Normal") {
        id = i;
        name = n;
        condition = c;
        priority = p;
    }

    string toString() {
        return to_string(id) + "," + name + "," + condition + "," + priority;
    }
};

// -------------------- File Handling --------------------
void writeFile(string filename, string data) {
    ofstream file(filename, ios::app);
    file << data << endl;
    file.close();
}

void readFile(string filename) {
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }
    file.close();
}

// -------------------- Hospital --------------------
class Hospital {
private:
    queue<Patient> normalQueue;
    queue<Patient> criticalQueue;

public:
    void addPatient(Patient p) {
        if (p.priority == "Critical") {
            criticalQueue.push(p);
        } else {
            normalQueue.push(p);
        }
        writeFile("patients.txt", p.toString());
    }

    void addDoctor(Doctor d) {
        writeFile("doctors.txt", d.toString());
    }

    void assignDoctor(Doctor d) {
        Patient p;

        if (!criticalQueue.empty()) {
            p = criticalQueue.front();
            criticalQueue.pop();
        } else if (!normalQueue.empty()) {
            p = normalQueue.front();
            normalQueue.pop();
        } else {
            cout << "No patients available\n";
            return;
        }

        cout << "Doctor " << d.name << " assigned to Patient " << p.name << endl;
    }
};

// -------------------- Main --------------------
int main() {
    Hospital hospital;
    int choice;

    while (true) {
        cout << "\n1. Add Doctor\n";
        cout << "2. Add Patient\n";
        cout << "3. Assign Doctor\n";
        cout << "4. View Doctors\n";
        cout << "5. View Patients\n";
        cout << "0. Exit\n";

        cin >> choice;

        if (choice == 1) {
            int id;
            string name, spec;

            cout << "Enter Doctor ID: ";
            cin >> id;
            cin.ignore();

            cout << "Enter Name: ";
            getline(cin, name);

            cout << "Enter Specialization: ";
            getline(cin, spec);

            hospital.addDoctor(Doctor(id, name, spec));
        }

        else if (choice == 2) {
            int id;
            string name, cond, priority;

            cout << "Enter Patient ID: ";
            cin >> id;
            cin.ignore();

            cout << "Enter Name: ";
            getline(cin, name);

            cout << "Enter Condition: ";
            getline(cin, cond);

            cout << "Priority (Critical/Normal): ";
            getline(cin, priority);

            hospital.addPatient(Patient(id, name, cond, priority));
        }

        else if (choice == 3) {
            string name;

            cin.ignore();
            cout << "Enter Doctor Name: ";
            getline(cin, name);

            hospital.assignDoctor(Doctor(0, name, ""));
        }

        else if (choice == 4) {
            readFile("doctors.txt");
        }

        else if (choice == 5) {
            readFile("patients.txt");
        }

        else if (choice == 0) {
            break;
        }
    }

    return 0;
}