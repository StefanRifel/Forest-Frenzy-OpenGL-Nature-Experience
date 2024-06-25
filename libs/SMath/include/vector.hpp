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
    vector(const vector<T>& other);
    vector(vector<T>&& other) noexcept;
    vector<T>& operator=(const vector<T>& other);
    vector<T>& operator=(vector<T>&& other) noexcept;
    void resize(size_t new_size);
    void push_back(const T& element);
    void push_back(T&& element);
    void pop_back();
    T& at(int index);
    const T& at(int index) const;
    [[nodiscard]] int size() const { return length; }
    [[nodiscard]] size_t capacity() const { return storage; }
    bool empty() const;

    // Iterator class
    class iterator {
    public:
        using iterator_category = std::random_access_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;

        explicit iterator(pointer ptr) : m_ptr(ptr) {}

        reference operator*() const { return *m_ptr; }
        pointer operator->() { return m_ptr; }

        // Prefix increment
        iterator& operator++() { ++m_ptr; return *this; }
        // Postfix increment
        iterator operator++(int) { iterator tmp = *this; ++m_ptr; return tmp; }

        // Comparison operators
        friend bool operator==(const iterator& a, const iterator& b) { return a.m_ptr == b.m_ptr; }
        friend bool operator!=(const iterator& a, const iterator& b) { return a.m_ptr != b.m_ptr; }

    private:
        pointer m_ptr;
    };

    iterator begin() const { return iterator(data); }
    iterator end() const { return iterator(data + length); }

private:
    T* data;
    size_t storage;
    int length;
};

template<typename T>
bool vector<T>::empty() const {
    return length == 0;
}

template <typename T>
vector<T>::vector() : data{nullptr}, storage{0}, length{0} {}

template <typename T>
vector<T>::~vector() {
    if (data) {
        for (int i = 0; i < length; ++i) {
            data[i].~T(); // Explicitly call destructor for each element
        }
        free(data); // Free the allocated memory
    }
}

template <typename T>
vector<T>::vector(const vector<T>& other) : storage{other.storage}, length{other.length} {
    data = static_cast<T*>(malloc(storage * sizeof(T)));
    if (!data) {
        throw std::bad_alloc();
    }
    try {
        for (int i = 0; i < length; ++i) {
            new (&data[i]) T(other.data[i]); // Placement new to copy construct elements
        }
    } catch (...) {
        free(data);
        throw;
    }
}

template <typename T>
vector<T>::vector(vector<T>&& other) noexcept : data{other.data}, storage{other.storage}, length{other.length} {
    other.data = nullptr;
    other.storage = 0;
    other.length = 0;
}

template <typename T>
vector<T>& vector<T>::operator=(const vector<T>& other) {
    if (this != &other) {
        if (data) {
            for (int i = 0; i < length; ++i) {
                data[i].~T(); // Destruct current elements
            }
            free(data); // Free current memory
        }
        storage = other.storage;
        length = other.length;
        data = static_cast<T*>(malloc(storage * sizeof(T))); // Allocate new memory
        if (!data) {
            throw std::bad_alloc();
        }
        try {
            for (int i = 0; i < length; ++i) {
                new (&data[i]) T(other.data[i]); // Placement new to copy construct elements
            }
        } catch (...) {
            free(data);
            throw;
        }
    }
    return *this;
}

template <typename T>
vector<T>& vector<T>::operator=(vector<T>&& other) noexcept {
    if (this != &other) {
        if (data) {
            for (int i = 0; i < length; ++i) {
                data[i].~T(); // Destruct current elements
            }
            free(data); // Free current memory
        }
        data = other.data;
        storage = other.storage;
        length = other.length;
        other.data = nullptr;
        other.storage = 0;
        other.length = 0;
    }
    return *this;
}

template <typename T>
void vector<T>::resize(size_t new_size) {
    if (new_size > storage) {
        T* newData = static_cast<T*>(malloc(new_size * sizeof(T))); // Allocate new memory
        if (!newData) {
            throw std::bad_alloc();
        }
        try {
            for (size_t i = 0; i < length; ++i) {
                new (&newData[i]) T(std::move(data[i])); // Placement new to move construct elements
                data[i].~T(); // Explicitly call destructor for moved-from elements
            }
        } catch (...) {
            free(newData);
            throw;
        }
        free(data); // Free old memory
        data = newData;
        storage = new_size;
    }
}

template <typename T>
void vector<T>::push_back(const T& element) {
    if (length == storage) {
        resize(storage == 0 ? 1 : storage * 2);
    }
    new (&data[length++]) T(element); // Placement new to copy construct element
}

template <typename T>
void vector<T>::push_back(T&& element) {
    if (length == storage) {
        resize(storage == 0 ? 1 : storage * 2);
    }
    new (&data[length++]) T(std::move(element)); // Placement new to move construct element
}

template <typename T>
void vector<T>::pop_back() {
    if (length > 0) {
        data[--length].~T(); // Explicitly call destructor for the last element
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

template <typename T>
const T& vector<T>::at(int index) const {
    if (index >= length || index < 0) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

#endif // VECTOR_HH
