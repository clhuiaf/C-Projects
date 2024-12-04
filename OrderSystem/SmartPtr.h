// This is to implement the smart pointer class

#ifndef SMARTPTR_H
#define SMARTPTR_H

#include <iostream>

template <typename T>
class SmartPtr {
    public:
        // Constructors & Destructors
        SmartPtr();
        // Adding explicit keyword to prevent from implicit conversion, causing deletion of the raw pointer
        // When the student directly parse the raw pointer to functions which accepts SmartPtr<T> as parameter
        explicit SmartPtr(T* p);
        SmartPtr(T& val);
        SmartPtr(const SmartPtr<T>& sp);
        ~SmartPtr();

        // Mutators
        void set(T& val);
        void unset();
        bool isNull() const;

        // Common operators & accessors
        SmartPtr<T>& operator=(const SmartPtr<T>& sp);
        bool operator==(const SmartPtr<T>& sp) const;
        bool operator!=(const SmartPtr<T>& sp) const;
        T& operator*() const;
        T* operator->() const;
        explicit operator bool() const;

        void printDetails() const {
            if (ptr == nullptr) {
                std::cout << "SmartPtr: (nullptr, ref_count: nullptr)" << std::endl;
                return;
            }
            std::cout << "SmartPtr: (" << *ptr << " ref_count: " << *ref_count << ")" << std::endl;
        }
        // Other methods
        friend std::ostream& operator<<(std::ostream& os, const SmartPtr<T>& sp) {
            if (sp.ptr == nullptr) {
                os << "SmartPtr: (nullptr)";
                return os;
            }
            os << "SmartPtr: (" << *sp.ptr << ")";
            return os;
        }

    private:
        // A raw pointer inside this container
        T* ptr;
        // A reference count for the raw pointer, showing how many SmartPtr objects are pointing to it
        unsigned int* ref_count;
};

#include "SmartPtr-impl.h"

#endif // SMARTPTR_H