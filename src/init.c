
#include <stdint.h>
#include <Rinternals.h>
#include "rust/api.h"

static uintptr_t TAGGED_POINTER_MASK = (uintptr_t)1;

SEXP handle_result(SEXP res_) {
    uintptr_t res = (uintptr_t)res_;

    // An error is indicated by tag.
    if ((res & TAGGED_POINTER_MASK) == 1) {
        // Remove tag
        SEXP res_aligned = (SEXP)(res & ~TAGGED_POINTER_MASK);

        // Currently, there are two types of error cases:
        //
        //   1. Error from Rust code
        //   2. Error from R's C API, which is caught by R_UnwindProtect()
        //
        if (TYPEOF(res_aligned) == CHARSXP) {
            // In case 1, the result is an error message that can be passed to
            // Rf_errorcall() directly.
            Rf_errorcall(R_NilValue, "%s", CHAR(res_aligned));
        } else {
            // In case 2, the result is the token to restart the
            // cleanup process on R's side.
            R_ContinueUnwind(res_aligned);
        }
    }

    return (SEXP)res;
}

SEXP to_upper__impl(SEXP x) {
    SEXP res = to_upper(x);
    return handle_result(res);
}

SEXP int_times_int__impl(SEXP x, SEXP y) {
    SEXP res = int_times_int(x, y);
    return handle_result(res);
}

SEXP Person_new__impl(void) {
    SEXP res = Person_new();
    return handle_result(res);
}

SEXP Person_set_name__impl(SEXP self__, SEXP name) {
    SEXP res = Person_set_name(self__, name);
    return handle_result(res);
}

SEXP Person_name__impl(SEXP self__) {
    SEXP res = Person_name(self__);
    return handle_result(res);
}

SEXP Person_associated_function__impl(void) {
    SEXP res = Person_associated_function();
    return handle_result(res);
}


static const R_CallMethodDef CallEntries[] = {
    {"to_upper__impl", (DL_FUNC) &to_upper__impl, 1},
    {"int_times_int__impl", (DL_FUNC) &int_times_int__impl, 2},
    {"Person_new__impl", (DL_FUNC) &Person_new__impl, 0},
    {"Person_set_name__impl", (DL_FUNC) &Person_set_name__impl, 2},
    {"Person_name__impl", (DL_FUNC) &Person_name__impl, 1},
    {"Person_associated_function__impl", (DL_FUNC) &Person_associated_function__impl, 0},
    {NULL, NULL, 0}
};

void R_init_p01ars(DllInfo *dll) {
  R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
  R_useDynamicSymbols(dll, FALSE);
}
