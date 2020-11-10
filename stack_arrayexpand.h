//
//  stack_arrayexpand.h
//  sqb
//
//  Created by William McCarthy on 159//20.
//  Copyright © 2020 William McCarthy. All rights reserved.
//

#ifndef stack_arrayexpand_h
#define stack_arrayexpand_h

#include <iostream>
#include "array_expand.h"

template <typename T>
class stack_arrayexpand {
private:
  array_expand<T> ae_;
  int sp_;

public:
//------------- iterator ----------------------------------------------
  class iterator {
  private:
    const array_expand<T>& array_;
    size_t index_;    // iterator data

  public:
    iterator(const array_expand<T>& array) : iterator(array, 0) { }
    iterator(const array_expand<T>& array, size_t index) : array_(array), index_(index) { }
    iterator& operator++() {  ++index_;  return *this; }

    T operator*() {  return array_[index_]; }
    bool operator==(const iterator& other) const { return &array_ == &other.array_ && index_ == other.index_; }
    bool operator!=(const iterator& other) const { return !operator==(other); }
  };
//------------- iterator ----------------------------------------------

public:
  stack_arrayexpand() : stack_arrayexpand(10) { }
  stack_arrayexpand(long capacity)
  : ae_(capacity), sp_(0) { }

  bool empty() const { return sp_ == 0; }

  void push(const std::initializer_list<T>& li) {
    for (const T& el : li) { push(el); }
  }
  void push(const T& value) { ae_.append(value);  ++sp_; }
  T pop() {
    check_underflow();
    const std::string& value = ae_.pop();
    --sp_;
    return value;
  }
  int sp() const { return sp_; }

  friend std::ostream& operator<<(std::ostream& os, const stack_arrayexpand& st) {
    if (st.empty()) { return os << "stack_arrayexpand is empty"; }
    for (size_t i = 0; i < st.sp_; ++i) { os << st.ae_[i] << " "; }
    return os;
  }

  class iterator begin() { return iterator(ae_, 0); }
  class iterator end()   { return iterator(ae_, sp_); }

  static void run_tests() {
//    stack_arrayexpand<std::string> st(5);
//    st.push({"three", "rings", "for", "the", "elven", "kings", "under", "the", "starry", "sky"});
//    std::cout << "st is: " << st << "\n";

//    stack_arrayexpand<std::string> st2 = st;   // copy ctor and assignment operator all work
//    stack_arrayexpand<std::string> st3;
//    st3 = st;

//    std::cout << "\nusing for each loop...\n";
//    for (const std::string& el : st) { std::cout << el << "\n"; }

    std::cout << "Enter some values (Ctrl-D to stop/Ctrl-Z on Windows\n\n";
    stack_arrayexpand<std::string> st4(5);
    std::string s;
    while (std::cin >> s) {
      if (s == "-") {
        std::cout << st4.pop() << " ";
        if (st4.empty()) { std::cout << " (stack is empty)\n"; }
      }
      else { st4.push(s); }
    }
  }
private:
  void check_underflow() {
    if (sp_ < 0) { throw new std::underflow_error("underflow\n"); }
  }
};

#endif /* stack_arrayexpand_h */
