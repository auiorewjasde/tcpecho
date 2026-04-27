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
	inet_pton(AF_INET, SERVERIP, &addr.sin_addr);

	if( connect(sd, (struct sockaddr *)&addr, sizeof(struct sockaddr_in)) < 0 ){
		perror("connect");
		return -1;
	}

	if( scanf(SCANFTXT,buf) != 1 ){
		fprintf(stderr, "input error\n");
		return -1;
	}
	printf("--> %s\n", buf);
	len = strnlen(buf, 16);
	if(send(sd, buf, len, 0) < 0) {
		perror("cannot send()");
		return -1;
	}
	if((len=recv(sd, buf, BUFSIZE, 0)) < 0) {
		perror("cannot recv()");
		return -1;
	}
	buf[len]='\0';
	printf("<-- %s\n", buf);

	close(sd);

	return 0;
}
