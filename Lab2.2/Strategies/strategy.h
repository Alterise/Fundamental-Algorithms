#pragma once

template<typename T>
class strategy
{
public:
    virtual void compare(const T&, const T&) = 0;
};