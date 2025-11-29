#pragma once
#include <array>
#include <atomic>
#include <optional>
#include <cassert>

// 高效单线程循环队列
template<typename T, size_t Capacity>
class CircularQueue
{
    static_assert(Capacity > 0, "Capacity must be greater than 0");

public:
    CircularQueue() : head_(0), tail_(0), full_(false) {}

    bool push(const T& value)
    {
        if (full_) return false; // 队列已满
        buffer_[tail_] = value;
        tail_ = (tail_ + 1) & mask();
        full_ = (tail_ == head_);
        return true;
    }

    bool push(T&& value)
    {
        if (full_) return false;
        buffer_[tail_] = std::move(value);
        tail_ = (tail_ + 1) & mask();
        full_ = (tail_ == head_);
        return true;
    }

    std::optional<T> pop()
    {
        if (empty()) return std::nullopt;
        T value = std::move(buffer_[head_]);
        head_ = (head_ + 1) & mask();
        full_ = false;
        return value;
    }

    bool empty() const { return !full_ && (head_ == tail_); }
    bool full() const { return full_; }

    size_t size() const
    {
        if (full_) return Capacity;
        return (tail_ + Capacity - head_) & mask();
    }

    void clear()
    {
        head_ = tail_ = 0;
        full_ = false;
    }

private:
    static constexpr size_t mask() { return Capacity - 1; }
    static_assert((Capacity & (Capacity - 1)) == 0, "Capacity must be power of 2 for bitmask optimization");

    std::array<T, Capacity> buffer_;
    size_t head_;
    size_t tail_;
    bool full_;
};

// ========================================================
// 可选：单生产者/单消费者多线程安全版本
template<typename T, size_t Capacity>
class SPSCQueue
{
    static_assert(Capacity > 0 && (Capacity & (Capacity - 1)) == 0, "Capacity must be power of 2");

public:
    SPSCQueue() : head_(0), tail_(0) {}

    bool push(const T& value)
    {
        size_t next = (tail_ + 1) & mask();
        if (next == head_.load(std::memory_order_acquire))
            return false; // 队满
        buffer_[tail_] = value;
        tail_ = next;
        return true;
    }

    bool push(T&& value)
    {
        size_t next = (tail_ + 1) & mask();
        if (next == head_.load(std::memory_order_acquire))
            return false;
        buffer_[tail_] = std::move(value);
        tail_ = next;
        return true;
    }

    std::optional<T> pop()
    {
        size_t h = head_.load(std::memory_order_relaxed);
        if (h == tail_)
            return std::nullopt; // 空队列
        T value = std::move(buffer_[h]);
        head_.store((h + 1) & mask(), std::memory_order_release);
        return value;
    }

    bool empty() const { return head_.load() == tail_; }

private:
    static constexpr size_t mask() { return Capacity - 1; }
    std::array<T, Capacity> buffer_;
    std::atomic<size_t> head_;
    size_t tail_;
};
