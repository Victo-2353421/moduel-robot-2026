#ifndef UTILS_HPP
#define UTILS_HPP

#include "config.hpp"

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

static constexpr uint32_t MICROSECONDES_PAR_SECONDE = 1000000;

template<typename T, typename U>
static U conversionClamp(T valeur, U min, U max) {
    static_assert(sizeof(T) < 8);
    static_assert(sizeof(U) < 8);
    if(static_cast<int64_t>(valeur) < static_cast<int64_t>(min))
        return min;
    else if(static_cast<int64_t>(max) < static_cast<int64_t>(valeur))
        return max;
    else return static_cast<U>(valeur);
}

} // namespace utils


#ifdef SERIAL_ENABLE
    #define SERIAL_BEGIN() Serial.begin(9600)
    #define PRINTLN(a) Serial.println(a)
    #define PRINT(a) Serial.print(a)
#else
    #define SERIAL_BEGIN()
    #define PRINTLN(a)
    #define PRINT(a)
#endif

#endif // UTILS_HPP
