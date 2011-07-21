
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


uint32_t set_ancillary_attr(struct msghdr* msg, uint32_t cmsg_lvl,
                uint32_t cmsg_type, void* cmsg_data, uint32_t cmsg_len);


/*
 * Utility macros for above function
 * */
#define CMSG_SET_IPV6_HOPLIMIT(msg, hoplim) set_ancillary_attr(msg, IPPROTO_IPV6, IPV6_HOPLIMIT, &hoplim, sizeof(uint32_t))
#define CMSG_SET_IPV6_DSCP(msg, dscp)       set_ancillary_attr(msg, IPPROTO_IPV6, IPV6_TCLASS, &dscp, sizeof(uint32_t))

/* create_dstopt()
 * @param msg (struct msghdr*) msghdr to insert the dstopt as controldata in 
 * @param hdrbuf (void*) data buffer to hold the dstopt 
 * @param hdrbuf_len (uint32_t)	length of the data buffer
 * @param dstopt_len (uint32_t) desired length of the dest opt header
 * @param optbuf (void**) returned pointer to the option data
 *
 * @brief Example usage: 
 * 
 *	#define BUFLEN 32
 *	#define WANTED_DSTOPT_LEN 8
 *	uint32_t acclen = 0;
 *	char hbuf[BUFLEN];
 *	memset(hbuf,0,BUFLEN);
 *	void* optbuf = NULL;
 *
 *	acclen += create_dstopt(&msg, hbuf, BUFLEN, 
 *		 WANTED_DSTOPT_LEN,  &optbuf);
 *
 *	@note Remember to update the msg_controllen in the msghdr 
 *	      to the accumulated length of all options.
 *		   
 * */
int create_dstopt(struct msghdr *msg, void *hdrbuf, uint32_t hdrbuf_len, 
		uint32_t dstopt_len, void** optbuf);

