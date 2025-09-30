/**
 * @file LinkedADTList.cpp
 * @brief Implementation of LinkedADTList methods.
 */
#include "LinkedADTList.h"

template <typename T>
void LinkedADTList<T>::destroyAll() {
    Node* cur = head_;
    while (cur) {
        Node* tmp = cur;
        cur = cur->next;
        delete tmp;
    }
    head_ = nullptr;
    length_ = 0;
}

template <typename T>
void LinkedADTList<T>::copyFrom(const LinkedADTList& other) {
    if (!other.head_) { head_ = nullptr; length_ = 0; return; }
    head_ = new Node(other.head_->data);
    Node* src = other.head_->next;
    Node* tail = head_;
    while (src) {
        tail->next = new Node(src->data);
        tail = tail->next;
        src = src->next;
    }
    length_ = other.length_;
}

template <typename T>
LinkedADTList<T>::LinkedADTList(const LinkedADTList& other)
    : head_(nullptr), length_(0) {
    copyFrom(other);
}

template <typename T>
LinkedADTList<T>& LinkedADTList<T>::operator=(const LinkedADTList& other) {
    if (this != &other) {
        destroyAll();
        copyFrom(other);
    }
    return *this;
}

template <typename T>
LinkedADTList<T>::~LinkedADTList() {
    destroyAll();
}

template <typename T>
void LinkedADTList<T>::putItem(const T& item) {
    Node* n = new Node(item, head_);
    head_ = n;
    ++length_;
}

template <typename T>
bool LinkedADTList<T>::deleteItem(const T& key) {
    Node* prev = nullptr;
    Node* cur  = head_;
    while (cur) {
        if (cur->data == key) {
            if (prev) prev->next = cur->next; else head_ = cur->next;
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
bool LinkedADTList<T>::getItem(const T& key, T& out) const {
    for (Node* cur = head_; cur; cur = cur->next) {
        if (cur->data == key) { out = cur->data; return true; }
    }
    return false;
}

// Explicit instantiations for common test types
template class LinkedADTList<int>;
template class LinkedADTList<std::string>;
