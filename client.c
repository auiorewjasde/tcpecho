#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "conf.h"
int main(int argc, char** argv)
{
	int sd, len;
	struct sockaddr_in addr;
	char buf[BUFSIZE+1];
 
	if((sd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("cannot socket()");
		return -1;
	}

	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = inet_addr(SERVERIP);

	connect(sd, (struct sockaddr *)&addr, sizeof(struct sockaddr_in));

	scanf(SCANFTXT,buf);
    printf("--> %s\n", buf);
	len = strnlen(buf, 16);
	if(send(sd, buf, len, 0) < 0) {
		perror("cannot send()");
	    return -1;
	}
	if((len=recv(sd, buf, sizeof(buf), 0)) < 0) {
	    perror("cannot recv()");
	    return -1;
	}
    printf("<-- %s\n", buf);

	close(sd);

	return 0;
}
