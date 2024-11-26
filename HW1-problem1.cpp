#include <iostream>
using namespace std;

// Node类模板
template <typename T>
class Node {
public:
    T data;            // 存储数据
    Node* next;        // 指向下一个节点的指针

    // 构造函数
    Node(T val) : data(val), next(nullptr) {}
};

// ListIterator类模板
template <typename T>
class ListIterator {
private:
    Node<T>* current;  // 当前迭代指针
public:
    // 构造函数
    ListIterator(Node<T>* start) : current(start) {}

    // 检查是否还有下一个节点
    bool HasNext() const {
        return current != nullptr;
    }

    // 获取下一个节点的数据
    T& Next() {
        if (!current) throw out_of_range("No more elements in the list");
        T& value = current->data;  // 返回引用
        current = current->next;
        return value;
    }
};

// LinkedList类模板
template <typename T>
class LinkedList {
private:
    Node<T>* head;     // 链表的头指针
    Node<T>* tail;     // 链表的尾指针
public:
    LinkedList() : head(nullptr), tail(nullptr) {}

    // 添加节点到链表尾部
    void Add(T& value) {
        Node<T>* newNode = new Node<T>(value);
        if (tail) {
            tail->next = newNode;
        } else {
            head = newNode;
        }
        tail = newNode;
    }

    void Insert(T& value, int index) {
        if (index < 0) {
            throw out_of_range("Index cannot be negative.");
        }

        Node<T>* newNode = new Node<T>(value);

        // 如果在头部插入
        if (index == 0) {
            newNode->next = head;
            head = newNode;
            if (tail == nullptr) {  // 如果链表原本为空
                tail = newNode;
            }
            return;
        }

        // 遍历找到插入位置的前一个节点
        Node<T>* current = head;
        int currentIndex = 0;

        while (current != nullptr && currentIndex < index - 1) {
            current = current->next;
            currentIndex++;
        }

        // 如果索引超出链表长度，抛出异常
        if (current == nullptr) {
            throw out_of_range("Index exceeds the length of the list.");
        }

        // 插入节点
        newNode->next = current->next;
        current->next = newNode;

        // 如果插入到尾部，需要更新 tail
        if (newNode->next == nullptr) {
            tail = newNode;
        }
    }

    // Get the element at the specified index
    T& Get(int index) {
        if (index < 0) {
            throw out_of_range("Index cannot be negative.");
        }

        Node<T>* current = head;  // 从头节点开始遍历
        int currentIndex = 0;

        while (current != nullptr) {
            if (currentIndex == index) {
                return current->data;  // 找到目标索引，返回数据引用
            }
            current = current->next;
            currentIndex++;
        }

        // 如果索引超出链表长度
        throw out_of_range("Index exceeds the length of the list.");
    }

    // Remove the element at the specified index and return it
    T& Remove(int index) {
        if (index < 0) {
            throw out_of_range("Index cannot be negative.");
        }

        if (head == nullptr) {
            throw out_of_range("Cannot remove from an empty list.");
        }

        Node<T>* current = head;
        Node<T>* previous = nullptr;

        // 如果删除头节点
        if (index == 0) {
            head = head->next;  // 更新头指针
            if (head == nullptr) { // 如果链表变为空
                tail = nullptr;
            }
            T& data = current->data; // 获取被删除节点的数据
            delete current;          // 释放被删除节点
            return data;
        }

        // 遍历找到目标索引的节点及其前一个节点
        int currentIndex = 0;
        while (current != nullptr && currentIndex < index) {
            previous = current;
            current = current->next;
            currentIndex++;
        }

        // 如果索引超出链表长度
        if (current == nullptr) {
            throw out_of_range("Index exceeds the length of the list.");
        }

        // 删除目标节点
        previous->next = current->next;

        // 如果删除的是尾节点
        if (current == tail) {
            tail = previous;  // 更新尾指针
        }

        T& data = current->data; // 获取被删除节点的数据
        delete current;          // 释放被删除节点
        return data;
    }

    int IndexOf(T& value) {
        Node<T>* current = head;  // 从头节点开始遍历
        int index = 0;

        // 遍历链表查找值
        while (current != nullptr) {
            if (current->data == value) {
                return index;  // 找到匹配的值，返回索引
            }
            current = current->next;
            index++;
        }

        // 未找到值
        return -1;
    }

    int Size() {
        int count = 0;                // 计数器初始化为0
        Node<T>* current = head;      // 从头节点开始遍历

        while (current != nullptr) {  // 遍历链表直到末尾
            count++;                  // 每遇到一个节点，计数器加1
            current = current->next;  // 移动到下一个节点
        }

        return count;                 // 返回节点总数
    }

    ListIterator<T> Iterator() {
        return ListIterator<T>(head);
    }

    // 打印链表
    void printList() const {
        Node<T>* current = head;
        while (current) {
            cout << current->data << " -> ";
            current = current->next;
        }
        cout << "nullptr" << endl;
    }

    // 获取链表的头节点
    Node<T>* getHead() const { return head; }

    // 析构函数
    ~LinkedList() {
        Node<T>* current = head;
        while (current) {
            Node<T>* temp = current;
            current = current->next;
            delete temp;
        }
    }
};


int main() {
    // 创建链表对象
    LinkedList<int> list;

    // 测试 Add 函数
    cout << "Adding elements to the list..." << endl;
    int a = 10, b = 20, c = 30, d = 40;
    list.Add(a);
    list.Add(b);
    list.Add(c);
    list.printList();  // 输出: 10 -> 20 -> 30 -> nullptr

    // 测试 Insert 函数
    cout << "Inserting element 40 at index 1..." << endl;
    list.Insert(d, 1);
    list.printList();  // 输出: 10 -> 40 -> 20 -> 30 -> nullptr

    // 测试 Get 函数
    cout << "Getting element at index 2: " << list.Get(2) << endl;  // 输出: 20

    // 测试 Remove 函数
    cout << "Removing element at index 1..." << endl;
    list.Remove(1);
    list.printList();  // 输出: 10 -> 20 -> 30 -> nullptr

    // 测试 IndexOf 函数
    cout << "Finding index of element 20: " << list.IndexOf(b) << endl;  // 输出: 1
    int e = 50;
    cout << "Finding index of non-existing element 50: " << list.IndexOf(e) << endl;  // 输出: -1

    // 测试 Size 函数
    cout << "Size of the list: " << list.Size() << endl;  // 输出: 3

    // 测试 Iterator 函数
    cout << "Iterating through the list: ";
    ListIterator<int> it = list.Iterator();
    while (it.HasNext()) {
        cout << it.Next() << " ";
    }
    cout << endl;  // 输出: 10 20 30

    return 0;
}
