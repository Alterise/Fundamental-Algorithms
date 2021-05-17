#pragma once

template<typename T>
class strategy
{
public:
    virtual long long compare(const T&, const T&) = 0;
};