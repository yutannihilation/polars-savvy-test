#' @export
p01ars_dataframe <- function(...) {
  P01DataFrame(list(...))
}

#' @export
print.P01DataFrame <- function(x, ...) {
  x$print()
}
