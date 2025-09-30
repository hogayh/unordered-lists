#ifndef LINKED_ADT_LIST_H
#define LINKED_ADT_LIST_H

#include <cstddef>
#include <stdexcept>
#include <utility>

/**
 * @brief Singly-linked node for LinkedADTList.
 */
template <typename T>
struct LLNode {
    T data{};
    LLNode* next{nullptr};
};

/**
 * @brief Unordered list backed by a singly-linked list.
 * @tparam T element type
 */
template <typename T>
class LinkedADTList {
public:
    /**
     * @brief Forward iterator over nodes.
     */
    class Iterator {
    public:
        explicit Iterator(LLNode<T>* p) : cur_(p) {}
        T& operator*() const { if (!cur_) throw std::out_of_range("Iterator at end"); return cur_->data; }
        Iterator& operator++() { if (cur_) cur_ = cur_->next; return *this; }
        bool operator==(const Iterator& rhs) const { return cur_ == rhs.cur_; }
        bool operator!=(const Iterator& rhs) const { return !(*this == rhs); }
    private:
        LLNode<T>* cur_{nullptr};
    };

    /// Default constructor
    LinkedADTList() : head_(nullptr), length_(0) {}

    /// Deep copy constructor
    LinkedADTList(const LinkedADTList& other) : head_(nullptr), length_(0) {
        if (!other.head_) return;
        head_ = new LLNode<T>{other.head_->data, nullptr};
        LLNode<T>* tail = head_;
        for (LLNode<T>* p = other.head_->next; p; p = p->next) {
            tail->next = new LLNode<T>{p->data, nullptr};
            tail = tail->next;
        }
        length_ = other.length_;
    }

    /// Copy-swap assignment
    LinkedADTList& operator=(LinkedADTList other) {
        swap(other);
        return *this;
    }

    /// Destructor
    ~LinkedADTList() { makeEmpty(); }

    /// Swap helper
    void swap(LinkedADTList& rhs) noexcept {
        std::swap(head_, rhs.head_);
        std::swap(length_, rhs.length_);
    }

    /// @return number of items
    int  getLength() const { return static_cast<int>(length_); }
    /// @return linked list isn’t capacity-bound; return false
    bool isFull()   const { return false; }

    /// Delete all nodes
    void makeEmpty() {
        LLNode<T>* p = head_;
        while (p) { LLNode<T>* n = p->next; delete p; p = n; }
        head_ = nullptr; length_ = 0;
    }

    /// Insert at head (O(1), unordered)
    void putItem(const T& item) {
        head_ = new LLNode<T>{item, head_};
        ++length_;
    }

    /// Find by value and copy into found_item
    bool getItem(const T& key, T& found_item) const {
        for (LLNode<T>* p = head_; p; p = p->next) {
            if (p->data == key) { found_item = p->data; return true; }
        }
        return false;
    }

    /// Compatibility overload: (key, bool& found)
    bool getItem(const T& key, bool& found) const {
        for (LLNode<T>* p = head_; p; p = p->next) {
            if (p->data == key) { found = true; return true; }
        }
        found = false; return false;
    }

    /// Delete first occurrence of key
    bool deleteItem(const T& key) {
        LLNode<T>* p = head_;
        LLNode<T>* prev = nullptr;
        while (p) {
            if (p->data == key) {
                if (prev) prev->next = p->next; else head_ = p->next;
                delete p; --length_; return true;
            }
            prev = p; p = p->next;
        }
        return false;
    }

    /// Iteration
    Iterator begin() { return Iterator(head_); }
    Iterator end()   { return Iterator(nullptr); }
    Iterator begin() const { return Iterator(head_); }
    Iterator end()   const { return Iterator(nullptr); }

private:
    LLNode<T>* head_;
    std::size_t length_;
};

#endif // LINKED_ADT_LIST_H
