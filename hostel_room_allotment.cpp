// Name: Muhammad Sami
#include <iostream>
#include <string>
using namespace std;

struct Student {
    int rollNo;
    string name;
    int roomNo;
    Student* next;
} *Start = NULL;


struct StackNode {
    Student* data;
    StackNode* next;
} *Top = NULL;


struct QueueNode {
    Student* data;
    QueueNode* next;
} *front = NULL, *rear = NULL;


void push(Student* student) {
    StackNode* temp = new StackNode();
    temp->data = student;
    temp->next = Top;
    Top = temp;
    cout << "Undo stack: Added student with Roll No " << student->rollNo << endl;
}

Student* pop() {
    if (Top == NULL) {
        cout << "Undo stack is empty.\n";
        return NULL;
    }
    StackNode* temp = Top;
    Top = Top->next;
    Student* student = temp->data;
    delete temp;
    return student;
}


void enqueue(Student* student) {
    QueueNode* temp = new QueueNode();
    temp->data = student;
    temp->next = NULL;
    if (rear == NULL) {
        front = rear = temp;
    } else {
        rear->next = temp;
        rear = temp;
    }
    cout << "Waiting list: Added student with Roll No " << student->rollNo << endl;
}

Student* dequeue() {
    if (front == NULL) {
        cout << "Waiting list is empty.\n";
        return NULL;
    }
    QueueNode* temp = front;
    front = front->next;
    if (front == NULL) {
        rear = NULL;
    }
    Student* student = temp->data;
    delete temp;
    return student;
}

bool isQueueEmpty() {
    return front == NULL;
}


void addStudent() {
    if (!isQueueEmpty()) {
        cout << "Assigning a room to a student from the waiting list.\n";
        Student* temp = dequeue();

        cout << "Enter Room Number for " << temp->name << ": ";
        cin >> temp->roomNo;

        temp->next = NULL;

        if (Start == NULL) {
            Start = temp;
        } else {
            Student* p = Start;
            while (p->next != NULL) {
                p = p->next;
            }
            p->next = temp;
        }
        cout << "Student from waiting list added successfully!\n";
    } else {
        Student* temp = new Student();
        cout << "Enter Roll Number: ";
        cin >> temp->rollNo;
        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, temp->name);
        cout << "Enter Room Number: ";
        cin >> temp->roomNo;
        temp->next = NULL;

        if (Start == NULL) {
            Start = temp;
        } else {
            Student* p = Start;
            while (p->next != NULL) {
                p = p->next;
            }
            p->next = temp;
        }
        cout << "Student added successfully!\n";
    }
}


void displayStudents() {
    if (Start == NULL) {
        cout << "No students in the hostel.\n";
        return;
    }
    Student* p = Start;
    while (p != NULL) {
        cout << "Roll No: " << p->rollNo << ", Name: " << p->name << ", Room No: " << p->roomNo << endl;
        p = p->next;
    }
}


void searchStudent(int rollNo) {
    Student* p = Start;
    while (p != NULL) {
        if (p->rollNo == rollNo) {
            cout << "Student Found!\n";
            cout << "Roll No: " << p->rollNo << ", Name: " << p->name << ", Room No: " << p->roomNo << endl;
            return;
        }
        p = p->next;
    }
    cout << "Student with Roll No " << rollNo << " not found.\n";
}


void deleteStudent(int rollNo) {
    Student* p = Start;
    Student* prev = NULL;

    while (p != NULL && p->rollNo != rollNo) {
        prev = p;
        p = p->next;
    }

    if (p == NULL) {
        cout << "Student with Roll No " << rollNo << " not found.\n";
        return;
    }

    if (prev == NULL) {
        Start = p->next;  
    } else {
        prev->next = p->next;  
    }

    push(p);  
    cout << "Student removed successfully! You can undo this action.\n";

    
    if (!isQueueEmpty()) {
        Student* waitingStudent = dequeue();
        waitingStudent->roomNo = p->roomNo;  
        waitingStudent->next = NULL;

        if (Start == NULL) {
            Start = waitingStudent;
        } else {
            Student* last = Start;
            while (last->next != NULL) {
                last = last->next;
            }
            last->next = waitingStudent;
        }
        cout << "Room " << p->roomNo << " has been assigned to " << waitingStudent->name << " from the waiting list.\n";
    }
}


void undoLastDelete() {
    Student* temp = pop();
    if (temp == NULL) {
        cout << "No delete operations to undo.\n";
        return;
    }

    temp->next = NULL;
    if (Start == NULL) {
        Start = temp;
    } else {
        Student* p = Start;
        while (p->next != NULL) {
            p = p->next;
        }
        p->next = temp;
    }
    cout << "Undo successful! Student restored.\n";
}


void addToWaitingList() {
    Student* temp = new Student();
    cout << "Enter Roll Number: ";
    cin >> temp->rollNo;
    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, temp->name);

    temp->next = NULL;
    enqueue(temp);
}


void displayWaitingList() {
    if (isQueueEmpty()) {
        cout << "No students in the waiting list.\n";
        return;
    }
    QueueNode* temp = front;
    cout << "Waiting List:\n";
    while (temp != NULL) {
        Student* student = temp->data;
        cout << "Roll No: " << student->rollNo << ", Name: " << student->name << endl;
        temp = temp->next;
    }
}

void countStudents() {
    int count = 0;
    Student* p = Start;
    while (p != NULL) {
        count++;
        p = p->next;
    }
    cout << "Total students in the hostel: " << count << endl;
}

int main() {
    int choice, rollNo;
    cout<<"-----------------COMSATS BOYS HOSTEL :-------------------\n";
    cout<<"-----Room will be alloted on first come first get base----";
    
    while (true) {
        cout << "\n1. Add Student\n";
        cout << "2. Add Student to Waiting List\n";
        cout << "3. Display All Students\n";
        cout << "4. Search Student by Roll No\n";
        cout << "5. Delete Student by Roll No\n";
        cout << "6. Undo Last Delete\n";
        cout << "7. Display Waiting List\n";
        cout << "8. Count Total Students\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                addToWaitingList();
                break;
            case 3:
                displayStudents();
                break;
            case 4:
                cout << "Enter Roll Number to Search: ";
                cin >> rollNo;
                searchStudent(rollNo);
                break;
            case 5:
                cout << "Enter Roll Number to Delete: ";
                cin >> rollNo;
                deleteStudent(rollNo);
                break;
            case 6:
                undoLastDelete();
                break;
            case 7:
                displayWaitingList();
                break;
            case 8:
                countStudents();
                break;
            case 9:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
    return 0;
}

