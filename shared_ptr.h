#pragma once
#include <iostream>

struct control_block
{
    int ref_count;
};
template <class T>
class shared_ptr
{
public:
    shared_ptr() = default;
    explicit shared_ptr(T *p) : ptr(p)
    {
        if (p)
        {
            cblock = new control_block{1};
        }
        std::cout << "带参构造" << std::endl;
    }
    // 拷贝构造
    shared_ptr(const shared_ptr &other) : ptr(other.ptr), cblock(other.cblock)
    {
        if (cblock)
        {
            ++(cblock->ref_count);
        }
        std::cout << "拷贝构造" << std::endl;
    }
    // 拷贝赋值运算符
    shared_ptr &operator=(const shared_ptr &other)
    {
        if (this != &other)
        {
            shared_ptr tmp(other);
            std::swap(ptr, tmp.ptr);
            std::swap(cblock, tmp.cblock);
        }
        std::cout << "拷贝赋值运算符" << std::endl;
        return *this;
    }
    // 移动构造
    shared_ptr(shared_ptr &&other) noexcept : ptr(other.ptr), cblock(other.cblock)
    {
        other.ptr = nullptr;
        other.cblock = nullptr;
        std::cout << "移动构造" << std::endl;
    }
    // 移动赋值运算符
    shared_ptr &operator=(shared_ptr &&other) noexcept
    {
        if (this != &other)
        {
            release();
            ptr = other.ptr;
            cblock = other.cblock;
            other.ptr = nullptr;
            other.cblock = nullptr;
        }
        std::cout << "移动赋值运算符" << std::endl;
        return *this;
    }
    // 重载 ->
    T *operator->() const
    {
        return ptr;
    }
    // 重载*
    T &operator*() const
    {
        return *ptr;
    }
    // 引用计数
    int use_count() const
    {
        return cblock ? cblock->ref_count : 0;
    }
    // 重载bool ()
    operator bool() const
    {
        return ptr != nullptr;
    }
    void reset()
    {
        release();
    }
    void reset(T *p)
    {
        release();
        ptr = p;
        if (ptr)
        {
            cblock = new control_block{1};
        }
    }
    // 构造其他类型的shared_ptr
    template <class E>
    shared_ptr(const shared_ptr<E> &other) : ptr(other.ptr), cblock(other.cblock)
    {
        if (cblock)
        {
            ++(cblock->ref_count);
        }
        std::cout << "其他类型的shared_ptr构造" << std::endl;
    }

    // 析构函数
    ~shared_ptr()
    {
        release();
        std::cout << "shared_ptr 析构" << std::endl;
    }

private:
    void release()
    {
        if (cblock)
        {
            if (--(cblock->ref_count) <= 0)
            {
                delete ptr;
                delete cblock;
            }
            ptr = nullptr;
            cblock = nullptr;
        }
    }

    T *ptr = nullptr;
    control_block *cblock = nullptr;

    template <class Y>
    friend class shared_ptr;
};

template <class T, class... Args>
shared_ptr<T> make_shared(Args &&...args)
{
    return shared_ptr<T>(new T(std::forward<Args>(args)...));
}