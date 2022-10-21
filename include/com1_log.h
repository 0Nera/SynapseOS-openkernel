/**
 * @file com1_log.h
 * @author Арен Елчинян (a2.dev@yandex.com)
 * @brief Функции отладки через COM1 порт
 * @version 0.1.0
 * @date 19-10-2022
 * 
 * @copyright Арен Елчинян (c) 2022
 * 
 */


#include <ports.h>
#include <libk.h>


#ifndef	_COM1_LOG_H
#define	_COM1_LOG_H	1


#if (defined __i386__ || defined __x86_64__)

void com1_log_printf(const char *format_string, ...);

#if DEBUG
#define com1_log(M, ...)                            \
    com1_log_printf("[DEBUG]["                       \
        "%s:"                                       \
        "%s:%d]" M "\n",                           \
        __FILE__,                                   \
        __FUNCTION__,                               \
        __LINE__,                                   \
        ##__VA_ARGS__                               \
        )

#define assert(condition) if (condition){                      \
    com1_log("ASSERT FAIL");                                   \
    for(;;) {                                                  \
        halt();                                                \
    }                                                          \
} 

#define unit_test(condition, message) if ((condition) > 0){                                      \
    com1_log_printf("[TEST PASSED][%s:%s:%d]%s\n", __FILE__, __FUNCTION__, __LINE__, message);    \
} else {                                                                                \
    com1_log_printf("[TEST FAILED][%s:%s:%d]%s\n", __FILE__, __FUNCTION__, __LINE__, message);    \
}

#else

#define com1_log(M, ...)                            \
    com1_log_printf("["                             \
        "%s:%d]" M "\n",                            \
        __FUNCTION__,                               \
        __LINE__,                                   \
        ##__VA_ARGS__                               \
        )
#define assert(condition) if (condition){                      \
    com1_log("[ASSERT FAIL]");                                 \
    for(;;) {                                                  \
        halt();                                                \
    }                                                          \
} 

#define unit_test(condition, message) if ((condition) > 0) {     \
    com1_log_printf("[PASS][%s]%s\n", __FUNCTION__, message);    \
} else {                                                                                \
    com1_log_printf("[FAIL][%s]%s\n", __FUNCTION__, message);    \
}
#endif



#endif  // i386, x86_64


#endif // com1_log.h

