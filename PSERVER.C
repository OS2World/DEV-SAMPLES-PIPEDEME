/*

	PSERVER.C - server (transmit) half of named pipe demo.

	Copyright (C) 1990, by John D. Ruley @ Zaphodyne Inc.

	Unlimited right is herewith granted to use, modify and otherwise
	exploit this software at will, however neither the author, nor
	Zaphodyne Inc. shall bear ANY responsibility for the results!

	Compile with MSC 5.1 using MKPDEMO.CMD

*/

#include <stdio.h>
#include <stdlib.h>

#define INCL_BASE
#include <os2.h>

static unsigned char far *buffer;

main(argc, argv)
int argc;
char *argv[];
{
int i;
HPIPE hp;
USHORT n;

if(argc < 2)
	{
	printf("useage pserver \\pipe\\PIPE_NAME");
	exit(0);
	}

/* make a byte-based pipe for output: */

if(( n = DosMakeNmPipe(argv[1],
		&hp,
		PIPE_ACCESS_OUTBOUND | PIPE_NOINHERIT | PIPE_NOWRITEBEHIND,
		PIPE_WAIT | PIPE_READMODE_BYTE | PIPE_TYPE_BYTE | 1,
		64000,
		0,
		1000L
		)))
	{
	printf("ERROR %d - unable to make pipe %s\n",n,argv[1]);
	exit(1);
	}

/* make a buffer for data: */

buffer = (unsigned char far *)malloc(64000);
if(!buffer)
	{
	printf("ERROR - unable to allocate buffer space!\n");
	exit(3);
	}

/* connect to the client: */

printf("Waiting for connection from client...");

if((n = DosConnectNmPipe(hp)))
	{
	printf("ERROR %d - bad connection!\n",n);
	}

else{
	printf("CONNECTED!\n");

	while(1)
		{

	/* loop until user presses ESCape: */

		if(kbhit())
			{
			i = getch();
			if(i == 27)break;
			}

	/* write 64K to the client: */

		if(DosWrite(hp, buffer, 64000, &n))break;
		printf(".");
		}

	/* done: disconnect from the client: */

	DosDisConnectNmPipe(hp);
	}

/* and clean up the mess: */

free(buffer);
printf("done!\n");
}
