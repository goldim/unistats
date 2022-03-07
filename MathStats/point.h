#pragma once

namespace stats
{

template<typename __X = double, typename __Y = double>
struct Point
{
    Point() = default;
    inline Point(__X _x, __Y _y){ x = _x; y = _y; }

    __X x;
    __Y y;
};

}

