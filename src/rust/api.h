SEXP to_upper(SEXP x);
SEXP int_times_int(SEXP x, SEXP y);

// methods and associated functions for Person
SEXP Person_new(void);
SEXP Person_set_name(SEXP self__, SEXP name);
SEXP Person_name(SEXP self__);
SEXP Person_associated_function(void);