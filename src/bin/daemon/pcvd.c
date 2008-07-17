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

#include <ev.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <picviz.h>


const char *spath = "/tmp/.pcvd-queue.fd";

#define BUFSIZE 1024
#define PCVD_QUEUE_MAX 32

int unix_server_create(void)
{

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

// all watcher callbacks have a similar signature
// this callback is called when data is readable on stdin
static void
stdin_cb (EV_P_ struct ev_io *w, int revents)
{
	puts ("stdin ready");
	// for one-shot events, one must manually stop the watcher
	// with its corresponding stop function.
	ev_io_stop (EV_A_ w);

	// this causes all nested ev_loop's to stop iterating
	ev_unloop (EV_A_ EVUNLOOP_ALL);
}



int main(int argc, char **argv)
{
	struct pcimage_t *image;
	int sockfd;
#if 0
	ssize_t nread;
	char buf[BUFSIZE];
	struct sockaddr_un from;
	socklen_t fromlen;
#endif
	ev_io queue_watcher;
	struct ev_loop *loop = ev_default_loop (0);


	fprintf(stdout, "Picviz Daemon - (C) Sebastien Tricaud 2008\n");
	fprintf(stdout, "[+] Starting\n");
	image = picviz_image_new();


	//sockfd = unix_server_create();
	sockfd = open(spath, O_RDONLY | O_NONBLOCK, 0);
	ev_io_init (&queue_watcher, stdin_cb, sockfd, EV_READ);
	ev_io_start (loop, &queue_watcher);

	ev_loop (loop, 0);

	close(sockfd);
#if 0
	fromlen = sizeof(from);

	while (1) {
		nread = recvfrom(sockfd, buf, BUFSIZE, 0, (struct sockaddr *)&from, &fromlen);
		if ( nread >= 0 ) {
			printf("We received data\n");
		}
		printf(".");
		sleep(1);
	}


	unlink(spath);
	close(sockfd);
#endif
	picviz_image_destroy(image);

	return 0;
}
