#include <iostream>
#include <iterator>
#include "LinkedListInterface.h"
using namespace std;

template <typename T>
class LinkedList : protected LinkedListInterface<T> {

    private:
        struct Node {
            T data;
            Node* next;
            Node(const T& value) {
                data = value;
                next = NULL;
            };
            Node() {
                next = NULL;
            };
        };
        Node* head;

    public:
        class Iterator{
            private:
                Node* iNode;
            public:
                Iterator(Node* head) : iNode(head) { }
                ~Iterator() {}

                friend std::ostream& operator<< (std::ostream& os, LinkedList<T>& linkedList)
                {
                    for (Iterator iter = linkedList.begin(); iter != linkedList.end(); ++iter)
                    {
                        os << *iter << " ";
                    }
                    return os;
                } 

                T& operator*() const {
                    cout << " Iterator::operator*() ";
                    return iNode->data;
                }

                bool operator!=(const Iterator& rhs) const{
                    if (iNode != rhs.iNode) {
                        return true;
                    }
                    cout << " Iterator::operator!=() ";
                    return false;
                }

                Iterator& operator++(){
                    cout << " Iterator::operator++() ";
                    iNode = iNode->next;
                    return *this;
                }
                Node* getNode() {
                    return iNode;
                }
        };

        Iterator begin(void){
            return LinkedList<T>::Iterator(head);
        }

        Iterator end(void){
            return LinkedList<T>::Iterator(NULL);
        }

        /** Return iterator pointing found value in linked list */
        Iterator find(Iterator first, Iterator last, const T& value){
          //  cout << endl << "find " << value;
            while (first != last) {
                if (*first == value) return first;
                ++first;
            }
            throw string("Not Found");
            return first;
        }

        /** Return iterator pointing to inserted value in linked list */
        Iterator insert(Iterator position, const T& value){
            if (position.getNode() == head) {
                Node* tempNode = new Node(value);
                tempNode->next = head;
                head = tempNode;
            }
            else {
                Node* temp = head;
                while (temp->next != position.getNode()) {
                    temp = temp->next;
                }
                temp->next = new Node(value);
                temp->next->next = position.getNode();
            }
            return LinkedList<T>::Iterator(position);
        }
        /** Return iterator pointing to inserted value in linked list */
        Iterator insert_after(Iterator position, const T& value){
            cout << endl << "insert_after " << value << " after " << *position;
            Node* temp = position.getNode()->next;
            position.getNode()->next = new Node;
            position.getNode()->next->data = value;
            position.getNode()->next->next = temp;

            return LinkedList<T>::Iterator(position.getNode());
        }

        /** Return iterator pointing to next item after deleted node linked list */
        Iterator erase(Iterator position){
            cout << endl << "erase " << *position;
            Node* temp = head; 
            if (position.getNode() == head) {
                head = position.getNode()->next;
                delete position.getNode();
            }
            else {
                while (temp->next != position.getNode()) {
                    temp = temp->next;
                }
                temp->next = position.getNode()->next;
                delete position.getNode();
            }
            return LinkedList<T>::Iterator(temp);
        }

        /** Replace first found old_value(s) with new_value */
        void replace(Iterator first, Iterator last, const T& old_value, const T& new_value){
            cout << endl << "replace " << old_value << " with " << new_value;
            while (first != last) {
                if (*first == old_value) {
                    *first = new_value;
                }
                ++first;
            }
            return;
        };

        LinkedList() {
            head =  NULL;
        };

        ~LinkedList() {
            clear();
        };

        void push_front(const T& value) {
            if (head == NULL) {
                head = new Node(value);
                return;
            }
            else {
                Node* tempNode = new Node(value);
                tempNode->next = head;
                head = tempNode;
            }
        };
        void pop_front(void) {
                Node* temp = head;
                head = head->next;
                delete temp;
        };
        T& front(void) {
            return head->data;
        };
        bool empty(void) const {
            bool question;
            if (head == NULL) {
                question = true;
            }
            else {
                question = false;
            }
            return question;
        };
        void remove(const T& value) {
            // Store head node  
            Node* temp = head, *prev = NULL;

            // If head node itself holds the key  
            // or multiple occurrences of key  
            while (temp != NULL && temp->data == value) {
                head = temp->next; // Changed head
                delete temp;
                temp = head;      // Change Temp  
            }
            // Delete occurrences other than head  
            while (temp != NULL) {
                while (temp != NULL && temp->data != value) {
                    prev = temp;
                    temp = temp->next;
                }
                if (temp != NULL) {
                    prev->next = temp->next;
                    delete temp;
                    temp = prev->next;
                }
            }
        };
        void clear(void) {
            while (head != NULL) {
                Node* deleter = head->next;
                delete head;
                head = deleter;
            }
        };
        void reverse(void) {
            // Initialize current, previous and 
            // next pointers 
            Node* current = head;
            Node* prev = NULL, * next = NULL;
            while (current != NULL) {
                // Store next 
                next = current->next;
                // Reverse current node's pointer 
                current->next = prev;
                // Move pointers one position ahead. 
                prev = current;
                current = next;
            }
            head = prev;
        };
        size_t size(void) const {
            int count = 0; // Initialize count  
            Node* current = head; // Initialize current  
            while (current != NULL){
                count++;
                current = current->next;
            }
            return count;
        };
        string toString(void) const {
            ostringstream oss;
            Node* temp = head;
            while (temp != NULL) {
                oss << temp->data << " ";
                temp = temp->next;
            }
            return oss.str();
        };

};




