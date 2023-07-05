#include <iostream>

class Node {
public:
    std::string dataval;
    Node* nextval;

    Node(std::string data) {
        dataval = data;
        nextval = nullptr;
    }
};

class SLinkedList {
public:
    Node* headval;

    SLinkedList() {
        headval = nullptr;
    }

    void listprint() {
        Node* printval = headval;
        while (printval != nullptr) {
            std::cout << "Value: " << printval->dataval << std::endl;
            printval = printval->nextval;
        }
    }
};

int main() {
    SLinkedList list;
    list.headval = new Node("Monday");
    Node* e2 = new Node("Tuesday");
    Node* e3 = new Node("Wednesday");

    list.headval->nextval = e2;
    e2->nextval = e3;

    list.listprint();

    // Clean up memory
    delete e3;
    delete e2;
    delete list.headval;

    return 0;
}
