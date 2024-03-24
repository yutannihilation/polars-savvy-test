#' @useDynLib p01ars, .registration = TRUE
#' @keywords internal
NULL

# Check class and extract the external pointer embedded in the environment
.savvy_extract_ptr <- function(e, class) {
  if(inherits(e, class)) {
    e$.ptr
  } else {
    msg <- paste0("Expected ", class, ", got ", class(e)[1])
    stop(msg, call. = FALSE)
  }
}



P01DataFrame <- function(x) {
  e <- new.env(parent = emptyenv())
  self <- .Call(P01DataFrame_new__impl, x)

  e$.ptr <- self
  e$print <- P01DataFrame_print(self)

  class(e) <- "P01DataFrame"
  e
}


P01DataFrame_print <- function(self) {
  function() {
    invisible(.Call(P01DataFrame_print__impl, self))
  }
}


