/*
 * Picviz - Parallel coordinates ploter
 * Copyright (C) 2008 Sebastien Tricaud <toady@gscore.org>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#include <picviz.h>

#define BUFSIZE 1024

int unix_server_create(void)
{
	const char *spath = "/tmp/pcvd-queue.fd";

	struct sockaddr_un local;

	int sockfd;
	int ret;
	int buflen = BUFSIZE;
	socklen_t len;
	socklen_t optlen;

	unlink(spath);

	memset(&local, 0, sizeof(local));
	local.sun_family = AF_UNIX;
	strncpy(local.sun_path, spath, sizeof(local.sun_path)-1);

	sockfd = socket(AF_UNIX, SOCK_DGRAM, 0);
	if (sockfd < 0) {
		fprintf(stderr, "Error on socket()\n");
		return sockfd;
	}

	len = strlen(local.sun_path) + sizeof(local.sun_family);
	ret = bind(sockfd, (struct sockaddr *)&local, len);
	if (ret < 0) {
		fprintf(stderr, "Error on bind()\n");
		close(sockfd);
		return ret;
	}

	setsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &buflen, optlen);

	return sockfd;
}

int main(int argc, char **argv)
{
	struct pcimage_t *image;
	int sockfd;
	ssize_t nread;
	char buf[BUFSIZE];
	socklen_t fromlen;

	fprintf(stdout, "Picviz Daemon - (C) Sebastien Tricaud 2008\n");
	fprintf(stdout, "[+] Starting\n");
	image = picviz_image_new();

	sockfd = unix_server_create();

	while (1) {
		nread = recvfrom(sockfd, buf, BUFSIZE, MSG_DONTWAIT, NULL, &fromlen);
		if ( nread >= 0 ) {
			printf("We received data\n");
		}
	}

	picviz_image_destroy(image);

	return 0;
}
