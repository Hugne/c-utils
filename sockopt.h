
/*
 * Look for a specific ancillary data item at a specific protocol level
 * for a received packet.
 * Example:
 *
 * int ip_ttl;
 * ip_ttl = *(int*) get_ancillary_attr(msg,IPPROTO_IPV6, IPV6_HOPLIMIT);
 *
 *
 * */

void* get_ancillary_attr(struct msghdr* msg, int cmsg_lvl, int cmsg_type);

/*
 * Utility macros for above function
 * */
#define CMSG_IPV6_HOPLIMIT(msg)  (*(int*)get_ancillary_attr(msg, IPPROTO_IPV6, IPV6_HOPLIMIT))
#define CMSG_IPV6_DSCP(msg)  (*(int*)get_ancillary_attr(msg, IPPROTO_IPV6, IPV6_TCLASS))


void set_ancillary_attr(struct msghdr* msg, uint32_t cmsg_lvl,
                uint32_t cmsg_type, void* cmsg_data, uint32_t cmsg_len);


/*
 * Utility macros for above function
 * */
#define CMSG_SET_IPV6_HOPLIMIT(msg, hoplim) set_ancillary_attr(msg, IPPROTO_IPV6, IPV6_HOPLIMIT, &hoplim, sizeof(uint32_t))
#define CMSG_SET_IPV6_DSCP(msg, dscp)       set_ancillary_attr(msg, IPPROTO_IPV6, IPV6_TCLASS, &dscp, sizeof(uint32_t))


