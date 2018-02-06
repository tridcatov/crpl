#ifndef UIP_H
#define UIP_H

typedef union uip_ip6addr_t {
  uint8_t u8[16];
  uint16_t u16[8];
} uip_ip6addr_t;

typedef uip_ip6addr_t uip_ipaddr_t;


#endif // UIP_H
