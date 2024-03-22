#' @useDynLib p01ars, .registration = TRUE
#' @keywords internal
NULL

#' Convert Input To Upper-Case
#'
#' @param x A character vector.
#' @returns A character vector with upper case version of the input.
#' @export
to_upper <- function(x) {
  .Call(to_upper__impl, x)
}

#' Multiply Input By Another Input
#'
#' @param x An integer vector.
#' @param y An integer to multiply.
#' @returns An integer vector with values multiplied by `y`.
#' @export
int_times_int <- function(x, y) {
  .Call(int_times_int__impl, x, y)
}

#' A person with a name
#'
#' @export
Person <- function() {
  e <- new.env(parent = emptyenv())
  self <- .Call(Person_new__impl)

  e$set_name <- Person_set_name(self)
  e$name <- Person_name(self)
  e$associated_function <- Person_associated_function(self)

  class(e) <- "Person"
  e
}


Person_set_name <- function(self) {
  function(name) {
    invisible(.Call(Person_set_name__impl, self, name))
  }
}

Person_name <- function(self) {
  function() {
    .Call(Person_name__impl, self)
  }
}

Person_associated_function <- function(self) {
  function() {
    .Call(Person_associated_function__impl)
  }
}


