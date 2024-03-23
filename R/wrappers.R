#' @useDynLib p01ars, .registration = TRUE
#' @keywords internal
NULL



P01DataFrame <- function(x) {
  e <- new.env(parent = emptyenv())
  self <- .Call(P01DataFrame_new__impl, x)

  e$print <- P01DataFrame_print(self)

  class(e) <- "P01DataFrame"
  e
}


P01DataFrame_print <- function(self) {
  function() {
    invisible(.Call(P01DataFrame_print__impl, self))
  }
}


