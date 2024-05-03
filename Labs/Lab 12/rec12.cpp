// Doubly linked list
//  Test code

#include <cstdlib>
#include <iostream>
using namespace std;

class List {
    friend ostream& operator<<(ostream& os, const List& list) {
        Node* curr = list.header->next;
        while (curr != list.trailer) {
            os << curr->data << " ";
            curr = curr->next;
        }
        return os;
    }
private:
    struct Node;
public:
    List() : header(new Node{0, nullptr, nullptr}), 
    trailer(new Node{0, header, nullptr}), num_items(0) {
        header->next = trailer;
    }

    // Add node to end
    void push_back(int data) {
        // Add before trailer
        Node* new_node = new Node{data, trailer->prev, trailer};
        (new_node->prev)->next = new_node;
        trailer->prev = new_node;
        num_items++;
    }

    // Delete node at end
    void pop_back() {
        if (num_items == 0) return;
        Node* new_last = trailer->prev->prev;
        new_last->next = trailer;
        delete trailer->prev;
        trailer->prev = new_last;
        num_items--;
    }

    // Return first data item
    int front() const { return header->next->data; }

    int& front() { return header->next->data; }

    // Return last data item
    int back() const { return trailer->prev->data; }

    int& back() { return trailer->prev->data; }

    // Return size
    size_t size() const { return num_items; }

    // Add node to front
    void push_front(int data) {
        // Add after header
        Node* new_node = new Node{data, header, header->next};
        (new_node->next)->prev = new_node;
        header->next = new_node;
        num_items++;
    }

    // Delete node at front
    void pop_front() {
        if (num_items == 0) return;
        Node* new_last = header->next->next;
        new_last->prev = header;
        delete header->next;
        header->next = new_last;
        num_items--;
    }

    void clear() {
        Node* curr = header->next;
        while (curr != trailer) {
            Node* curr_next = curr->next;
            delete curr;
            curr = curr_next;
        }
        header->next = trailer;
        trailer->prev = header;
        num_items = 0;
    }

    // Access item at index
    int operator[](size_t i) const {
        Node* curr = header->next;
        size_t j = 0;
        while (curr != trailer) {
            if (j == i) return curr->data;
            j++;
            curr = curr->next;
        }
        return trailer->data;
    }
    int& operator[](size_t i) {
        Node* curr = header->next;
        size_t j = 0;
        while (curr != trailer) {
            if (j == i) return curr->data;
            j++;
            curr = curr->next;
        }
        return trailer->data;
    }

    class Iterator {
        friend List;
    public:
        Iterator(Node* n) : node(n) {}

        Iterator& operator++() {
            node = node->next;
            return *this;
        }

        Iterator& operator--() {
            node = node->prev;
            return *this;
        }

        bool operator==(const Iterator rhs) const {
            return node == rhs.node;
        }

        bool operator!=(const Iterator rhs) const {
            return node != rhs.node;
        }

        int& operator*() const {
            return node->data;
        }
    private:
        Node* node;
    };

    Iterator begin() { return Iterator(header->next); }

    Iterator end() { return trailer; }

    Iterator insert(Iterator it, int num) {
        Node* new_node = new Node{num, it.node->prev, it.node};
        it.node->prev = new_node;
        new_node->prev->next = new_node;
        num_items++;
        return Iterator(new_node);
    }

    Iterator erase(Iterator it) {
        it.node->prev->next = it.node->next;
        it.node->next->prev = it.node->prev;
        Node* next = it.node->next;
        delete it.node;
        num_items--;
        return Iterator(next);
    }
private:
    struct Node {
        int data;
        Node* prev;
        Node* next;
    };
    Node* header;
    Node* trailer;
    size_t num_items;
};

// Task 1
void printListInfo(const List& myList) {
        cout << "size: " << myList.size()
             << ", front: " << myList.front()
             << ", back(): " << myList.back()
             << ", list: " << myList << endl;
}

// The following should not compile. Check that it does not.
// void changeFrontAndBackConst(const List& theList) {
//     theList.front() = 17;
//     theList.back() = 42;
// }


void changeFrontAndBack(List& theList) {
    theList.front() = 17;
    theList.back() = 42;
}

// Task 4
void printListSlow(const List& myList) {
    for (size_t i = 0; i < myList.size(); ++i) {
        cout << myList[i] << ' ';
    }
    cout << endl;
}
/*
// Task 8
void doNothing(List aList) {
    cout << "In doNothing\n";
    printListInfo(aList);
    cout << "Leaving doNothing\n";
}    
*/

int main() {

    // Task 1
    cout << "\n------Task One------\n";
    List myList;
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        cout << "myList.push_back(" << i*i << ");\n";
        myList.push_back(i*i);
        printListInfo(myList);
    }
    cout << "===================\n";
    
    cout << "Modify the first and last items, and display the results\n";
    changeFrontAndBack(myList);
    printListInfo(myList);
    cout << "===================\n";

    cout << "Remove the items with pop_back\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.pop_back();
    }
    cout << "===================\n";

    // Task 2
    cout << "\n------Task Two------\n";
    cout << "Fill empty list with push_front: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        cout << "myList2.push_front(" << i*i << ");\n";
        myList.push_front(i*i);
        printListInfo(myList);
    }
    cout << "===================\n";
    cout << "Remove the items with pop_front\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.pop_front();
    }
    printListInfo(myList);
    cout << "===================\n";

    // Task 3
    cout << "\n------Task Three------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        myList.push_back(i*i);
    }
    printListInfo(myList);
    cout << "Now clear\n";
    myList.clear();
    cout << "Size: " << myList.size() << ", list: " << myList << endl;
    cout << "Okay now add an item\n";
    myList.push_back(1);
    cout << "Size: " << myList.size() << ", list: " << myList << endl;
    cout << "Clear again\n";
    myList.clear();
    cout << "Size: " << myList.size() << ", list: " << myList << endl;
    cout << "===================\n";

    // Task 4
    cout << "\n------Task Four------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
    cout << "Display elements with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
    cout << endl;
    cout << "Add one to each element with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) myList[i] += 1;
    cout << "And print it out again with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
    cout << endl;
    cout << "Now calling a function, printListSlow, to do the same thing\n";
    printListSlow(myList);
    cout << "Finally, for this task, using the index operator to modify\n"
         << "the data in the third item in the list\n"
         << "and then using printListSlow to display it again\n";
    myList[2] = 42;
    printListSlow(myList);
    

    // Task 5
    cout << "\n------Task Five------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
    printListInfo(myList);
    cout << "Now display the elements in a ranged for\n";
    for (int x : myList) cout << x << ' ';
    cout << endl;
    cout << "And again using the iterator type directly:\n";
    // Note you can choose to nest the iterator class or not, your choice.
    //for (iterator iter = myList.begin(); iter != myList.end(); ++iter) {
    for (List::Iterator iter = myList.begin(); iter != myList.end(); ++iter) {
        cout << *iter << ' ';
    }
    cout << endl;
    cout << "WOW!!! (I thought it was cool.)\n";

    // Task 6
    cout << "\n------Task Six------\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    printListInfo(myList);
    cout << "Filling an empty list with insert at begin(): "
         << "i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.begin(), i*i);
    printListInfo(myList);
    // ***Need test for insert other than begin/end***
    cout << "===================\n";

    // Task 7
    cout << "\n------Task Seven------\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    cout << "Erasing the elements in the list, starting from the beginning\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.erase(myList.begin());
    }
    // ***Need test for erase other than begin/end***
    cout << "===================\n";
/*
    // Task 8
    cout << "\n------Task Eight------\n";
    cout << "Copy control\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    printListInfo(myList);
    cout << "Calling doNothing(myList)\n";
    doNothing(myList);
    cout << "Back from doNothing(myList)\n";
    printListInfo(myList);

    cout << "Filling listTwo with insert at begin: i*i for i from 0 to 9\n";
    List listTwo;
    for (int i = 0; i < 10; ++i) listTwo.insert(listTwo.begin(), i*i);
    printListInfo(listTwo);
    cout << "listTwo = myList\n";
    listTwo = myList;
    cout << "myList: ";
    printListInfo(myList);
    cout << "listTwo: ";
    printListInfo(listTwo);
    cout << "===================\n";
*/
}
