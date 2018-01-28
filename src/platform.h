#ifndef PLATFORM_H
#define PLATFORM_H

// IO
#include <stdio.h>
#define PRINTF(...) printf(__VA_ARGS__)

// TYPES

typedef unsigned int				uint32_t;
typedef short unsigned int 	uint16_t;
typedef unsigned char			uint8_t;
typedef short int int16_t;
typedef char int8_t;
/** Representing ipv6 address
 */

typedef union uip_ip6addr_t {
  uint8_t u8[16];
  uint16_t u16[8];
} uip_ip6addr_t;

typedef uip_ip6addr_t uip_ipaddr_t;


/** Timers and time constants
 */

typedef uint32_t clock_time_t;

#define CLOCK_SECOND 1000 * 1000

struct timer {
  clock_time_t start;
  clock_time_t interval;
};

clock_time_t clock_time();

// Callback timer

struct ctimer {
  struct timer timer;
  struct timer etimer;
  void (*f)(void *);
  void *ptr;
};

void ctimer_set(struct ctimer *c, clock_time_t t,
    void (*f)(void *), void *ptr);
void ctimer_stop(struct ctimer * c);
void ctimer_restart(struct ctimer * c);
void ctimer_reset(struct ctimer * c);

int etimer_expired(struct timer * t);
clock_time_t etimer_expiration_time(struct timer * t);
/**
 * Link layer
 */

typedef struct uip_eth_addr {
  uint8_t addr[6];
} uip_eth_addr;

typedef uip_eth_addr uip_lladdr_t;

#define LINKADDR_SIZE 6

typedef union {
  unsigned char u8[LINKADDR_SIZE];
  uint16_t u16;
} linkaddr_t;

extern uip_lladdr_t uip_lladdr;

struct link_stats {
  uint16_t etx;               /* ETX using ETX_DIVISOR as fixed point divisor */
  int16_t rssi;               /* RSSI (received signal strength) */
  uint8_t freshness;          /* Freshness of the statistics */
  clock_time_t last_tx_time;  /* Last Tx timestamp */
};

/* Returns the neighbor's link statistics */
const struct link_stats *link_stats_from_lladdr(const linkaddr_t *lladdr);
/* Are the statistics fresh? */
int link_stats_is_fresh(const struct link_stats *stats);

/* Initializes link-stats module */
void link_stats_init(void);
/* Packet sent callback. Updates statistics for transmissions on a given link */
void link_stats_packet_sent(const linkaddr_t *lladdr, int status, int numtx);
/* Packet input callback. Updates statistics for receptions on a given link */
void link_stats_input_callback(const linkaddr_t *lladdr);

#define uip_is_addr_unspecified(a)              \
  ((((a)->u16[0]) == 0) &&                      \
  (((a)->u16[1]) == 0) &&                       \
  (((a)->u16[2]) == 0) &&                       \
  (((a)->u16[3]) == 0) &&                       \
  (((a)->u16[4]) == 0) &&                       \
  (((a)->u16[5]) == 0) &&                       \
  (((a)->u16[6]) == 0) &&                       \
  (((a)->u16[7]) == 0))

#define uip_ip6addr(addr, addr0,addr1,addr2,addr3,addr4,addr5,addr6,addr7) do { \
  (addr)->u16[0] = UIP_HTONS(addr0);                                           \
  (addr)->u16[1] = UIP_HTONS(addr1);                                           \
  (addr)->u16[2] = UIP_HTONS(addr2);                                           \
  (addr)->u16[3] = UIP_HTONS(addr3);                                           \
  (addr)->u16[4] = UIP_HTONS(addr4);                                           \
  (addr)->u16[5] = UIP_HTONS(addr5);                                           \
  (addr)->u16[6] = UIP_HTONS(addr6);                                           \
  (addr)->u16[7] = UIP_HTONS(addr7);                                           \
  } while(0)
  
#define UIP_HTONS(a) a
  

/**
 * DS6 
 */

#define UIP_DS6_DEFAULT_PREFIX 0xfd00

#define ADDR_TENTATIVE 0
#define ADDR_PREFERRED 1
#define ADDR_AUTOCONF 1

#define UIP_DS6_ADDR_NB 1
#define UIP_CONF_MAX_ROUTES 100
#define UIP_MAX_ROUTES 100
#define UIP_DS6_ROUTE_NB UIP_CONF_MAX_ROUTES

typedef struct uip_ds6_addr {
  uint8_t isused;
  uip_ipaddr_t ipaddr;
  uint8_t state;
  uint8_t type;
  uint8_t isinfinite;
} uip_ds6_addr_t;

typedef struct uip_ds6_netif {
  uint32_t link_mtu;
  uint8_t cur_hop_limit;
  uint32_t base_reachable_time;
  uint32_t reachable_time;
  uint32_t retrans_timer;
  uint8_t maxdadns;
#if UIP_DS6_ADDR_NB 
  uip_ds6_addr_t addr_list[UIP_DS6_ADDR_NB];
#endif // UIP_DS6_ADDR_NB
} uip_ds6_netif_t;

extern uip_ds6_netif_t uip_ds6_if;

#define uip_debug_ipaddr_print(any)

typedef struct uip_ds6_route uip_ds6_route_t;

typedef struct uip_ds6_defrt {
  uip_ipaddr_t ipaddr;
  uint8_t isinfinite;
} uip_ds6_defrt_t;

typedef void (* uip_ds6_notification_callback)(int event,
  uip_ipaddr_t *route,
  uip_ipaddr_t *nexthop,
  int num_routes);

struct uip_ds6_notification {
  uip_ds6_notification_callback callback;
};
  

// functions

uip_ds6_addr_t * uip_ds_addr_lookup(uip_ipaddr_t  *ipaddr);
void uip_ds6_defrt_rm(uip_ds6_defrt_t *defrt);
int uip_ipaddr_cmp(const uip_ip6addr_t *s, const uip_ip6addr_t *d);
void uip_ds6_set_addr_iid(uip_ipaddr_t *ipaddr, uip_lladdr_t *lladdr);
uip_ds6_addr_t *uip_ds6_addr_add(uip_ipaddr_t *ipaddr, unsigned long vlifetime, uint8_t  type);
void uip_ds6_notification_add(struct uip_ds6_notification *n, uip_ds6_notification_callback c);
uip_ds6_addr_t *uip_ds6_addr_lookup(uip_ipaddr_t *ipaddr);

void uip_ds6_addr_rm(uip_ds6_addr_t *addr);

int uip_ds6_route_num_routes(void);

/*
 * Neighbors
 */

typedef struct uip_ds6_nbr {
  uip_ipaddr_t ipaddr;
  uint8_t isrouter;
  uint8_t state;
} uip_ds6_nbr_t;

typedef void nbr_table_item_t;
typedef void(nbr_table_callback)(nbr_table_item_t *item);

typedef struct nbr_table {
  int index;
  int item_size;
  nbr_table_callback *callback;
  nbr_table_item_t *data;
} nbr_table_t;

typedef enum {
  NBR_TABLE_REASON_UNDEFINED,
  NBR_TABLE_REASON_RPL_DIO,
  NBR_TABLE_REASON_RPL_DAO,
  NBR_TABLE_REASON_RPL_DIS,
  NBR_TABLE_REASON_ROUTE,
  NBR_TABLE_REASON_IPV6_ND,
  NBR_TABLE_REASON_MAC,
  NBR_TABLE_REASON_LLSEC,
  NBR_TABLE_REASON_LINK_STATS,
} nbr_table_reason_t;

#define RPL_NEIGHBORS_NUM 100
#define NBR_TABLE_MAX_NEIGHBORS RPL_NEIGHBORS_NUM
nbr_table_item_t * nbr_table_head(nbr_table_t *);
nbr_table_item_t *nbr_table_next(nbr_table_t *, nbr_table_item_t *);
nbr_table_item_t *nbr_table_add_lladdr(nbr_table_t *table, const linkaddr_t *lladdr, nbr_table_reason_t reason, void *data);
nbr_table_item_t *nbr_table_get_from_lladdr(nbr_table_t *table, const linkaddr_t *lladdr);
int uip_ds6_route_is_nexthop(const uip_ipaddr_t *ipaddr);
const uip_lladdr_t *uip_ds6_nbr_get_ll(const uip_ds6_nbr_t *nbr);
uip_ds6_nbr_t *uip_ds6_nbr_lookup(const uip_ipaddr_t *ipaddr);
const uip_lladdr_t *uip_ds6_nbr_lladdr_from_ipaddr(const uip_ipaddr_t *ipaddr);
uip_ds6_defrt_t *uip_ds6_defrt_add(uip_ipaddr_t *ipaddr,
                                   unsigned long interval);

linkaddr_t *nbr_table_get_lladdr(nbr_table_t *table, const nbr_table_item_t *item);
uip_ipaddr_t *uip_ds6_nbr_ipaddr_from_lladdr(const uip_lladdr_t *lladdr);
uip_ds6_nbr_t *uip_ds6_nbr_add(const uip_ipaddr_t *ipaddr,
                               const uip_lladdr_t *lladdr,
                               uint8_t isrouter, uint8_t state,
                               nbr_table_reason_t reason, void *data);
uip_ds6_addr_t *uip_ds6_get_link_local(int8_t state);


#define uip_ipaddr_prefixcmp(addr1, addr2, length) (memcmp(addr1, addr2, length>>3) == 0)


#define nbr_table_register(...)
extern nbr_table_t * ds6_neighbors;
extern nbr_table_t * rpl_parents;
#define uip_ds6_nbr_num() RPL_NEIGHBORS_NUM

#define ANNOTATE(...) printf(__VA_ARGS__)
#define PRINT6ADDR(...)


#define nbr_table_lock(...)
#define nbr_table_unlock(...)
#define nbr_table_remove(...)

#define uip_is_addr_linklocal(...) 1
#define UIP_DS6_NOTIFICATION_DEFRT_ADD 0
#define UIP_DS6_NOTIFICATION_DEFRT_RM 1

// RPL monikers

#define UIP_ND6_RA_FLAG_AUTONOMOUS 0x40

// UIP BUFFERS
#define ETHERNET_MTU_SIZE 2048
extern unsigned char uip_buf[ETHERNET_MTU_SIZE];
extern uint8_t uip_ext_len;
#define UIP_LLH_LEN 0

#define UIP_IPH_LEN    40
#define UIP_FRAGH_LEN  8
#define UIP_UDPH_LEN    8    /* Size of UDP header */
#define UIP_TCPH_LEN   20    /* Size of TCP header */
#define UIP_ICMPH_LEN   4    /* Size of ICMP header */

#define UIP_IPUDPH_LEN (UIP_UDPH_LEN + UIP_IPH_LEN)   /* Size of IP + UDP header */
#define UIP_IPTCPH_LEN (UIP_TCPH_LEN + UIP_IPH_LEN)   /* Size of IP + TCP header */
#define UIP_TCPIP_HLEN UIP_IPTCPH_LEN
#define UIP_IPICMPH_LEN (UIP_IPH_LEN + UIP_ICMPH_LEN) /* Size of ICMP + IP header */
#define UIP_LLIPH_LEN (UIP_LLH_LEN + UIP_IPH_LEN)     /* Size of L2 + IP header */

#define uip_l2_l3_hdr_len (UIP_LLH_LEN + UIP_IPH_LEN + uip_ext_len)
#define uip_l2_l3_icmp_hdr_len (UIP_LLH_LEN + UIP_IPH_LEN + uip_ext_len + UIP_ICMPH_LEN)
#define uip_l3_hdr_len (UIP_IPH_LEN + uip_ext_len)
#define uip_l3_icmp_hdr_len (UIP_IPH_LEN + uip_ext_len + UIP_ICMPH_LEN)

typedef struct uip_ext_hdr {
  uint8_t next;
  uint8_t len;
} uip_ext_hdr;

/* Hop by Hop option header */
typedef struct uip_hbho_hdr {
  uint8_t next;
  uint8_t len;
} uip_hbho_hdr;

/* RPL option */
typedef struct uip_ext_hdr_opt_rpl {
  uint8_t opt_type;
  uint8_t opt_len;
  uint8_t flags;
  uint8_t instance;
  uint16_t senderrank;
} uip_ext_hdr_opt_rpl;

#define UIP_EXT_HDR_OPT_RPL   0x63
uip_ds6_route_t *uip_ds6_route_lookup(uip_ipaddr_t *destipaddr);
uip_ds6_route_t *uip_ds6_route_add(uip_ipaddr_t *ipaddr, uint8_t length,
                                   uip_ipaddr_t *next_hop);
void uip_ds6_route_rm(uip_ds6_route_t *route);
void uip_ds6_route_rm_by_nexthop(uip_ipaddr_t *nexthop);

/* The IP header */
struct uip_ip_hdr {
  /* IPV6 header */
  uint8_t vtc;
  uint8_t tcflow;
  uint16_t flow;
  uint8_t len[2];
  uint8_t proto, ttl;
  uip_ip6addr_t srcipaddr, destipaddr;
};

#define PACKETBUF_ADDR_SENDER 0
const linkaddr_t *packetbuf_addr(uint8_t type);
#define UIP_PROTO_HBHO        0
#define UIP_PROTO_DESTO       60
#define UIP_PROTO_ROUTING     43
#define UIP_PROTO_FRAG        44
#define UIP_PROTO_NONE        59
extern int uip_len;
#define UIP_BUFSIZE ETHERNET_MTU_SIZE

#define uip_is_addr_mcast(a)                    \
  (((a)->u8[0]) == 0xFF)

#define uip_ds6_is_my_addr(addr)  (uip_ds6_addr_lookup(addr) != NULL)

// ICMP 6

typedef struct uip_icmp6_input_handler {
  struct uip_icmp6_input_handler *next;
  uint8_t type;
  uint8_t icode;
  void (*handler)(void);
} uip_icmp6_input_handler_t;  

#define UIP_ICMP6_HANDLER(name, type, code, func) \
  static uip_icmp6_input_handler_t name = { NULL, type, code, func }

#define ICMP6_RPL 155

#define UIP_DS6_ROUTE_STATE_TYPE rpl_route_entry_t
/* Needed for the extended route entry state when using ContikiRPL */
#define RPL_ROUTE_ENTRY_NOPATH_RECEIVED   0x01
#define RPL_ROUTE_ENTRY_DAO_PENDING       0x02
#define RPL_ROUTE_ENTRY_DAO_NACK          0x04

#define RPL_ROUTE_IS_NOPATH_RECEIVED(route)                             \
(((route)->state.state_flags & RPL_ROUTE_ENTRY_NOPATH_RECEIVED) != 0)
#define RPL_ROUTE_SET_NOPATH_RECEIVED(route) do {                       \
(route)->state.state_flags |= RPL_ROUTE_ENTRY_NOPATH_RECEIVED;      \
} while(0)
#define RPL_ROUTE_CLEAR_NOPATH_RECEIVED(route) do {                       \
(route)->state.state_flags &= ~RPL_ROUTE_ENTRY_NOPATH_RECEIVED;      \
} while(0)

#define RPL_ROUTE_IS_DAO_PENDING(route)                                 \
((route->state.state_flags & RPL_ROUTE_ENTRY_DAO_PENDING) != 0)
#define RPL_ROUTE_SET_DAO_PENDING(route) do {                           \
(route)->state.state_flags |= RPL_ROUTE_ENTRY_DAO_PENDING;          \
} while(0)
#define RPL_ROUTE_CLEAR_DAO_PENDING(route) do {                         \
(route)->state.state_flags &= ~RPL_ROUTE_ENTRY_DAO_PENDING;         \
} while(0)

#define RPL_ROUTE_IS_DAO_NACKED(route)                                  \
((route->state.state_flags & RPL_ROUTE_ENTRY_DAO_NACK) != 0)
#define RPL_ROUTE_SET_DAO_NACKED(route) do {                            \
(route)->state.state_flags |= RPL_ROUTE_ENTRY_DAO_NACK;             \
} while(0)
#define RPL_ROUTE_CLEAR_DAO_NACKED(route) do {                          \
(route)->state.state_flags &= ~RPL_ROUTE_ENTRY_DAO_NACK;            \
} while(0)

#define RPL_ROUTE_CLEAR_DAO(route) do {                                 \
(route)->state.state_flags &= ~(RPL_ROUTE_ENTRY_DAO_NACK|RPL_ROUTE_ENTRY_DAO_PENDING); \
} while(0)

struct rpl_dag;
typedef struct rpl_route_entry {
  uint32_t lifetime;
  struct rpl_dag *dag;
  uint8_t dao_seqno_out;
  uint8_t dao_seqno_in;
  uint8_t state_flags;
} rpl_route_entry_t;


typedef struct uip_ds6_route {
  uip_ipaddr_t ipaddr;
  uint8_t length;
  rpl_route_entry_t state;
} uip_ds6_route_t;

#define PRINTLLADDR(...)
#define  NBR_REACHABLE 1
uip_ipaddr_t *uip_ds6_route_nexthop(uip_ds6_route_t *);
#define uip_ipaddr_copy(dest, src) (*(dest) = *(src))
void uip_clear_buf();
void uip_icmp6_send(const uip_ipaddr_t *dest, int type, int code, int payload_len);
void uip_icmp6_register_input_handler(uip_icmp6_input_handler_t *handler);

// MRHOF

#define MIN(n, m)   (((n) < (m)) ? (n) : (m))
#define MAX(n, m)   (((n) < (m)) ? (m) : (n))

#define LINK_STATS_ETX_DIVISOR              128


// RANDOM
unsigned random_rand();
#define RANDOM_RAND_MAX (1 << 30)

// MADDR
typedef struct uip_ds6_maddr {
  uint8_t isused;
  uip_ipaddr_t ipaddr;
} uip_ds6_maddr_t;

uip_ds6_maddr_t *uip_ds6_maddr_add(const uip_ipaddr_t *ipaddr);

// ROUTE TABLE

uip_ds6_route_t *uip_ds6_route_head(void);
uip_ds6_route_t *uip_ds6_route_next(uip_ds6_route_t *);


#endif // PLATFORM_H
