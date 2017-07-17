// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

// read_pcap_
DataFrame read_pcap_(std::string fname, std::string filter, unsigned int layers);
RcppExport SEXP _Rtins_read_pcap_(SEXP fnameSEXP, SEXP filterSEXP, SEXP layersSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::string >::type fname(fnameSEXP);
    Rcpp::traits::input_parameter< std::string >::type filter(filterSEXP);
    Rcpp::traits::input_parameter< unsigned int >::type layers(layersSEXP);
    rcpp_result_gen = Rcpp::wrap(read_pcap_(fname, filter, layers));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_Rtins_read_pcap_", (DL_FUNC) &_Rtins_read_pcap_, 3},
    {NULL, NULL, 0}
};

RcppExport void R_init_Rtins(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
