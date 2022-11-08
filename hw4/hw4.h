/* takes in a string and returns a string with the 
capitalization of each letter flipped */
char* flip_case(char* s);

/* takes in a string, and a string to search for within that string,
and returns a list of matches in the larger string */
char** matches(char* s, char* pat, unsigned int* nmatches);

/* takes in  a takes in a list of strings and concatenates them into one 
larger string, with a specified delimiter between each string */
char* concat_strings(char** strings, unsigned int num_strings, char delim);

/* adds two values. returns an error if they cannot be added */
struct measurement add_measurements(struct measurement m1, struct measurement m2);

/* returns a copy of the measurement, with the value scaled by factor lambda */
struct measurement scale_measurement(struct measurement m, double lambda);

/* multiplies two measurements. The the resulting exponent is 
consistent with multiplying together the two values. */
struct measurement multiply_measurements(struct measurement m1, struct measurement m2);

/* return a string-formatted version of the measurement: number, a space, 
the units, and, if the exponent is not 1, a carat (^) and the exponent. */
char* measurement_tos(struct measurement m);

/* takes in a list of known conversion factors and that list's length, 
a measurement, and the units we want to convert to. 
It returns a properly-converted and labeled value.*/
struct measurement convert_units(struct conversion* conversions,
                                 unsigned int n_conversions,
                                 struct measurement m, 
                                 char* to);