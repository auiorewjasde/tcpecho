#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "conf.h"

int main(int argc, char** argv) {
	int sd, sd1, i, len;
	struct sockaddr_in addr;

	socklen_t sin_size = sizeof(struct sockaddr_in);
	struct sockaddr_in src_addr;

	char buf[BUFSIZE+1];

	memset(buf, 0, sizeof(buf));

	if((sd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("cannot socket");
		return -1;
	}

	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = INADDR_ANY;

	if(bind(sd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		perror("cannot bind");
		return -1;
	}

	if(listen(sd, 10) < 0) {
		perror("cannot listen");
		return -1;
	}

	if((sd1 = accept(sd, (struct sockaddr *)&src_addr, &sin_size)) < 0) {
		perror("cannot accept");
		return -1;
	}

	if((len=recv(sd1, buf, sizeof(buf), 0)) < 0) {
		perror("cannot recv");
		return -1;
	}
	printf("<-- %s\n", buf);

	for(i=0; i<len/2; i++){
		char t = buf[i];
		buf[i] = buf[len-1-i];
		buf[len-1-i] = t;
	}

	printf("--> %s\n", buf);
	if( send(sd1, buf, len, 0) < 0) {
		perror("cannot send");
		return -1;
	}

	close(sd1);
	close(sd);
	return 0;
}
