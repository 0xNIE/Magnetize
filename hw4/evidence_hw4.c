#include <stdlib.h>
#include <stdio.h>
#include "hw4.h"

/* evidence_flip_case: test flip_case */
void evidence_flip_case()
{
    printf("*** testing flip_case\n");
    printf("- expecting hELLO, wORLD! : %s\n", flip_case("Hello, World!"));
    printf("- expecting aBcDeFgH : %s\n", flip_case("AbCdEfGh"));
    printf("- expecting .</?}[+-!25)1`~ : %s\n", flip_case(".</?}[+-!25)1`~"));
    printf("- expecting Jon. : %s\n", flip_case("jON."));
}

/* evidence_matches: test matches */
void evidence_matches()
{
    printf("*** testing matches\n");
    unsigned int num = 0;
    char** a = matches("the thing is there, then?", "the" , &num);
    char** b = matches("Abet a botanist to bet a bit", "b?t", &num);
    char** c = matches("hello world", "?", &num);
    char** d = matches("ththe", "th?", &num);
    printf("-expecting the, the, the : %s, %s , %s\n", a[0], a[1], a[2]);
    printf("-expecting bet, bot, bet, bit : %s, %s, %s, %s\n", b[0], b[1], b[2], b[3]);
    printf("-expecting h, e, l, l, o, , w, o, r, l ,d : %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s\n", c[0], c[1], c[2], c[3], c[4], c[5], c[6], c[7], c[8], c[9], c[10]);
    printf("-expecting tht, the : %s, %s\n", d[0], d[1]);
}

/* evidence_concat_strings: test concat_strings */
void evidence_concat_strings()
{
    printf("*** testing concat_strings\n");
    char* a[4] = {"my", " name", " is", " Jon"};
    char* b[1] = {"1"};
    char* c[3] = {"he", "", "him"};
    char* d[0] = {};
    printf("- expecting my- name- is- Jon : %s\n", concat_strings(a , 4, '-'));
    printf("- expecting 1 : %s\n", concat_strings(b, 1, '?'));
    printf("- expecting he!!him : %s\n", concat_strings(c, 3, '!'));
    printf("- expecting (***literally nothing): %s\n", concat_strings(d, 0, '!'));
}

struct measurement {
    double value;
    char* units;
    unsigned int exponent;
};

/* structs for testing */
struct measurement a = { .value = 2, .units = "meter", .exponent = 2};
struct measurement b = { .value = 16, .units = "meter", .exponent = 2};
struct measurement c = { .value = 14.675, .units = "mile", .exponent = 2};
struct measurement d = { .value = 15.23, .units = "meter", .exponent = 3};
struct measurement e = { .value = 3.141, .units = "mile", .exponent = 2};
struct measurement f = { .value = 6.2, .units = "ton", .exponent = 1};
struct measurement g = { .value = 500, .units = "meter", .exponent = 1};

/* evidence_add_measurements: test add_measurements */
void evidence_add_measurements()
{
    printf("*** testing add_measurements\n");
    struct measurement ab = add_measurements(a, b);
    struct measurement ce = add_measurements(c, e);
    /* testing for errors, following two line should print error statements */
    struct measurement bd = add_measurements(b, d);
    struct measurement ac = add_measurements(a, c);
    printf("- expected two 'ERROR: Units or exponents not equal.' above");

    printf("- expecting 18.0, meter, 2 : %lf, %s, %u\n", ab.value, ab.units, ab.exponent);
    printf("- expecting 17.816, mile, 2 : %lf, %s, %u\n", ce.value, ce.units, ce.exponent);
}

/* evidence_scale_measurement: test scale_measurement */
void evidence_scale_measurement()
{
    printf("*** testing scale_measurement\n");
    struct measurement a_s = scale_measurement(a, 1.54);
    struct measurement b_s = scale_measurement(b, 0.2);
    struct measurement c_s = scale_measurement(c, 1);
    struct measurement d_s = scale_measurement(d, -0.45);
    printf("- expecting 3.08, meter, 2 : %lf, %s, %u\n", a_s.value, a_s.units, a_s.exponent);
    printf("- expecting 3.2, meter, 2 : %lf, %s, %u\n", b_s.value, b_s.units, b_s.exponent);
    printf("- expecting 14.675, mile, 2 : %lf, %s, %u\n", c_s.value, c_s.units, c_s.exponent);
    printf("- expecting -6.8535, meter, 3 : %lf, %s, %u\n", d_s.value, d_s.units, d_s.exponent);
}

/* evidence_multiply_measurements: test multiply_measurements */
void evidence_multiply_measurements()
{
    printf("*** testing multiply_measurements\n");
    struct measurement ab = multiply_measurements(a, b);
    struct measurement bd = multiply_measurements(b, d);
    struct measurement ce = multiply_measurements(c, e);
    printf("- expecting 32, meter, 4 : %lf, %s, %u\n", ab.value, ab.units, ab.exponent);
    printf("- expecting 243.68, meter, 5 : %lf, %s, %u\n", bd.value, bd.units, bd.exponent);
    printf("- expecting 46.094175, mile, 4: %lf, %s, %u\n", ce.value, ce.units, ce.exponent);

/* testing for errors, following line should print an error statement */
    struct measurement bc = multiply_measurements(b, c);
        printf("- expected 'ERROR: Units are not equal.' above");

}

/* evidence_measurement_tos: test measurement_tos */
void evidence_measurement_tos()
{
    printf("*** testing measurement_tos\n");
    printf("- expecting 2 meter^2 : %s\n", measurement_tos(a));
    printf("- expecting 16 meter^2 : %s\n", measurement_tos(b));
    printf("- expecting 14.675 mile^2 : %s\n", measurement_tos(c));
    printf("- expecting 6.2 ton : %s\n", measurement_tos(f));
}

struct conversion {
    char *from, *to;
    double mult_by;
};
struct conversion aa = {.from = "meter", .to = "mile", .mult_by = 0.000621371};
struct conversion bb = {.from = "mile", .to = "meter", .mult_by = 1609.34};
struct conversion* conv1 = {&aa, &bb};
/* evidence_convert_units: test convert_units */
void evidence_convert_units()
{
    printf("*** testing convert_units\n");
    struct measurement g_c;
    g_c = convert_units(conv1, 2, g, "mile");
    printf("- expecting 0.310686, mile, 1 : %lf, %s, %u", g_c.value, g_c.units, g_c.exponent);

}
/* main: run the evidence functions above */
int main(int argc, char *argv[])
{
    evidence_flip_case();
    evidence_matches();
    evidence_concat_strings();
    evidence_add_measurements();
    evidence_scale_measurement();
    evidence_multiply_measurements();
    evidence_measurement_tos();

    return 0;
}

