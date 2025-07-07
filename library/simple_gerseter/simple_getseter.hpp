#ifndef SIMPLE_GETSETER_HPP
#define SIMPLE_GETSETER_HPP

#ifdef __PROPERTY_GETSET
#error "__PROPERTY_GETSET is defined, which is not allowed!"
#else
#define __PROPERTY_GETSET(type, value_name)      \
    inline type get_##value_name() const {       \
        return value_name;                       \
    }                                            \
    inline void set_##value_name(type __value) { \
        value_name = __value;                    \
    }
#endif

#endif // SIMPLE_GETSETER_HPP
