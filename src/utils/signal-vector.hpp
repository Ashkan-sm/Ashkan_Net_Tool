//
// Created by dev on 10/16/25.
//

#ifndef ASHKANTOOL_SIGNAL_VECTOR_HPP
#define ASHKANTOOL_SIGNAL_VECTOR_HPP
#include <condition_variable>
#include "functional"
#include <vector>
#include <memory>
#include <mutex>
#include <thread>

namespace ashk::utils {

template <typename T>
class SignalVector {
 public:
  SignalVector();
  ~SignalVector();
  void push_back(T a);
  void WaitChange();
  std::function<void()> OnChanged{[](){}};
  [[nodiscard]] const T& operator[](size_t idx) const;
  size_t size() const;

  // Iterator types
  using iterator = typename std::vector<T>::iterator;
  using const_iterator = typename std::vector<T>::const_iterator;
  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;

 private:
  std::vector<T> arr;
  std::mutex mutex_;
  std::condition_variable cnv_;
  std::unique_ptr<std::thread> thread_;
  bool alive = true;
};

template <typename T>
SignalVector<T>::SignalVector() {
  thread_ = std::make_unique<std::thread>([&]() {
    std::unique_lock<std::mutex> lock(mutex_);
    while (alive) {
      cnv_.wait(lock);
      OnChanged();
    }
  });
}

template <typename T>
void SignalVector<T>::push_back(T a) {
  {
    std::unique_lock<std::mutex> lock(mutex_);
    arr.push_back(a);
  }
  cnv_.notify_all();
}

template <typename T>
SignalVector<T>::~SignalVector() {
  alive = false;
  cnv_.notify_all();
  if (thread_->joinable()) {
    thread_->join();
  }
}

template <typename T>
void SignalVector<T>::WaitChange() {
  std::unique_lock<std::mutex> lock(mutex_);
  cnv_.wait(lock);
}

template <typename T>
typename SignalVector<T>::iterator SignalVector<T>::begin() {
  return arr.begin();
}

template <typename T>
typename SignalVector<T>::iterator SignalVector<T>::end() {
  return arr.end();
}

template <typename T>
typename SignalVector<T>::const_iterator SignalVector<T>::begin() const {
  return arr.begin();
}

template <typename T>
typename SignalVector<T>::const_iterator SignalVector<T>::end() const {
  return arr.end();
}

template <typename T>
size_t SignalVector<T>::size() const {
  return arr.size();
}

template <typename T>
const T& SignalVector<T>::operator[](size_t idx) const {
  return arr[idx];
}

} // namespace ashk::utils

#endif  // ASHKANTOOL_SIGNAL_VECTOR_HPP
