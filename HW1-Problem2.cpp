#include <iostream>
#include <stdexcept> 

// Node class for a doubly linked list
template <typename T>
class DNode {
public:
    T data;         // Node data
    DNode* next;    // Pointer to next node
    DNode* prev;    // Pointer to previous node

    DNode(T value) : data(value), next(nullptr), prev(nullptr) {}
};

// Doubly linked list class
template <typename T>
class DoublyLinkedList {
private:
    DNode<T>* head; // First node in the list
    DNode<T>* tail; // Last node in the list
    int size;       // Number of nodes

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    ~DoublyLinkedList() {
        Clear(); // Free all nodes
    }

    // Add an element to the end
    void Add(const T& value) {
        DNode<T>* newNode = new DNode<T>(value);
        if (!head) { 
            head = tail = newNode; // If empty, set head and tail to new node
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode; // Update tail
        }
        size++;
    }

    // Get the element at a specific index
    T Get(int index) const {
        if (index < 0 || index >= size) throw std::out_of_range("Index out of bounds");
        DNode<T>* current = head;
        for (int i = 0; i < index; ++i) current = current->next; // Traverse to index
        return current->data;
    }

    // Remove an element by index
    void Remove(int index) {
        if (index < 0 || index >= size) throw std::out_of_range("Index out of bounds");

        DNode<T>* toDelete = nullptr;
        if (index == 0) { 
            toDelete = head;
            head = head->next; // Update head
            if (head) head->prev = nullptr;
            if (!head) tail = nullptr; // Empty list case
        } else if (index == size - 1) {
            toDelete = tail;
            tail = tail->prev; // Update tail
            tail->next = nullptr;
        } else { 
            toDelete = head;
            for (int i = 0; i < index; ++i) toDelete = toDelete->next; // Traverse to node
            toDelete->prev->next = toDelete->next;
            toDelete->next->prev = toDelete->prev;
        }
        delete toDelete;
        size--;
    }

    // Clear the entire list
    void Clear() {
        while (head) {
            DNode<T>* temp = head;
            head = head->next;
            delete temp;
        }
        head = tail = nullptr;
        size = 0;
    }

    // Print all elements
    void Print() const {
        DNode<T>* current = head;
        while (current) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    // Get the size of the list
    int Size() const {
        return size;
    }
};

// Test cases
int main() {
    DoublyLinkedList<int> list;

    std::cout << "Adding elements 10, 20, 30...\n";
    list.Add(10);
    list.Add(20);
    list.Add(30);
    list.Print();

    std::cout << "Element at index 1: " << list.Get(1) << std::endl;
    std::cout << "Element at index 0: " << list.Get(0) << std::endl;
    std::cout << "Element at index 2: " << list.Get(2) << std::endl;

    std::cout << "Removing element at index 1...\n";
    list.Remove(1);
    list.Print();

    std::cout << "Removing element at index 0...\n";
    list.Remove(0);
    list.Print();

    std::cout << "Removing element at index 0...\n";
    list.Remove(0);
    list.Print();

    std::cout << "Adding elements 40, 50...\n";
    list.Add(40);
    list.Add(50);
    list.Print();

    std::cout << "Removing tail...\n";
    list.Remove(1);
    list.Print();

    std::cout << "Removing head...\n";
    list.Remove(0);
    list.Print();

    std::cout << "List size: " << list.Size() << std::endl;

    return 0;
}

