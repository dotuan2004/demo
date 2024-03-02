#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

struct Staff {
    string Id;
    string Name;
    float Salary;
    int WorkYear;
};

struct Note {
    Staff data;
    Note* next;
};

struct List {
    Note* pHead;
    Note* pTail;
    int staffCount;
};

Note* CreateNote(Staff st) {
    Note* p = new Note;
    if (p == NULL) {
        cout << "Unable to allocate memory";
        return NULL;
    }
    p->data = st;
    p->next = NULL;
    return p;
}

void CreateList(List* lt) {
    lt->pHead = NULL;
    lt->pTail = NULL;
    lt->staffCount = 0;  // Initialize the number of staff to 0
}

bool IsEmpty(List lt) {
    return lt.pHead == NULL;
}

void InsertTop(List* lt, Staff st) {
    Note* p = CreateNote(st);
    if (p == NULL) {
        cout << "Failed to create note. Memory allocation failed.\n";
        return;
    }
    if (IsEmpty(*lt)) {
        lt->pHead = lt->pTail = p;
    } else {
        p->next = lt->pHead;
        lt->pHead = p;
    }
    lt->staffCount++; 
}

void DeleteHead(List* lt) {
    if (lt->pHead == NULL) {
        cout << "List is empty. Nothing to delete.\n";
        return;
    }
    Note* p = lt->pHead;
    lt->pHead = p->next;
    delete p;
    lt->staffCount--;
    if (lt->pHead == NULL) {
        lt->pTail = NULL;
    }
}

void InsertEnd(List* lt, Staff st) {
    Note* p = CreateNote(st);
    if (p == NULL) {
        cout << "Failed to create note. Memory allocation failed.\n";
        return;
    }
    if (IsEmpty(*lt)) {
        lt->pHead = lt->pTail = p;
    } else {
        lt->pTail->next = p;
        lt->pTail = p;
    }
    lt->staffCount++;
}

void DeleteTail(List* lt) {
    if (lt->pHead == NULL) {
        cout << "List is empty. Nothing to delete\n";
        return;
    }
    if (lt->pHead == lt->pTail) { // Only one element in the list
        DeleteHead(lt);
        return;
    }
    Note* p = lt->pHead;
    while (p->next != lt->pTail) {
        p = p->next;
    }
    delete lt->pTail;
    lt->pTail = p;
    p->next = NULL;
    lt->staffCount--;
}

void InsertMid(List *lt, Staff st) {
    int number;
    cout << "Enter the staff number to insert: ";
    cin >> number;
    if (number <= 0 || IsEmpty(*lt)) {
        InsertTop(lt, st);
    } else if (number >= lt->staffCount) {
        cout << "\nThe input number is greater than the number of existing staffs, the entered staffs will be moved to the bottom of the list\n";
        InsertEnd(lt, st);
    } else {
        Note* p = lt->pHead;
        for (int i = 1; i < number && p != NULL; i++) {
            p = p->next;
        }
        if (p == NULL) {
            cout << "Invalid position.\n";
            return;
        }
        Note* q = CreateNote(st);
        if (q == NULL) {
            cout << "Failed to create note. Memory allocation failed.\n";
            return;
        }
        q->next = p->next;
        p->next = q;
        lt->staffCount++;
    }
}

void DeleteAfter(List* lt) {
    int position;
    cout << "Enter the position of the node after which you want to delete: ";
    cin >> position;
    if (position <= 0 || position >= lt->staffCount) {
        cout << "Invalid position.\n";
        return;
    }
    Note* q = lt->pHead;
    for (int i = 1; i < position && q != NULL; ++i) {
        q = q->next;
    }   
    if (q != NULL && q->next != NULL) {
        Note* p = q->next;
        q->next = p->next;
        if (p == lt->pTail) {
            lt->pTail = q;
        }
        delete p;
        lt->staffCount--;
    }
}

void DeleteStaff(List* lt) {
    Note* p = lt->pHead;
    Note* q = NULL;
    while (p != NULL && p->data.WorkYear >= 4) {
        q = p;
        p = p->next;
    }
    if (p == NULL) {
        cout << "No staff with work year >= 4 found.\n";
        return;
    }
    if (q == NULL) {
        DeleteHead(lt);
    } else if (p == lt->pTail) {
        DeleteTail(lt);
    } else {
        q->next = p->next;
        delete p;
        lt->staffCount--;
    }
    cout << "Staff with work year >= 4 has been deleted.\n";
}

void ShowStaff(List lt) {
    if (lt.pHead == NULL) {
        cout << "List is empty.\n";
        return;
    }
    Note* p = lt.pHead;
    int staffNumber = 1;
    cout << "Staff List:\n";
    cout << left << setw(20) << "Numerical order" << setw(15) << "ID" << setw(30) << "Name" << setw(25) << "Coefficients Salary" << setw(10) << "Work Year" << endl;
    while (p != NULL) {
        cout << left << setw(20) << staffNumber << setw(15) << p->data.Id << setw(30) << p->data.Name << setw(25) << p->data.Salary << setw(10) << p->data.WorkYear << endl;
        p = p->next;
        staffNumber++;
    }
    cout << "Total staff: " << lt.staffCount << endl; 
}

void EnterStaffList(List* lt) {
    char opinion;
    do {
        Staff st;
        cout << "Enter information for a new staff:\n";
        cout << "ID: ";
        getline(cin, st.Id);
        cout << "Name: ";
        getline(cin, st.Name);
        cout << "Coefficients salary: ";
        cin >> st.Salary;
        cout << "Work Year: ";
        cin >> st.WorkYear;
        cin.ignore();
        InsertEnd(lt, st);
        cout << "Do you want to enter another staff? (Y/N): ";
        cin >> opinion;
        cin.ignore();
    } while (opinion == 'Y' || opinion == 'y');
}

void FreeSt(List* lt) {
    Note* p = lt->pHead;
    while (p != NULL) {
        Note* temp = p;
        p = p->next;
        delete temp;
    }
    lt->pHead = lt->pTail = NULL;
}

int main() {
    List lt;
    CreateList(&lt);
    
    int choice;
    char opinion;

    do {
        cout << "\n===== Employee Management System =====\n";
        cout << "1. Add new employee\n";
        cout << "2. Display list of employees\n";
        cout << "3. Delete employee with work year >= 4\n";
        cout << "4. Insert new employee with ID\n";
        cout << "5. Delete employee after position\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                EnterStaffList(&lt);
                break;
            case 2:
                ShowStaff(lt);
                break;
            case 3:
                DeleteStaff(&lt);
                break;
            case 4:{
                Staff newEmployee;
                cout << "Enter information for a new staff:\n";
                cout << "ID: ";
                getline(cin, newEmployee.Id);
                cout << "Name: ";
                getline(cin, newEmployee.Name);
                cout << "Coefficients salary: ";
                cin >> newEmployee.Salary;
                cout << "Work Year: ";
                cin >> newEmployee.WorkYear;
                cin.ignore();
                InsertMid(&lt, newEmployee);
                break;
            }
            case 5:
                DeleteAfter(&lt);
                break;
            case 6:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }

        cout << "Do you want to continue? (Y/N): ";
        cin >> opinion;
        cin.ignore();

    } while (opinion == 'Y' || opinion == 'y');

    FreeSt(&lt); // Free memory before exiting the program
    return 0;
}
