#ifndef LINKED_ADT_LIST_H
#define LINKED_ADT_LIST_H

#include <cstddef>
#include <string>

template <typename T>
class LinkedADTList {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& d) : data(d), next(nullptr) {}
    };

public:
    /**
     *
     */
    class Iterator {
    public:
        explicit Iterator(Node* ptr) : cur(ptr) {}
        T& operator*() { return cur->data; }
        Iterator& operator++() { cur = cur->next; return *this; }
        bool operator!=(const Iterator& other) const { return cur != other.cur; }
    private:
        Node* cur;
    };

    LinkedADTList();
    LinkedADTList(const LinkedADTList& other);
    LinkedADTList& operator=(const LinkedADTList& other);
    ~LinkedADTList();

    void putItem(const T& item);
    bool deleteItem(const T& item);
    void makeEmpty();
    bool getItem(const T& key, T& found_item) const;
    int getLength() const;
    bool isFull() const;

    Iterator begin() { return Iterator(head_); }
    Iterator end() { return Iterator(nullptr); }

private:
    Node* head_;
    int length_;

    void copyFrom(const LinkedADTList& other);
};

#endif
