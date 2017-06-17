#' @useDynLib Rtins, .registration=TRUE
#' @importFrom Rcpp evalCpp
NULL

#' Read a PCAP file
#' 
#' @param fname path to the capture file.
#' @param filter BPF filter to apply for reading the capture.
#' @param layers number of layers to decode.
#' 
#' @examples
#' ## Not run:
#' fname <- system.file("pcaps/http.cap", package="Rtins")
#' pcap <- read_pcap(fname)
#' head(pcap)
#' summary(pcap)
#' 
#' ## End(Not run)
#' @export
read_pcap <- function(fname, filter, layers=3) {
  fname <- path.expand(fname)
  stopifnot(file.exists(fname))
  stopifnot(layers > 0)
  if (missing(filter)) filter <- ""
  df <- read_pcap_(fname, filter, layers)
  class(df) <- c("pcap", class(df))
  attr(df, "fname") <- fname
  attr(df, "filter") <- filter
  attr(df, "layers") <- layers
  df
}

#' @export
summary.pcap <- function(object, ...) {
  ts_first <- object$tv_sec[[1]] + object$tv_usec[[1]]*1e-6
  ts_last <- object$tv_sec[[nrow(object)]] + object$tv_usec[[nrow(object)]]*1e-6
  ts_span <- ts_last - ts_first
  cat("File info\n",
      "  Capture file   : ", attr(object, "fname"), "\n",
      "  Filter applied : ", attr(object, "filter"), "\n",
      "  Layers decoded : ", attr(object, "layers"), "\n",
      "  Length (bytes) : ", file.size(attr(object, "fname")), "\n\n",
      "Time info\n",
      "  First packet   : ", format(as.POSIXct(ts_first, origin="1970-01-01 00:00:00", tz="UTC")), "\n",
      "  Last packet    : ", format(as.POSIXct(ts_last, origin="1970-01-01 00:00:00", tz="UTC")), "\n\n",
      "Statistics\n",
      "  Packets        : ", nrow(object), "\n",
      "  Time span (s)  : ", ts_span, "\n",
      "  Average pps    : ", nrow(object) / ts_span, "\n",
      "  Average Mbps   : ", sum(object$layer_1_size) * 8 / ts_span / 1e6,
      sep="")
}
