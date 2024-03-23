
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


SEXP P01DataFrame_new__impl(SEXP x) {
    SEXP res = P01DataFrame_new(x);
    return handle_result(res);
}

SEXP P01DataFrame_print__impl(SEXP self__) {
    SEXP res = P01DataFrame_print(self__);
    return handle_result(res);
}


static const R_CallMethodDef CallEntries[] = {

    {"P01DataFrame_new__impl", (DL_FUNC) &P01DataFrame_new__impl, 1},
    {"P01DataFrame_print__impl", (DL_FUNC) &P01DataFrame_print__impl, 1},
    {NULL, NULL, 0}
};

void R_init_p01ars(DllInfo *dll) {
  R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
  R_useDynamicSymbols(dll, FALSE);
}
