#ifndef WHY_MATH_H
#define WHY_MATH_H

namespace why
{
    template <typename type>
    type inline get_absolute_value(type x) {return x < 0 ? -x : x;}
}

#endif