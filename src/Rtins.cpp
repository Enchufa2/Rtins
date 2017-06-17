#include "utils.h"
#include <Rcpp.h>
#include <tins/tins.h>

using namespace Rcpp;
using namespace Tins;

//[[Rcpp::export]]
DataFrame read_pcap_(std::string fname, std::string filter, unsigned int layers) {
  SnifferConfiguration config;
  config.set_filter(filter);
  FileSniffer cap(fname, config);
  
  std::vector<int> tv_sec;
  std::vector<int> tv_usec;
  std::vector<std::vector<int>> size(layers);
  std::vector<std::vector<std::string> > layer(layers);
  std::vector<std::vector<std::string> > src(layers);
  std::vector<std::vector<std::string> > dst(layers);
  std::vector<int> payload_size;
  
  for (auto& packet : cap) {
    tv_sec.push_back(packet.timestamp().seconds());
    tv_usec.push_back(packet.timestamp().microseconds());
    const PDU* pdu = packet.pdu();
    for (size_t i = 0; i < layers; i++) {
      if (pdu) {
        size[i].push_back(pdu->size());
        layer[i].push_back(Utils::to_string(pdu->pdu_type()));
        src[i].push_back(get_src(pdu));
        dst[i].push_back(get_dst(pdu));
        pdu = pdu->inner_pdu();
      } else {
        size[i].push_back(0);
        layer[i].push_back("");
        src[i].push_back("");
        dst[i].push_back("");
      }
    }
    pdu = packet.pdu()->find_pdu<RawPDU>();
    if (pdu) payload_size.push_back(pdu->size());
    else payload_size.push_back(0);
  }
  
  List cols = List::create(tv_sec, tv_usec);
  std::vector<std::string> names = {"tv_sec", "tv_usec"};
  for (size_t i = 0; i < layers; i++) {
    cols.push_back(size[i]);
    cols.push_back(layer[i]);
    cols.push_back(src[i]);
    cols.push_back(dst[i]);
    names.push_back("layer_" + std::to_string(i + 1) + "_size");
    names.push_back("layer_" + std::to_string(i + 1) + "_id");
    names.push_back("layer_" + std::to_string(i + 1) + "_src");
    names.push_back("layer_" + std::to_string(i + 1) + "_dst");
  }
  cols.push_back(payload_size);
  names.push_back("payload_size");
  cols.attr("names") = names;
  
  return DataFrame(cols);
}
