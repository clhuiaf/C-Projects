#ifndef SMARTPTR_IMPL_H
#define SMARTPTR_IMPL_H

#include "SmartPtr.h"


// TODO: TASK 1 SmartPtr Class
// Complete & Implement all of the following functions
// Some functions have a dummy return value to let the program compile.
// You should replace the dummy return value with your own implementation.

// Constructors & Destructors
// TODO: Task 1.1 
template <typename T>
SmartPtr<T>::SmartPtr() : ptr(nullptr), ref_count(nullptr){ // No object is created
}

// TODO: Task 1.2
// Assume passing new X as argument
template <typename T>
SmartPtr<T>::SmartPtr(T* p) {
// A raw pointer p is passed to the constructor. 
// Assume that the pointer p is pointing to a variable or object of type T that was created using the new operator, storing the raw pointer and set ref_count to 1.
// We assume that all pointers provided to this constructor point to objects created using the new operator and are not currently managed by another SmartPtr object. 
// An explicit keyword is added to prevent implicit conversion and potential undefined behaviors. 
// Note that here p can possibly be nullptr.
    ptr = p;
    if (p != nullptr)
        ref_count = new unsigned int(1);
    else
        ref_count = nullptr;
}

// TODO: Task 1.3
// Only works for having copy constructor for T
template <typename T>
SmartPtr<T>::SmartPtr(T& val) {
// The conversion constructor allocates memory for a value type T by using the copy constructor.
// It creates a new object instance of T by copying val and sets ref_count to 1.
// We assume that class T has its copy constructor. 
// Here val must be a reference to a valid object, because a reference to nullptr is undefined in C++.
// The reason to copy val is because we do not know if the memory referenced by val is allocated on the stack or heap.
    ptr = new T(val);
    ref_count = new unsigned int(1);
}

// TODO: Task 1.4
template <typename T>
SmartPtr<T>::SmartPtr(const SmartPtr<T>& sp) {
// The copy constructor of SmartPtr does not allocate new memory.
// If it stores a valid pointer, copy and store the same pointer, and increment ref_count by 1, since there is one more SmartPtr instance sharing the same pointer.
// The heap memory pointed by ref_count is shared by the new SmartPtr when we copy-construct it from another SmartPtr.
// If sp stores nullptr, it just creates a new SmartPtr object with nullptr, which is basically the same with a default constructor.
    /*
    If sp stores nullptr, it just creates a new SmartPtr object with nullptr, 
    which is basically the same with a default constructor.
    */
    if (sp.ptr == nullptr){
        ptr = nullptr;
        ref_count = nullptr;
    }
    /*
    If it stores a valid pointer, copy and store the same pointer, 
    and increment ref_count by 1, since there is one more SmartPtr instance sharing the same pointer.
    */
    else{
        ptr = sp.ptr;
        ref_count = sp.ref_count;
        if (ref_count != nullptr) {
            (*ref_count)++;
        }
    }
}

// TODO: Task 1.5
template <typename T>
SmartPtr<T>::~SmartPtr() {
//The destructor of a SmartPtr instance.
// If the underlying ptr is nullptr, we can simply destruct the object safely.
// If ptr is not nullptr, we decrement ref_count by 1 as there is now one less SmartPtr object pointing to the variable/object.
// If ref_count is 0 after the decrement, we should deallocate the memory since the pointer is no longer being referred to by anyone.
// ref_count should also be deleted if we delete ptr.
// Unset the SmartPtr object.
    unset();
}

// Mutators
// TODO: Task 1.6
template <typename T>
void SmartPtr<T>::set(T& val) {
// This function allocates memory for a value type T by using the copy constructor. // new
// It creates a new object instance of T by copying val and set ref_count to 1. 
// The function also needs to ensure that the previous ptr content has been unset properly. 
// The previously pointed ptr should be deallocated as specified in the destructor. 
// Note that self-assignment is possible (i.e., val is exactly the object ptr points at).  
// Same with above, val must be a reference to a valid object, because a reference to nullptr is undefined in C++. 
// ref_count should also be deleted if we delete ptr.
// Hint: To do that, you should copy val first, then destruct current ptr and ref_count , and finally assign the new ptr.
    // Copy val first
    T* new_ptr = new T(val);
    unsigned int* new_ref_count = new unsigned int(1);
    // Destruct current ptr and ref_count
    unset();
    // Assign the new ptr
    ptr = new_ptr;
    ref_count = new_ref_count;
}

// TODO: Task 1.7
template <typename T>
void SmartPtr<T>::unset() {
// Set ptr to nullptr.
// The memory originally pointed to by ptr will be deallocated when no other instances of SmartPtr hold the same address.
// Same with above, ref_count should also be deleted if we delete ptr.
    if (ref_count != nullptr && (--(*ref_count) == 0)){
        delete ptr;
        delete ref_count;
    }
    // Prevent any pointer dangling
    ptr = nullptr;
    ref_count = nullptr;
}

template <typename T>
bool SmartPtr<T>::isNull() const {
    return !bool(*this);
}

// Common operators & accessors
// TODO: Task 1.8
template <typename T>
SmartPtr<T>& SmartPtr<T>::operator=(const SmartPtr<T>& sp) {
// The assignment operator stores the same address in ptr as in sp.ptr. 
// The memory originally pointed by ptr will be deallocated if no other instance is using that memory, 
// increment or decrement the ref_count accordingly if the memory is still being used by another instance of SmartPtr. 
// For the newly pointed ptr, we should increment the ref_count accordingly as we have more SmartPtr objects. 
// This operator should support cascading assignment, i.e., sp = sp1 = sp2;.
// Note that sp should be copied before deleting the old ptr if no other instances are pointing to the old ptr.
    // Avoid self-assignment
    if (this != &sp){
        // Copy the passed SmartPtr object to create reference to it
        SmartPtr<T> temp(sp);
        // Unset the SmartPtr object
        unset();
        // If the passed SmartPtr object stores nullptr, we just set the current SmartPtr object to nullptr.
        if (temp.ptr == nullptr){
            ptr = nullptr;
            ref_count = nullptr;
        }
        //  If the passed SmartPtr object stores a valid pointer, we copy and store the same pointer,
        else{
            ptr = temp.ptr;
            ref_count = temp.ref_count;
            if (ref_count != nullptr){
                (*ref_count)++;
            }
        }
    }
    // Return the current SmartPtr object
    return *this;
}

// TODO: Task 1.9
template <typename T>
bool SmartPtr<T>::operator==(const SmartPtr<T>& sp) const {
    return ptr == sp.ptr;
}

template <typename T>
bool SmartPtr<T>::operator!=(const SmartPtr<T>& sp) const {
    return ptr != sp.ptr;
}

// TODO: Task 1.10
template <typename T>
T& SmartPtr<T>::operator*() const{ // Dereference operator
    // We do not check whether ptr is nullptr or not (like a raw pointer).
    return *ptr;
}

// TODO: Task 1.11
template <typename T>
T* SmartPtr<T>::operator->() const{
    // Return the address stored in ptr. Same with above, this overloads the arrow operator but NOT the dereference operator.
    return ptr;
}

// TODO: Task 1.12
// Note that the SmartPtr<T>::isNull() function is calling this bool operator
template <typename T>
SmartPtr<T>::operator bool() const {
    //Return true if ptr is not nullptr
    return ptr != nullptr;
}




#endif // SMARTPTR_IMPL_H