/*
 * Picviz - Parallel coordinates ploter
 * Copyright (C) 2008 Sebastien Tricaud <toady@gscore.org>
 *
 * This Code is mostly stolen from:
 * http://www.monkey.org/~provos/libevent/event-test.c
 *
 * This file is under a different license than the others:
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


#include <sys/types.h>
#include <sys/stat.h>
#ifndef WIN32
#include <sys/queue.h>
#include <unistd.h>
#include <sys/time.h>
#else
#include <windows.h>
#endif
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <event.h>

#include <picviz.h>

void
fifo_read(int fd, short event, void *arg)
{
	char buf[255];
	int len;
	struct event *ev = arg;
	struct line_t *line;
#ifdef WIN32
	DWORD dwBytesRead;
#endif

	/* Reschedule this event */
	event_add(ev, NULL);

#if 0
	fprintf(stderr, "fifo_read called with fd: %d, event: %d, arg: %p\n",
		fd, event, arg);
#endif
#ifdef WIN32
	len = ReadFile((HANDLE)fd, buf, sizeof(buf) - 1, &dwBytesRead, NULL);

	// Check for end of file.
	if(len && dwBytesRead == 0) {
		fprintf(stderr, "End Of File");
		event_del(ev);
		return;
	}

	buf[dwBytesRead + 1] = '\0';
#else
	len = read(fd, buf, sizeof(buf) - 1);

	if (len == -1) {
		perror("read");
		return;
	} else if (len == 0) {
		fprintf(stderr, "Connection closed\n");
		return;
	}

	buf[len] = '\0';
#endif
	//fprintf(stdout, "Read: %s", buf);
	line = picviz_parse_line(buf);
	printf("line id =%d\n",line->id);
}

int picviz_fifo_data_read(struct pcimage_t *image, char *filename)
{
	struct event evfifo;
#ifdef WIN32
	HANDLE socket;
	// Open a file.
	socket = CreateFile(filename,     // open File
			GENERIC_READ,                 // open for reading
			0,                            // do not share
			NULL,                         // no security
			OPEN_EXISTING,                // existing file only
			FILE_ATTRIBUTE_NORMAL,        // normal file
			NULL);                        // no attr. template

	if(socket == INVALID_HANDLE_VALUE)
		return 1;

#else
	struct stat st;
	char *fifo = filename;
	int socket;

	if (lstat (fifo, &st) == 0) {
		if ((st.st_mode & S_IFMT) == S_IFREG) {
			errno = EEXIST;
			perror("lstat");
			exit (1);
		}
	}

	unlink (fifo);
	if (mkfifo (fifo, 0600) == -1) {
		perror("mkfifo");
		exit (1);
	}

	/* Linux pipes are broken, we need O_RDWR instead of O_RDONLY */
#ifdef __linux
	socket = open (fifo, O_RDWR | O_NONBLOCK, 0);
#else
	socket = open (fifo, O_RDONLY | O_NONBLOCK, 0);
#endif

	if (socket == -1) {
		perror("open");
		exit (1);
	}

	//fprintf(stderr, "Write data to %s\n", fifo);
#endif
	/* Initalize the event library */
	event_init();

	/* Initalize one event */
#ifdef WIN32
	event_set(&evfifo, (int)socket, EV_READ, fifo_read, &evfifo);
#else
	event_set(&evfifo, socket, EV_READ, fifo_read, &evfifo);
#endif

	/* Add it to the active events, without a timeout */
	event_add(&evfifo, NULL);

	event_dispatch();
#ifdef WIN32
	CloseHandle(socket);
#endif
	return (0);
}


#ifdef _UNIT_TEST_
int main(void)
{
	picviz_fifo_data_read(NULL, "local.fifo");

	return 0;
}
#endif /* _UNIT_TEST_ */
