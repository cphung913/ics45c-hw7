#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>

template <typename T>
class Array {
public:
    Array() : len{0}, buf{nullptr} {
    }

    explicit Array(int len) : len{len}, buf{new T[len]} {
    }

    Array(const Array &a) : len{a.length()}, buf{new T[len]} {
        for (int i = 0; i < len; i++) {
            buf[i] = a[i];
        }
    }

    Array(Array &&a) noexcept : len{0}, buf{nullptr} {
        swap(*this, a);
    }

    friend void swap(Array& lhs, Array& rhs) noexcept {
        std::swap(lhs.len, rhs.len);
        std::swap(rhs.buf, lhs.buf);
    }

    Array &operator=(const Array &a) {
        Array cpy(a);
        swap(cpy, *this);
        return *this;
    }

    Array &operator=(Array &&a) noexcept {
        swap(a, *this);
        return *this;
    }
    
    ~Array() {
        delete[] buf;
    }

    int length() const {
        return len;
    }

    T& operator[](int index) {
        if (!in_bounds(index)) {
            throw std::string(
                "Exception operator[](" 
                + std::to_string(index) 
                + ") Out Of Range"
            );
        }
        return buf[index];
    }

    const T& operator[](int index) const {
        if (!in_bounds(index)) {
            throw std::string(
                "Exception operator[](" 
                + std::to_string(index) 
                + ") Out Of Range"
            );
        }
        return buf[index];
    }

    void fill(const T& val) {
        for (int i = 0; i < len; i++) {
            buf[i] = val;
        }
    }

    template <typename Fn>
    void fill_with_fn(Fn fn) {
        for (int i = 0; i < len; i++) {
            buf[i] = fn(i);
        }
    }
 
private:
    int len;
    T* buf;

    bool in_bounds(int index) const {
        return index >= 0 && index < len;
    }
};

template <typename T>
inline std::ostream& operator<<(std::ostream& out, const Array<T>& array) {
    std::stringstream temp;
    // We don't want to set formatting flags globally.
    temp << std::setprecision(2) << std::fixed << std::right;

    for (int i = 0; i < array.length(); ++i) {
        temp << std::setw(8) << array[i];
    }

    out << temp.str();
    return out;
}

template <typename T>
inline std::istream& operator>>(std::istream& in, Array<T>& array) {
    for (int i = 0; i < array.length(); ++i) {
        in >> array[i];
    }

    return in;
}

#endif
