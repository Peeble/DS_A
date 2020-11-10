//
//  st.h
//  stacks_queues_bags
//
//  Created by William McCarthy on 178//20.
//  Copyright © 2020 William McCarthy. All rights reserved.
//

#ifndef st_h
#define st_h

#include <iostream>
#include "array.h"
#include "queue.h"


template <typename Key, typename Value> class binary_search_st;
//template <typename Key, typename Value> class binary_search_st::iterator;

template <typename Key, typename Value>
class binary_search_st {
//public:
//  template <typename T>
//  class iterator {
//    const array_<T>& arr_;
//    size_t current_;
//
//    iterator(const array_<T>& arr) : iterator(arr, 0) {}
//    iterator(const array_<T>& arr, size_t current) : arr_(arr), current_(current),  { }
//    iterator(const iterator& other) : iterator(other.arr_) { copy(other); }
//    iterator& operator=(const iterator& other) {  if (this != &other) { copy(other); }   return *this; }
//    iterator& operator++() {  ++current_;  return *this; }
//    iterator& operator++(int) {  iterator it = *this;  ++current_;  return it; }
//    const T& operator*() const {  return arr_[current_];  }
//    bool operator==(const iterator& other) const { return current_ == other.current_; }
//    bool operator!=(const iterator& other) const { return !operator==(other); }
//  private:
//    void copy(const iterator& other) { std::copy(other.arr_, other.arr_ + other.size_, arr_);  current_ = other.current_; }
//  };   // end of Iterator ------------------------------------------------------------------------

private:
  const static size_t MIN_CAPACITY_;
  const static Value& null_value_;

  const comparator<Key>& comp_;
  size_t size_;
  array_<Key> keys_;
  array_<Value> values_;

  bool check() const { return sorted() && rank_check(); }
  bool sorted() const {
    for (size_t i = 1; i < size_; ++i) {
      if (less(keys_[i], keys_[i - 1], comp_)) { return false; }
    }
    return true;
  }
  bool rank_check() const {
    for (size_t i = 0; i < size_; ++i) {
      if (i != rank(select(i))) { return false; }
    }
    for (size_t i = 0; i < size_; ++i) {
      Key k = select(rank(keys_[i]));
      if (less(keys_[i], k, comp_) || less(k, keys_[i], comp_)) { return false; }
    }
    return true;
  }
  void check_underflow() {
    size_t capacity_ = keys_.capacity();
    if (empty()) { throw new std::underflow_error("underflow in delete_min\n"); }
    if (size_ <= capacity_ / 4) { resize(capacity_ / 2); }
  }
  void check_overflow() {
    size_t capacity_ = keys_.capacity();
    if (size_ >= capacity_) { resize(2 * capacity_); }
  }
//  void check_nullkey(Key key) const { if (key == nullptr) { throw new std::invalid_argument("arg is nullptr\n"); } }
  void resize(size_t capacity) {
    assert(capacity >= size_);
//    std::cout << "\nResizing from: " << keys_.capacity() << " to " << capacity << "\n";
    keys_.resize(capacity);
    values_.resize(capacity);
  }

public:
//  binary_search_st() : binary_search_st(fwd_comparator<Key>(), 2) { }
  binary_search_st(const comparator<Key>& comp=fwd_comparator<Key>(), size_t capacity=2)
  : size_(0), comp_(comp), keys_(capacity), values_(capacity) { }
  
  void put(Key key, const Value& val) {
//    check_nullkey(key);
//    if (val == Value(nullptr)) { delete_key(key);  return; }
    size_t i = rank(key);
    int cmp = compare(keys_[i], key);
    if (cmp == 0) {
      values_[i] = val;
      return;
    }
    check_overflow();
//    std::cout << "moving entries to right\n";
    for (size_t j = size_; j > i; --j) {
      keys_[j] = keys_[j - 1];
      values_[j] = values_[j - 1];
    }
    for (size_t i = 0; i < size_; ++i) {
      std::cout << "keys[" << i << "] = " << keys_[i] << ", and values_[" << i << "] = " << values_[i] << "\n";
    }

    if (i > keys_.capacity()) { resize(2 * i); }
    keys_[i] = key;    keys_.size_inc();
    values_[i] = val;  values_.size_inc();
    ++size_;
    for (size_t i = 0; i < size_; ++i) {
      std::cout << "keys[" << i << "] = " << keys_[i] << ", and values_[" << i << "] = " << values_[i] << "\n";
    }
  }
  Value get(Key key) {
//    check_nullkey(key);
//    if (empty()) { return const_cast<Value&>(null_value_); }
    if (empty()) { throw new std::underflow_error("trying to get from empty binary_search_st\n"); }
    size_t i = rank(key);
    if (i < size_ && compare(keys_[i], key) == 0) {
      Value val = values_[i];
      return val;
    }
//    if (i < size_ && less(keys_[i], key, comp_)) { return values_[i]; }
//    return const_cast<Value&>(null_value_);
    throw new std::invalid_argument("key not present in binary_search_st\n");
  }
  void delete_key(Key key) {
    check_underflow();
//    check_nullkey();
    size_t i = rank(key);
    if (i == size_ || less(keys_[i], key, comp_)) { return; }  // key not in table
    for (size_t j = i; j < size_ - 1; ++j) {
      keys_[j] = keys_[j + 1];
      values_[j] = values_[j + 1];
    }
    --size_;
    keys_[size_] = Key();
    values_[size_] = null_value_;
  }
  void delete_min() {  check_underflow();  delete_key(min());  }
  void delete_max() {  check_underflow();  delete_key(max());  }
  bool contains(Key key) {  /* check_nullkey(key);*/
    size_t i = rank(key);
    if (i < size_ && compare(keys_[i], key) == 0) {
      return true;
    } else { return false; }
//    bool contain = get(key) != Value(nullptr);
//    return contain;
  }
  bool empty() const  { return size_ == 0; }
  size_t size() const { return size_; }
  size_t size(Key low, Key high) const {
//    check_nullkey(low);
//    check_nullkey(high);
    if (less(high, low, comp_)) { return 0;
    } else if (contains(high)) { return rank(high) - rank(low) + 1;
    } else { return rank(high) - rank(low); }
  }
  Key min() const {  check_underflow();  return keys_[0]; }
  Key max() const {  check_underflow();  return keys_[size_ - 1]; }
  Key floor(Key key) const {
//    check_nullkey(key);
    size_t i = rank(key);
    if (i < size_ && less(key, keys_[i], comp_)) { return keys_[i];
    } else { return (i == 0 ? nullptr : keys_[i - 1]); }
  }
  Key ceiling(Key key) const {  /*check_nullkey(key);*/  size_t i = rank(key);  return (i == size_ ? nullptr : keys_[i]); }
  size_t rank(Key key) {
//    check_nullkey(key);
    int low = 0, high = (int)size_ - 1;
    while (low <= high) {
      int mid = low + (high - low) / 2;
      int cmp = compare(key, keys_[mid], comp_);
      if (cmp < 0) {
        high = mid - 1;
      } else if (cmp > 0) { low = mid + 1;
      } else { return mid; }
    }
    return low;  // TODO
  }
  Key select(size_t k) const {
    if (k > keys_.capacity() || k >= size_) { throw new std::invalid_argument("k too large\n"); }
    return keys_[k];
  }
//  iterator array_<Key>::iterator keys() const { return keys(min(), max()); }
  const array_<Key>& keys() const { return keys_; }
  const array_<Value>& values() const { return values_; }
//  iterator array_<Key>::iterator begin() const { return iterator(keys_); }
//  iterator array_<Key>::iterator end() const { return iterator(keys_, size_); }
//  iterator array_<Key>::iterator keys(Key low, Key high) const {
////    check_nullkey(low);
////    check_nullkey(high);
//    array_queue<Key> qu;
//    if (less(high, low, comp_)) { return qu; }
//    for (size_t i = rank(low); i < rank(high); ++i) {
//      qu.enqueue(keys_[i]);
//    }
//    if (contains(high)) { qu.enqueue(keys_[rank(high)]); }
//    return qu;
//  }
};

template <typename Key, typename Value>
const size_t binary_search_st<Key, Value>::MIN_CAPACITY_ = 20;

template <typename Key, typename Value>
const Value& binary_search_st<Key, Value>::null_value_ = Value(nullptr);



//---------------------------------------------------------------------------
// frequency counter
//
#define ARGC_ERROR 1

void frequency_ctr(int argc, const char* argv[], const std::string& usage) {
  if (argc != 2) { std::cerr << usage << "\n";  exit(ARGC_ERROR); }
  size_t minlen = atoi(argv[1]);

  binary_search_st<std::string, size_t> symtable;
  std::string word;
  while (std::cin >> word) {
    if (word.length() < minlen) { continue; }
    if (!symtable.contains(word)) { symtable.put(word, 1);
    } else                      { symtable.put(word, symtable.get(word) + 1); }
  }
  std::string max = "";
  symtable.put(max, 0);
  for (const std::string& a_word : symtable.keys()) {
    if (symtable.get(a_word) > symtable.get(max)) {
      max = a_word;
    }
  }
  std::cout << max << " " << symtable.get(max);
}

#endif /* st_h */
