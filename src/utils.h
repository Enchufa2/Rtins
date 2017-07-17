#ifndef UTILS_H
#define UTILS_H

#include <tins/tins.h>

using namespace Tins;

inline std::string get_src(const PDU* pdu) {
  switch(pdu->pdu_type()) {
  case ARP::pdu_flag:
    return ((ARP*)pdu)->sender_ip_addr().to_string();
  case Dot11::pdu_flag:
    return ((Dot11*)pdu)->addr1().to_string();
  case Dot3::pdu_flag:
    return ((Dot3*)pdu)->src_addr().to_string();
  case EthernetII::pdu_flag:
    return ((EthernetII*)pdu)->src_addr().to_string();
  case IP::pdu_flag:
    return ((IP*)pdu)->src_addr().to_string();
  case IPv6::pdu_flag:
    return ((IPv6*)pdu)->src_addr().to_string();
  case MPLS::pdu_flag:
    return std::to_string(((MPLS*)pdu)->label());
  case SLL::pdu_flag:
    return ((SLL*)pdu)->address().to_string();
  case TCP::pdu_flag:
    return std::to_string(((TCP*)pdu)->sport());
  case UDP::pdu_flag:
    return std::to_string(((UDP*)pdu)->sport());
  default:
    return "";
  }
}

inline std::string get_dst(const PDU* pdu) {
  switch(pdu->pdu_type()) {
  case ARP::pdu_flag:
    return ((ARP*)pdu)->target_ip_addr().to_string();
  case Dot3::pdu_flag:
    return ((Dot3*)pdu)->dst_addr().to_string();
  case EthernetII::pdu_flag:
    return ((EthernetII*)pdu)->dst_addr().to_string();
  case IP::pdu_flag:
    return ((IP*)pdu)->dst_addr().to_string();
  case IPv6::pdu_flag:
    return ((IPv6*)pdu)->dst_addr().to_string();
  case TCP::pdu_flag:
    return std::to_string(((TCP*)pdu)->dport());
  case UDP::pdu_flag:
    return std::to_string(((UDP*)pdu)->dport());
  default:
    return "";
  }
}

#endif