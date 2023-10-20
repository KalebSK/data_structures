#include <iostream>
using namespace std;

class Node {
    private:
        int value = 0;
    public:
        Node* next = nullptr;

        Node(int v) {
            value = v;
        };

        int getValue() {
            return value;
        };

        int& setValue(int i) {
            return value = i;
        };
};

class LinkedList {
    private:
        Node* updateHead(Node* n) {
            n->next = head;
            return head = n;
        };

    public:
        Node* head = nullptr;
        LinkedList(Node* n) {
            head = n;
        };

        Node* insertNode(Node* n, int index) {
            if(index == 0) {
                return updateHead(n);
            };

            int count = 0;
            Node* current = head;
            Node* previous = nullptr;
            while(count < index && current != nullptr) {
                previous = current;
                current = previous->next;
                count++;
            };

            if(count < index) {
                throw "Invalid index";
                return nullptr;
            };

            n->next = previous->next;
            previous->next = n;
            return head;
        };

        Node* removeNode(int index) {
            if(index == 0) {
                Node* next = head->next;
                return head = next;
            }

            int count = 0;
            Node* current = head;
            Node* previous = nullptr;

            while(count < index && current != nullptr) {
                previous = current;
                current = previous->next;
                count++;
            }

            if(current == nullptr) {
                throw "Invalid index";
                return nullptr;
            };

            previous->next = current->next;
            current->next = nullptr;

            return head;
        };
        friend ostream& operator<<(ostream& os, const LinkedList& ll);
};

ostream &operator<<(ostream &os, const LinkedList &ll) {
    int count = 0;
    Node* current = ll.head;
    while(current != nullptr) {
        os << count << ": " << "Node(" << current->getValue() << ") "; 
        current = current->next;
        count++;
    }
    os << endl;
    return os;
}

int main() {
    Node one(1);
    Node two(2);
    Node three(3);

    LinkedList myList(&one);
    cout << "initial list" << endl;
    cout << "Row 1: " << myList;
    myList.insertNode(&two, 1);
    cout << "add node 2 on the end" << endl;
    cout << "Row 2: " << myList;
    myList.insertNode(&three, 2);
    cout << "add node 3 on the end" << endl;
    cout << "Row 3: " << myList;
}


