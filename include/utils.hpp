#ifndef UTILS_DEBUG_HPP
#define UTILS_DEBUG_HPP

#define XSTRING_UTIL__(a) STRING_UTIL__(a)
#define STRING_UTIL__(a) #a

#define assert(condition, message)\
    do{ \
        if(!(condition)){ \
            Serial.println("Échec d'assertion : " __FILE__ ":" XSTRING_UTIL__(__LINE__)); \
            Serial.println(message); \
            exit(1); \
        } \
    }while(false);

namespace utils {

/**
 * Comme map de core/arduino/WMath.cpp mais templaté.
 */
template<typename T>
T map(T x, T in_min, T in_max, T out_min, T out_max)
{
return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

} // namespace utils

#endif // UTILS_DEBUG_HPP
