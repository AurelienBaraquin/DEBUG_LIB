/*
** EPITECH PROJECT, 2023
** debug_lib
** File description:
** debug
*/

#include "debug.h"

void debug_int(void *var)
{
    int *tmp = var;
    if (!tmp || !var) {
        DEBUG_MSG(RED);
        fprintf((FILE *)error_output, "%s %s variable is NULL%s\n", LRED, "int", RESET);
        return;
    }

    fprintf((FILE *)debug_output, "%s%d%s", col_deb[DEBUG_INT].str, *tmp, RESET);
}

void debug_char(void *var)
{
    char *tmp = var;

    if (!tmp || !var) {
        DEBUG_MSG(RED);
        fprintf((FILE *)error_output, "%s %s variable is NULL%s\n", LRED, "char", RESET);
        return;
    }

    fprintf((FILE *)debug_output, "%s%c%s", col_deb[DEBUG_CHAR].str, *tmp, RESET);
}

void debug_string(void *var)
{
    char *tmp = var;
    if (!tmp || !var) {
        DEBUG_MSG(RED);
        fprintf((FILE *)error_output, "%s %s variable is NULL%s\n", LRED, "String", RESET);
        return;
    }
    if (tmp == NULL) {
        DEBUG_MSG(RED);
        fprintf((FILE *)error_output, "%s NULL pointer%s\n", LRED, RESET);
    }
    else if (STRLEN(tmp) == 0) {
        DEBUG_MSG(RED);
        fprintf((FILE *)error_output, "%s Empty string%s\n", LRED, RESET);
    }
    else if (tmp[STRLEN(tmp)] != '\0') {
        DEBUG_MSG(RED);
        fprintf((FILE *)error_output, "%s String not terminated by '\\0'%s\n", LRED, RESET);
    }
    else
        fprintf((FILE *)debug_output, "%s%s%s", col_deb[DEBUG_STRING].str, tmp, RESET);
}

void debug_float(void *var)
{
    float *tmp = var;

    if (!tmp || !var) {
        DEBUG_MSG(RED);
        fprintf((FILE *)error_output, "%s %s variable is NULL%s\n", LRED, "float", RESET);
        return;
    }

    fprintf((FILE *)debug_output, "%s%f%s", col_deb[DEBUG_FLOAT].str, *tmp, RESET);
}

void debug_double(void *var)
{
    double *tmp = var;

    if (!tmp || !var) {
        DEBUG_MSG(RED);
        fprintf((FILE *)error_output, "%s %s variable is NULL%s\n", LRED, "double", RESET);
        return;
    }

    fprintf((FILE *)debug_output, "%s%f%s", col_deb[DEBUG_DOUBLE].str, *tmp, RESET);
}

void debug_array(void *var)
{
    char **tmp = var;

    if (!tmp || !var) {
        DEBUG_MSG(RED);
        fprintf((FILE *)error_output, "%s %s variable is NULL%s\n", LRED, "array", RESET);
        return;
    }
    if (!tmp[0]) {
        DEBUG_MSG(RED);
        fprintf((FILE *)error_output, "%s %s variable first element is NULL%s\n", LRED, "array", RESET);
        return;
    }
    fprintf((FILE *)debug_output, "%s%s%s", col_deb[DEBUG_ARRAY].str, "[", RESET);
    for (int i = 0; tmp[i]; i++) {
        fprintf((FILE *)debug_output, "%s%s%s", col_deb[DEBUG_ARRAY].str, tmp[i], RESET);
        if (tmp[i + 1])
            fprintf((FILE *)debug_output, "%s%s%s", col_deb[DEBUG_ARRAY].str, ", ", RESET);
    }
    fprintf((FILE *)debug_output, "%s%s%s", col_deb[DEBUG_ARRAY].str, "]", RESET);
}

void debug_2d_array(void *var)
{
    char ***tmp = var;

    if (!tmp || !var) {
        DEBUG_MSG(RED);
        fprintf((FILE *)error_output, "%s %s variable is NULL%s\n", LRED, "2d array", RESET);
        return;
    }

    fprintf((FILE *)debug_output, "%s%s%s", YELLOW, "[", RESET);
    for (int i = 0; tmp[i]; i++) {
        if (!tmp[i]) {
            DEBUG_MSG(RED);
            fprintf((FILE *)error_output, "%s %s sub-array is NULL%s\n", LRED, "2d array", RESET);
            continue;
        }

        fprintf((FILE *)debug_output, "%s%s%s", LGREEN, "[", RESET);
        for (int j = 0; tmp[i][j]; j++) {
            if (!tmp[i][j]) {
                DEBUG_MSG(RED);
                fprintf((FILE *)error_output, "%s %s value is NULL%s\n", LRED, "2d array", RESET);
                continue;
            }

            fprintf((FILE *)debug_output, "%s%s%s", col_deb[DEBUG_ARRAY].str, tmp[i][j], RESET);
            if (tmp[i][j + 1])
                fprintf((FILE *)debug_output, "%s%s%s", LGREEN, ", ", RESET);
        }
        fprintf((FILE *)debug_output, "%s%s%s", LGREEN, "]", RESET);
        if (tmp[i + 1])
            fprintf((FILE *)debug_output, "%s%s%s", LYELLOW, ", ", RESET);
    }
    fprintf((FILE *)debug_output, "%s%s%s", YELLOW, "]", RESET);
}


void debug_line(void)
{
    fprintf((FILE *)debug_output, "%s[ %s ] %s-> %sL.%d%s\n", LYELLOW, __FILE__, LRED, LYELLOW, __LINE__, RESET);
}

void debug(char *type, int nb_arg, ...)
{
    nb_arg--;
    va_list ap;
    va_start(ap, nb_arg);
    int i = 0;

    for (; debug_type[i].type; i++) {
        if (STRCMP(debug_type[i].type, type) == 0) {
            DEBUG_MSG(GREEN);
            debug_type[i].fct(va_arg(ap, void *));
            if (nb_arg > 0) {
                fprintf((FILE *)debug_output, "%s%s%s", WHITE, " | ", RESET);
                for (int j = 0; j < nb_arg; j++) {
                    debug_type[i].fct(va_arg(ap, void *));
                    if (j + 1 < nb_arg)
                        fprintf((FILE *)debug_output, "%s%s%s", WHITE, " | ", RESET);
                }
            }
            fprintf((FILE *)debug_output, "\n");
            break;
        }
    }
    va_end(ap);
}

// int main(void)
// {
//     int a = 12;
//     int inta = 12;
//     int intb = 32;
//     int intc = 56;
//     char b = 'c';
//     char *c = NULL;
//     float d = 42.42;
//     double e = 42.42;
//     char *f[] = {"Hello", "World", NULL};
//     char *g[] = {"BONJOUR", "VARRAR", "ERTYKJHG", NULL};
//     char **h[] = {f, g, NULL};
//     char *error_str = "";
//     SET_DEBUG_OUTPUT(stdout);
//     SET_ERROR_OUTPUT(stderr);
//     char *str = "Hello World\0";

//     DEBUG_STRING(c);
//     DEBUG_VAR("int", &a);
//     debug("array", 2, f, g);
//     DEBUG_LINE;
//     PRINT_VAR(error_str);
//     debug("2d_array", 1, h);
//     debug("int", 4, &a, &inta, &intb, &intc);
//     DEBUG_INT(&a);
//     DEBUG_STRING(error_str);
//     DEBUG_LINE;

//     debug("string", 3, str, c, str);

//     DEBUG_2D_ARRAY(h);
//     return (0);
// }