#' @export
pl <- new.env(parent = emptyenv())

pl$DataFrame <- function(...) {
  P01DataFrame(list(...))
}

#' @export
print.P01DataFrame <- function(x, ...) {
  x$print()
}
