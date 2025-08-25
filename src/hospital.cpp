#include <iostream>
#include <queue>
#include <string>
using namespace std;

struct EmergencyPatient {
    string name;
    int severity;
    bool operator<(const EmergencyPatient& p) const {
        return severity < p.severity; // max-heap
    }
};

priority_queue<EmergencyPatient> emergencyQueue;
queue<string> regularQueue;

void addEmergency() {
    EmergencyPatient p;
    cout << "Enter patient name: ";
    cin >> p.name;
    cout << "Enter severity (1-10): ";
    cin >> p.severity;
    emergencyQueue.push(p);
}

void addRegular() {
    string name;
    cout << "Enter patient name: ";
    cin >> name;
    regularQueue.push(name);
}

void processPatient() {
    if (!emergencyQueue.empty()) {
        EmergencyPatient p = emergencyQueue.top(); emergencyQueue.pop();
        cout << "Processing Emergency Patient: " << p.name << " (Severity: " << p.severity << ")\n";
    } else if (!regularQueue.empty()) {
        string name = regularQueue.front(); regularQueue.pop();
        cout << "Processing Regular Patient: " << name << endl;
    } else {
        cout << "No patients in queue.\n";
    }
}

void estimateWaitTime() {
    int time = emergencyQueue.size() * 5 + regularQueue.size() * 10;
    cout << "Estimated wait time: " << time << " minutes\n";
}

int main() {
    int choice;
    do {
        cout << "\n1. Add Emergency Patient\n2. Add Regular Patient\n3. Process Patient\n4. Estimate Wait Time\n5. Exit\nChoice: ";
        cin >> choice;
        if (choice == 1) addEmergency();
        else if (choice == 2) addRegular();
        else if (choice == 3) processPatient();
        else if (choice == 4) estimateWaitTime();
    } while (choice != 5);
    return 0;
}
