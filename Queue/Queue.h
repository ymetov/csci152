
#ifndef QUEUE_INCLUDED
#define QUEUE_INCLUDED 1

#include <iostream>
#include <initializer_list>

struct queue {
  size_t current_size;
  size_t current_capacity;
  size_t begin;
  size_t end;

  double *data;

  void ensure_capacity(size_t c);

  size_t next(size_t i) const {
    i = i + 1;
    if (i == current_capacity)
      i = 0;
    return i;
  }

  void checkinvariant() const;
  // Call this function often during your tests. We will
  // call it during checking!

  void printfields(std::ostream &) const;
  // Print the fields current_size, current_capacity,
  // begin, end. It should be used for debugging.

public:
  queue()
      : current_size{0}, current_capacity{50}, begin{0}, end{0},
        data{new double[50]} {}
  // Constructs empty queue.

  queue(const queue &q)
      : current_size{q.current_size}, current_capacity{q.current_capacity + 1},
        begin{q.begin}, end{q.end}, data{new double[q.current_capacity + 1]} {
    for (size_t i = q.begin, j = q.begin;
         i < q.end || (j - q.begin) < q.current_size; i++, j++)
      data[i] = q.data[i];
  }

  ~queue() { delete[] data; }

  const queue &operator=(const queue &q) {

    ensure_capacity(q.current_capacity + 1);

    for (size_t i = 0; i < q.current_size; i++)
      data[i] = q.data[i];
    current_size = q.current_size;

    begin = q.begin;
    end = q.end;
    return q;
  }

  queue(std::initializer_list<double> init)
      : current_size{init.size()}, current_capacity{init.size() + 1}, begin{0},
        end{0}, data{new double[init.size() + 1]} {

    for (double d : init) {
      data[end] = d;
      end = next(end);
    }
  }
  // So that you can write q = { 1,2,3 };
  // You can use init. size( ) to see the size, and
  // for( double d : init ) to go through all
  // elements in the initializer_list.

  void push(double d) {
    ensure_capacity(current_size + 1);
    data[end] = d;
    current_size++;
    end = next(end);
  }

  void pop() {
    begin = next(begin);
    current_size--;
  }

  void clear() {
    current_size = 0;
    begin = end = 0;
  }

  double peek() const { return data[begin]; }

  size_t size() const { return current_size; }

  bool empty() const { return current_size == 0; }

  friend std::ostream &operator<<(std::ostream &, const queue &);
};

std::ostream &operator<<(std::ostream &, const queue &);

#endif
