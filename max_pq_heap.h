//
//  max_pq_heap.h
//  sorts
//
//  Created by William McCarthy on 2310//20.
//

#ifndef max_pq_heap_h
#define max_pq_heap_h

#include "array.h"

#define MIN_CAPACITY 3

//------------------------------------------------------
template <typename T>
class max_pq_heap {
public:
  max_pq_heap() : max_pq_heap(MIN_CAPACITY_) { }
  max_pq_heap(const comparator<T>& compar) : max_pq_heap(MIN_CAPACITY, compar) { }
  max_pq_heap(size_t capacity, const comparator<T>& compar)
  : pq_(capacity + 1), comp(compar) { pq_.push_back(T()); }  // make space for skipped-over 0 entry
  
  max_pq_heap(const std::initializer_list<T>& li, const comparator<T>& compar)
  : max_pq_heap(li.size() + 1, compar) {
    for (const T& el : li) {
      if (el != "-") { insert(el);
      } else { std::cout << del_max() << " "; }
    }
    std::cout << "\t(" << size() << " left on the heap)\n\n";
  }
  ~max_pq_heap() {
//    std::cout << "destroying the max_pq_heap...\n";
  }

  T max() const {
    if (empty()) { throw new std::underflow_error("no such element\n"); }
    return pq_[1];
  }
  
  // Used to prevent access of array[0]
  bool empty() const { return pq_.size() == 1; }   // leaves 0 index empty
  size_t size() const { return pq_.size() - 1; }   // ditto
  
  // void resize(size_t capacity)     // handled by array_ class

  void clear() {
    std::cout << "clearing max_pq_heap...\n";
    while (!empty()) {
      del_max();
    }
    std::cout << *this << "\n";
  }
  
  void insert(const T& value) {
    // adds node to the end of the tree/array
    pq_.push_back(value);
//    std::cout << "in insert, pq is: " << pq_ << "\n";
    // Does a check to see if it needs to swim up the array, size() returns array.size() - 1 to account for 0 index being empty
    swim(size());
  }


  T del_max() {
    // max = root node, array[0]
    T maximum = pq_[1];
    // n = array.size()-1
    size_t n = size();
    
    // exchanges root node with bottom of tree
    exchange(1, n);
    // std::cout << "BLUB BLUB " << pq_[n+1] << "\n";
    // pops null value at end of array (not part of tree)
    pq_.pop_back();
    // sinks the root node down the tree
    sink(1);
    // sets the bottom of tree to null value, deleting what used to be the parent node/maximum
    pq_[n] = T();
    //std::cout << "at end of del_max , pq is: " << pq_ << "\n";
    // returns what used to be the maximum 
    return maximum;
  }
  void swim(size_t k) {
    // while not at root node and the parent of k is less than k
    // exchange with parent and move up the tree
    while (k > 1 && less(k / 2, k)) {
      exchange(k, k / 2);
      k /= 2;
    }
  }

  void sink(size_t k) {
    // Gets size of array-1
    size_t n = size();

    // children of parent node are 2k and 2k+1
    while (2 * k <= n) {
      size_t j = 2 * k;
      // check whether 2k or 2k+1 is bigger 
      // check whether we go off the end of the heap
      // if 2k is larger, increments j to identify it as the larger of the two
      if (j < n && less(j, j + 1)) { ++j; }
      // if k isn't smaller than either 2k or 2k+1 then we're done
      if (!less(k, j)) { break; }

      // if k is smaller, exchange with the larger of the two children nodes, move down the heap.
      exchange(k, j);
      k = j;
    }
  }
  friend std::ostream& operator<<(std::ostream& os, const max_pq_heap& maxpq) {
    if (maxpq.empty()) { return os << "max_pq_heap is empty\n"; }
    return os << maxpq.pq_ << "\n";
  }
  
  static void test_initializer_list(const std::initializer_list<T>& li,
                                    const comparator<std::string>& compar=fwd_comparator<std::string>()) {
    std::cout << "\n//======================================================\nTesting max_pq_heap with alphabetical std::initializer_list...\n";
    max_pq_heap<std::string> pqheap(li, compar);
    while (pqheap.size() > 3) {
      std::cout << pqheap.del_max() << " ";
    }
    std::cout << "\t(" << pqheap.size() << " left on the heap)\n\n";
  }
  static void test_file(const std::string& filename,
                        const comparator<std::string>& compar= fwd_comparator<std::string>()) {
    std::cout << "\n//======================================================\nTesting max_pq_heap with filename: '" << filename << "'...\n";

    max_pq_heap<std::string> pqheap(compar);
    std::string s;
    std::ifstream ifs(filename);
    if (!ifs.is_open()) {
      std::cerr << "Could not open file: '" << filename << "'\n";
      throw new std::invalid_argument("invalid filename\n");
    }
    
    while (ifs >> s) {
      if (s != "-") { pqheap.insert(s);
      } else {
        std::cout << pqheap.del_max() << " ";
      }
    }
    std::cout << "\t(" << pqheap.size() << " left on the heap)\n\n";
    ifs.close();
  }


private:
  static const size_t MIN_CAPACITY_;
  
  void exchange(size_t i, size_t j) {
    T temp = pq_[i];
    pq_[i] = pq_[j];
    pq_[j] = temp;
  }
  bool less(size_t i, size_t j) {
    return ::less(pq_[i], pq_[j], comp);
  }
  
  bool is_max_heap() const {
    size_t n = size();
    for (size_t i = 0; i < n; ++i) {
      if (pq_[i] == T()) { return false; }
    }
    for (size_t i = n + 1; i < size(); ++i) {
      if (pq_[i] != T()) { return false; }
    }
    if (pq_[0] != T()) { return false; }
    return is_max_heap_ordered(1);
  }

  bool is_max_heap_ordered(size_t k) {
    size_t n = size();
    if (k > n) { return true; }
    size_t left = 2 * k;
    size_t right = left + 1;
    
    if (left  <= n && less(k, left))  { return false; }
    if (right <= n && less(k, right)) { return false; }

    return is_max_heap_ordered(left) && is_max_heap_ordered(right);
  }
  
private:
  array_<T> pq_;                // uses expandable array from array.h, not std::array<T>
  const comparator<T>& comp;
};

#endif /* max_pq_heap_h */
