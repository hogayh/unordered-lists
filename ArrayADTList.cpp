#include "LinkedADTList.h"
#include <utility>      // std::swap

// ---------- internals ----------

template <typename DataType>
void LinkedADTList<DataType>::destroyAll() {
    auto* cur = head_;
    while (cur) {
        auto* nxt = cur->next;
        delete cur;
        cur = nxt;
    }
    head_ = nullptr;
    len_ = 0;
}

template <typename DataType>
void LinkedADTList<DataType>::copyFrom(const LinkedADTList& other) {
    if (!other.head_) { head_ = nullptr; len_ = 0; return; }
    // copy in original order
    Node* src = other.head_;
    head_ = new Node(src->data);
    Node* tail = head_;
    src = src->next;
    while (src) {
        tail->next = new Node(src->data);
        tail = tail->next;
        src = src->next;
    }
    len_ = other.len_;
}

// ---------- rule of three ----------

template <typename DataType>
LinkedADTList<DataType>::LinkedADTList(const LinkedADTList& other)
    : head_(nullptr), len_(0) {
    copyFrom(other);
}

template <typename DataType>
LinkedADTList<DataType>& LinkedADTList<DataType>::operator=(const LinkedADTList& other) {
    if (this == &other) return *this;
    destroyAll();
    copyFrom(other);
    return *this;
}

template <typename DataType>
LinkedADTList<DataType>::~LinkedADTList() {
    destroyAll();
}

// ---------- core API ----------

template <typename DataType>
void LinkedADTList<DataType>::putItem(const DataType& item) {
    // insert at head (unordered, O(1))
    Node* n = new Node(item);
    n->next = head_;
    head_ = n;
    ++len_;
}

template <typename DataType>
bool LinkedADTList<DataType>::getItem(const DataType& item, DataType& found) const {
    for (Node* cur = head_; cur; cur = cur->next) {
        if (cur->data == item) { found = cur->data; return true; }
    }
    return false;
}

template <typename DataType>
void LinkedADTList<DataType>::makeEmpty() {
    destroyAll();
}

template <typename DataType>
bool LinkedADTList<DataType>::deleteItem(const DataType& item) {
    Node* prev = nullptr;
    Node* cur  = head_;
    while (cur) {
        if (cur->data == item) {
            if (prev) prev->next = cur->next;
            else      head_ = cur->next;
            delete cur;
            --len_;
            return true;
        }
        prev = cur;
        cur = cur->next;
    }
    return false;
}

// ---------- iterator ----------

template <typename DataType>
typename LinkedADTList<DataType>::Iterator::reference
LinkedADTList<DataType>::Iterator::operator*() const {
    if (!cur_) throw std::out_of_range("LinkedADTList iterator deref at end");
    return cur_->data;
}

template <typename DataType>
typename LinkedADTList<DataType>::Iterator&
LinkedADTList<DataType>::Iterator::operator++() {
    if (cur_) cur_ = cur_->next;
    return *this;
}

// ------------- EXPLICIT INSTANTIATIONS (optional) -------------
template class LinkedADTList<int>;
template class LinkedADTList<std::string>;
// Add other concrete types as needed, e.g. Customer
// template class LinkedADTList<Customer>;
