// vector.hpp
#ifndef VECTOR_HH
#define VECTOR_HH

#include <cstdlib>
#include <stdexcept>
#include <iterator>

template <typename T>
class vector {
public:
    vector();
    ~vector();
    void resize();
    void push_back(const T& element);
    void pop_back();
    T& at(int index);
    size_t size() const { return length; }
    size_t capacity() const { return storage; }
    
    // Iterator class
    class iterator {
    public:
        using iterator_category = std::random_access_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;
        
        iterator(pointer ptr) : m_ptr(ptr) {}
        
        reference operator*() const { return *m_ptr; }
        pointer operator->() { return m_ptr; }
        
        // Prefix increment
        iterator& operator++() { ++m_ptr; return *this; }  
        // Postfix increment
        iterator operator++(int) { iterator tmp = *this; ++m_ptr; return tmp; }

        friend bool operator==(const iterator& a, const iterator& b) { return a.m_ptr == b.m_ptr; }
        friend bool operator!=(const iterator& a, const iterator& b) { return a.m_ptr != b.m_ptr; }

    private:
        pointer m_ptr;
    };

    iterator begin() { return iterator(data); }
    iterator end() { return iterator(data + length); }

private:
    T* data;
    size_t storage;
    size_t length;
};

template <typename T>
vector<T>::vector() : data{nullptr}, storage{0}, length{0} {}

template <typename T>
vector<T>::~vector() {
    free(data);
}

template <typename T>
void vector<T>::resize() {
    storage = (storage == 0) ? 1 : storage * 2;
    T* newData = (T*)malloc(storage * sizeof(T));
    for (size_t i = 0; i < length; ++i) {
        newData[i] = data[i];
    }
    free(data);
    data = newData;
}

template <typename T>
void vector<T>::push_back(const T& element) {
    if (length == storage) {
        resize();
    }
    data[length++] = element;
}

template <typename T>
void vector<T>::pop_back() {
    if (length > 0) {
        --length;
    } else {
        throw std::out_of_range("Pop from empty vector");
    }
}

template <typename T>
T& vector<T>::at(int index) {
    if (index >= length || index < 0) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

#endif // VECTOR_HPP
