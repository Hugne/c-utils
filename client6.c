#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/ip6.h>
#include <errno.h>

#define CMSG_BUFLEN 64
#define BUFLEN 512
#define NPACK 10
#define PORT 9930
#define SRV_IP "::1"

#include "sockopt.h"


void diep(char *s)
{
        perror(s);
        exit(1);
}


/*Create a simple msghdr with one iov, and buffer for ancillary data */
void msghdr_create(struct msghdr* m, struct iovec* iov,
                   void* buffer, int buflen,
                   void* control_buf, int control_len,
                   struct sockaddr_in6* saddr)
{
        memset(m,0,sizeof(struct msghdr));
        memset(iov,0,sizeof(struct iovec));
        iov[0].iov_base = buffer;
        iov[0].iov_len = buflen;
        m->msg_iov = iov;
        m->msg_iovlen = 1;
        m->msg_name = saddr;
        m->msg_namelen = sizeof(struct sockaddr_in6);
        m->msg_control = control_buf;
        m->msg_controllen = control_len;
}


int main(void)
{
	struct sockaddr_in6 si_other;
	uint32_t s, i, slen=sizeof(si_other);
	struct msghdr msg;
	struct iovec iov;
	uint8_t buf[BUFLEN];
	uint8_t cmsgbuf[CMSG_BUFLEN];
	uint32_t on = 1;
	uint32_t acclen = 0;

	
	if ((s=socket(AF_INET6, SOCK_DGRAM, IPPROTO_UDP))==-1)
		diep("Socket");

	memset(cmsgbuf,0,CMSG_BUFLEN);
	memset((char *) &si_other, 0, sizeof(si_other));
	
	si_other.sin6_family = AF_INET6;
	si_other.sin6_port = htons(PORT);
	if (inet_pton(AF_INET6, SRV_IP, &si_other.sin6_addr) == 0) {
	fprintf(stderr, "inet_aton() failed\n");
		diep("aton");
	}

	msghdr_create(&msg, &iov, buf, BUFLEN, cmsgbuf, CMSG_BUFLEN, &si_other);

	/*Change the hoplimit*/
	uint32_t hoplimit = 5;
	acclen += CMSG_SET_IPV6_HOPLIMIT(&msg, hoplimit);

	/*Change the traffic class (dscp)*/
	uint32_t tclass = 12;
	acclen += CMSG_SET_IPV6_DSCP(&msg, tclass);

	/*Insert an empty destination options header
	(need su for this)*/
	#define EXTH_BUFLEN 32
	#define DSTOPT_LEN 8
	uint8_t ext_hdrs[EXTH_BUFLEN];
	void* optvals;
	memset(ext_hdrs, 0, EXTH_BUFLEN);
	
	acclen += create_dstopt(&msg, ext_hdrs, EXTH_BUFLEN, 
				DSTOPT_LEN, &optvals); 


	/*Update the msg_controllen with the actual length of all 
	 * ancillary data items*/
	msg.msg_controllen = acclen;

	for (i=0; i<NPACK; i++) {
	printf("Sending packet %d\n", i);
	sprintf(buf, "This is packet %d\n", i);
	if (sendmsg(s,&msg, 0 )==-1)
		diep("sendto");
	}
	
	close(s);
	return 0;
}

