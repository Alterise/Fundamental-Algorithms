#pragma once

template<typename T>
class strategy
{
public:
    virtual int compare(const T&, const T&) = 0;
};