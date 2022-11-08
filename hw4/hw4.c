#include <string.h>
#include <stdlib.h>
#include <stdio.h>


char* flip_case(char* s) 
{
    int len = strlen(s);
    char* res = (char*)malloc(sizeof(char) * len);
    for (int i = 0; i < len; i++) {
        char x = s[i];
        if (x >= 65 && x <= 90) {
            res[i] = x + 32;
        }
        else if (x >= 97 && x <= 122) {
            res[i] = x - 32;
        }
        else {
            res[i] = s[i];
        }
    }
    return res;
}

int matches_aux(char* s, char* pat)
{
    int i = 0;
    while (pat[i] != '\0') {
        if (pat[i] == 63){
            i++;
            continue;
        }
        if (pat[i] != s[i]) {
            return 0;
        }
        i++;
    }
    return 1; 
}

char** matches(char* s, char* pat, unsigned int* nmatches)
{
    *nmatches = 0;
    int len_s = strlen(s);
    int len_pat = strlen(pat);
    char** res = (char**)malloc(sizeof(char*) * len_s);
    for (int j = 0; j < len_s; j++) {
        res[j] = (char*)malloc(sizeof(char) * len_pat);
    }
    unsigned int x = *nmatches;
    for (int i = 0; i < len_s; i++) {
        if (matches_aux(s+i, pat) == 1||pat[0] == 63) {
                res[x][0] = s[i];
                int k;
                for (k = 1; k < len_pat; k++) {
                    res[x][k] = s[i+k];
                }
                res[x][k] = '\0';
                x++;
         }
    }
            return res;
}


char* concat_strings(char** strings, unsigned int num_strings, char delim)
{
    int k = 0, chars = 0;
    for (int l = 0; l < num_strings; l++) {
        for (int y = 0; y < strlen(strings[l]); y++) {
            chars++;
        }
    }
    char *res = (char*)malloc(sizeof(char) * chars);
    for (int i = 0; i < num_strings; i++) {
        int j = 0;
        while (strings[i][j] != '\0') {
            res[k] = strings[i][j];
            k++;
            j++;
        }
        res[k] = delim;
        k++;
    }
    res[k-1] = '\0';
    return res;
}

struct measurement {
    double value;
    char* units;
    unsigned int exponent;
};

struct measurement add_measurements(struct measurement m1, struct measurement m2)
{
    if (strcmp(m1.units, m2.units) == 0&& m1.exponent == m2.exponent) {
        struct measurement res; 
        res.value = m1.value + m2.value;
        res.units = m1.units;
        res.exponent = m1.exponent;
        return res;
    } else {
        fprintf(stderr, "ERROR: Units or exponents not equal.\n");
        /* break; */
    }

}

struct measurement scale_measurement(struct measurement m, double lambda)
{
    struct measurement res;
    res.units = m.units;
    res.exponent = m.exponent;
    res.value = m.value * lambda;
    return res;
}

struct measurement multiply_measurements(struct measurement m1, struct measurement m2)
{
    if (strcmp(m1.units, m2.units) == 0){
        struct measurement res;
        res.units = m1.units;
        res.value = m1.value * m2.value;
        res.exponent = m1.exponent + m2.exponent;
    } else {
        fprintf(stderr, "ERROR: Units are not equal.\n");
        /* break; */
    }
}

char* measurement_tos(struct measurement m)
{
    char res[100];
    if (m.exponent == 1) {
        sprintf(res, "%lf %s", m.value, m.units);
    } else {
        sprintf(res, "%lf %s^%u", m.value, m.units, m.exponent);
    }
    char* result = strdup(res);
    return result;
}

struct conversion {
    char *from, *to;
    double mult_by;
};

struct measurement convert_units(struct conversion* conversions,
                                 unsigned int n_conversions,
                                 struct measurement m, 
                                 char* to)
{
    struct measurement res;
    for (int i = 0; i < n_conversions; i++){
        if (strcmp(conversions[i].from, m.units) == 0&&strcmp(conversions[i].to, to) == 0) {

            double val = m.value;
            for (int j = 0; j < m.exponent; j++) {
                val *= conversions[i].mult_by;
            }
            res.value = val;
            res.units = to;
            res.exponent = m.exponent;
        } else {
            fprintf(stderr, "ERROR: No direct conversion provided\n");
            /* break; */
        }
    }
    return res;
}