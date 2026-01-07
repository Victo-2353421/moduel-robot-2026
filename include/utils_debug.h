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
