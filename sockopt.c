#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <string.h>
#include <stdio.h>


#define CMSG_IPV6_HOPLIMIT(msg)  (*(int*)get_ancillary_attr(msg, IPPROTO_IPV6, IPV6_HOPLIMIT))
#define CMSG_IPV6_DSCP(msg)  (*(int*)get_ancillary_attr(msg, IPPROTO_IPV6, IPV6_TCLASS))
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
void* get_ancillary_attr(struct msghdr* msg, int cmsg_lvl, int cmsg_type)
{
    struct cmsghdr *cmsg;
    cmsg = CMSG_FIRSTHDR(msg);

    while(cmsg != NULL)
    {
        if ((cmsg->cmsg_level == cmsg_lvl) &&
            (cmsg->cmsg_type == cmsg_type))
        {
            return (void*)CMSG_DATA(cmsg);
        }
        cmsg = CMSG_NXTHDR(msg, cmsg);
    }
    fprintf(stderr,"ERROR: ATTRIBUTE NOT FOUND!");
	return NULL;
}


#define CMSG_SET_IPV6_HOPLIMIT(msg, hoplim) set_ancillary_attr(msg, IPPROTO_IPV6, IPV6_HOPLIMIT, &hoplim, sizeof(uint32_t))
#define CMSG_SET_IPV6_DSCP(msg, dscp)       set_ancillary_attr(msg, IPPROTO_IPV6, IPV6_TCLASS, &dscp, sizeof(uint32_t))

void set_ancillary_attr(struct msghdr* msg, uint32_t cmsg_lvl,
                uint32_t cmsg_type, void* cmsg_data, uint32_t cmsg_len)
{
    struct cmsghdr *cmsg;
    cmsg = CMSG_FIRSTHDR(msg);
    void* value_p;

    if (cmsg == NULL)
        fprintf(stderr,"ERROR: No CMSG buffer allocated! ");
    while(cmsg->cmsg_len > 0)
    {
        cmsg = CMSG_NXTHDR(msg, cmsg);
        if (cmsg == NULL)
            fprintf(stderr,"ERROR: Out of CMSG buffer space!");
    }
    cmsg->cmsg_level = cmsg_lvl;
    cmsg->cmsg_type = cmsg_type;
    cmsg->cmsg_len = CMSG_LEN(cmsg_len);
    value_p = (void*)CMSG_DATA(cmsg);
    memcpy(value_p, cmsg_data, cmsg_len);
}

