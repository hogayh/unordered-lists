/**
 * @file LinkedADTList.cpp
 * @brief Implementation of LinkedADTList methods.
 */
#include "LinkedADTList.h"
#include <string> // for explicit instantiation

// ----- helpers -----
template <typename T>
void LinkedADTList<T>::copyFrom(const LinkedADTList<T>& other) {
    head_ = nullptr;
    length_ = 0;

    Node* src = other.head_;
    Node** tail = &head_;
    while (src) {
        *tail = new Node(src->data);
        tail = &((*tail)->next);
        src = src->next;
        ++length_;
    }
}

// ----- Big Three -----
template <typename T>
LinkedADTList<T>::LinkedADTList() : head_(nullptr), length_(0) {}

template <typename T>
LinkedADTList<T>::LinkedADTList(const LinkedADTList& other) : head_(nullptr), length_(0) {
    copyFrom(other);
}

template <typename T>
LinkedADTList<T>& LinkedADTList<T>::operator=(const LinkedADTList& other) {
    if (this != &other) {
        makeEmpty();
        copyFrom(other);
    }
    return *this;
}

template <typename T>
LinkedADTList<T>::~LinkedADTList() {
    makeEmpty();
}

// ----- Core ops -----
template <typename T>
void LinkedADTList<T>::putItem(const T& item) {
    Node* n = new Node(item);
    n->next = head_;
    head_ = n;
    ++length_;
}

template <typename T>
bool LinkedADTList<T>::deleteItem(const T& item) {
    Node* cur = head_;
    Node* prev = nullptr;
    while (cur) {
        if (cur->data == item) {
            if (prev) prev->next = cur->next;
            else      head_ = cur->next;
            delete cur;
            --length_;
            return true;
        }
        prev = cur;
        cur = cur->next;
    }
    return false;
}

template <typename T>
void LinkedADTList<T>::makeEmpty() {
    Node* cur = head_;
    while (cur) {
        Node* nxt = cur->next;
        delete cur;
        cur = nxt;
    }
    head_ = nullptr;
    length_ = 0;
}

template <typename T>
bool LinkedADTList<T>::getItem(const T& key, T& found_item) const {
    Node* cur = head_;
    while (cur) {
        if (cur->data == key) {
            found_item = cur->data;
            return true;
        }
        cur = cur->next;
    }
    return false;
}

// ----- Queries -----
template <typename T>
int LinkedADTList<T>::getLength() const {
    return length_;
}

template <typename T>
bool LinkedADTList<T>::isFull() const {
    return false; // linked list limited only by memory
}

// ----- Explicit instantiations for test types -----
template class LinkedADTList<int>;
template class LinkedADTList<std::string>;
