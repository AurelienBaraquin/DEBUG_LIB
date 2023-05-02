/*
** EPITECH PROJECT, 2023
** debug_lib
** File description:
** debug
*/

#ifndef DEBUG_H_
    #define DEBUG_H_

    #include <stdbool.h>
    #include <stddef.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <stdio.h>
    #include <fcntl.h>
    #include <sys/stat.h>
    #include <sys/types.h>
    #include <stdarg.h>

    #ifndef COLORS
        #define RED "\033[0;31m"
        #define GREEN "\033[0;32m"
        #define YELLOW "\033[0;33m"
        #define BLUE "\033[0;34m"
        #define PURPLE "\033[0;35m"
        #define CYAN "\033[0;36m"
        #define WHITE "\033[0;37m"
        #define GREY "\033[0;90m"
        #define LRED "\033[0;91m"
        #define LGREEN "\033[0;92m"
        #define LYELLOW "\033[0;93m"
        #define LBLUE "\033[0;94m"
        #define LPURPLE "\033[0;95m"
        #define LCYAN "\033[0;96m"
        #define LWHITE "\033[0;97m"

        #define COLORS const char *colors[] = {RED,         \
        GREEN, YELLOW, BLUE, PURPLE, CYAN, WHITE,       \
        GREY, LRED, LGREEN, LYELLOW, LBLUE, LPURPLE,    \
        LCYAN, LWHITE, NULL}
    #endif /* !COLORS */

    #ifndef RESET
        #define RESET "\033[0m"
    #endif /* !RESET */

    #ifndef TEXT_STYLE
        #define ITALIC "\033[3m"
        #define RITALIC "\033[23m"
        #define BOLD "\033[1m"
        #define RBOLD "\033[21m"
        #define UNDERLINE "\033[4m"
        #define BLINK "\033[5m"
        #define REVERSE "\033[7m"
        #define HIDDEN "\033[8m"

        #define TEXT_STYLE const char *text_style[] = {ITALIC, RITALIC, BOLD, \
        RBOLD, UNDERLINE, BLINK, REVERSE, HIDDEN, NULL}
    #endif /* !TEXT_STYLE */

    #ifndef CLEAR
        #define CLEAR "\033[H\033[2J"
    #endif /* !CLEAR */




    // ------------------------------

    //NULL output without core dump
    #ifndef NULL_OUTPUT
        #define NULL_OUTPUT fopen("/dev/null", "w")
    #endif /* !NULL_OUTPUT */

    // ------------------------------




    //Others output
    #ifndef DEBUG_OUTPUT
        #define DEBUG_OUTPUT stdout
    #endif /* !DEBUG_OUTPUT */

    #ifndef ERROR_OUTPUT
        #define ERROR_OUTPUT stderr
    #endif /* !ERROR_OUTPUT */




    //      * SET OUTPUT OF DEBUG *

    //! IMPORTANT :
    // ONLY USE THE debug_output DEFINED BELOW OR THE SET_DEBUG_OUTPUT MACRO WITH THE GLOBAL VARIABLE debug_output
    // NOTE : The global variable debug_output is not coding style compliant, but the #define debug_output stdout is.
    // The global variable is more flexible because you can reset and change the output during the program, but the #define is more secure.

    //* ------------------------------

    // #ifndef debug_output
    //     #define debug_output stdout // <- Change this to change the output of debug (default : stdout)
    // #endif /* !debug_output */

    // #ifndef error_output
    //     #define error_output stderr // <- Change this to change the output of error (default : stderr)
    // #endif /* !error_output */

    //* ------------------------------

    //! USE THIS /\ (define)
    //! OR THIS  \/ (global variable)

    //* ------------------------------
    // GLOBAL VARIABLE, you need to SET_DEBUG_OUTPUT before using it

    static FILE *debug_output = NULL;
    static FILE *error_output = NULL;

    #ifndef SET_DEBUG_OUTPUT
        #define SET_DEBUG_OUTPUT(file) debug_output = file
    #endif /* !SET_DEBUG_OUTPUT */

    #ifndef RESET_DEBUG_OUTPUT
        #define RESET_DEBUG_OUTPUT debug_output = stdout
    #endif /* !RESET_DEBUG_OUTPUT */

    #ifndef SET_ERROR_OUTPUT
        #define SET_ERROR_OUTPUT(file) error_output = file
    #endif /* !SET_ERROR_OUTPUT */

    #ifndef RESET_ERROR_OUTPUT
        #define RESET_ERROR_OUTPUT error_output = stderr
    #endif /* !RESET_ERROR_OUTPUT */

    //* ------------------------------





    #ifndef DEBUG_MSG
        #define DEBUG_MSG(color)\
            if (debug_output != NULL) {\
                if (color == RED || color == LRED)\
                    fprintf(error_output, "%s[ %sDEBUG%s ] %s", LYELLOW, color, YELLOW, RESET);\
                else\
                    fprintf(debug_output, "%s[ %sDEBUG%s ] %s", LYELLOW, color, YELLOW, RESET);\
            }
    #endif /* !DEBUG_MSG */



    //    * DEBUG *   //
    void debug_int(void *var);
    void debug_char(void *var);
    void debug_string(void *var);
    void debug_float(void *var);
    void debug_double(void *var);
    void debug_array(void *var);
    void debug_2d_array(void *var);

    void debug(char *type, int nb_arg, ...);

    enum debug_type_e {
        DEBUG_INT,
        DEBUG_CHAR,
        DEBUG_STRING,
        DEBUG_FLOAT,
        DEBUG_DOUBLE,
        DEBUG_ARRAY,
    };

    typedef struct debug_type_s {
        char *type;
        void (*fct)(void *);
    } debug_type_t;

    #ifndef DEBUG
        #define DEBUG static const debug_type_t
    #endif /* !DEBUG */

    typedef struct _i_str {
        int i;
        char *str;
    } _i_str_t;

    #ifndef I_STR
        #define I_STR static const _i_str_t
    #endif /* !I_STR */

    I_STR col_deb[] = {
        {DEBUG_INT, LGREEN},
        {DEBUG_CHAR, LPURPLE},
        {DEBUG_STRING, LPURPLE},
        {DEBUG_FLOAT, LGREEN},
        {DEBUG_DOUBLE, LGREEN},
        {DEBUG_ARRAY, LPURPLE},
        {0, NULL}
    };

    DEBUG debug_type[] = {
        {"int", &debug_int},
        {"char", &debug_char},
        {"string", &debug_string},
        {"float", &debug_float},
        {"double", &debug_double},
        {"array", &debug_array},
        {"2d_array", &debug_2d_array},
        {NULL, NULL}
    };



    //    * ERROR *   //

    #define DEBUG_INT(var) debug("int", 1, var)
    #define DEBUG_CHAR(var) debug("char", 1, var)
    #define DEBUG_STRING(var) debug("string", 1, var)
    #define DEBUG_FLOAT(var) debug("float", 1, var)
    #define DEBUG_DOUBLE(var) debug("double", 1, var)
    #define DEBUG_ARRAY(var) debug("array", 1, var)
    #define DEBUG_2D_ARRAY(var) debug("2d_array", 1, var)

    #define DEBUG_VAR(type, var) debug(type, 1, var)

    #define DEBUG_LINE \
        DEBUG_MSG(YELLOW); \
        fprintf(debug_output, "%s[ %s ] %s-> %sL.%d%s\n", \
        LYELLOW, __FILE__, LRED, LYELLOW, __LINE__, RESET);

    #ifndef IS_INT
        #define IS_INT(p) \
        _Generic((p), \
            int*: 1, \
            default: 0 \
        )
    #endif /* !IS_INT */




    //    * TOOLS *   //

    #ifndef GET_VAR
        #define GET_VAR(var) #var
    #endif /* !GET_VAR */

    #ifndef PRINT_VAR
        #define PRINT_VAR(var) DEBUG_MSG(BLUE); fprintf(debug_output, "%s%s%s\n", LBLUE, GET_VAR(var), RESET)
    #endif /* !PRINT_VAR */

    #ifndef GET_TYPE
        #define GET_TYPE(var) _Generic((var), \
        int: DEBUG_INT, \
        char: DEBUG_CHAR, \
        char *: DEBUG_STRING, \
        float: DEBUG_FLOAT, \
        double: DEBUG_DOUBLE, \
        default: DEBUG_ARRAY)
    #endif /* !GET_TYPE */

    #ifndef STRCMP
        #define STRCMP(a, b) \
        ({ \
            const char *str1 = (a); \
            const char *str2 = (b); \
            int result = 0; \
            while (*str1 != '\0' || *str2 != '\0') { \
                if (*str1 != *str2) { \
                    result = (*str1 < *str2) ? -1 : 1; \
                    break; \
                } \
                str1++; \
                str2++; \
            } \
            result; \
        })
    #endif /* !STRCMP */

    #ifndef STRLEN
        #define STRLEN(str) \
        ({ \
            const char *s = (str); \
            int len = 0; \
            while (*s != '\0') { \
                len++; \
                s++; \
            } \
            len; \
        })
    #endif /* !STRLEN */

#endif /* !DEBUG_H_ */
