/*

	PCLIENT.C - client (receive) half of named pipe demo.

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

unsigned char far *buffer;

main(argc, argv)
int argc;
char *argv[];
{
HPIPE hp;
USHORT n, action;
int i;

if(argc < 2)
	{
	printf("useage pclient \\pipe\\PIPE_NAME");
	exit(0);
	}

/* make a data buffer: */

buffer = (unsigned char far *)malloc(64000);
if(!buffer)
	{
	printf("ERROR - unable to allocate buffer space!\n");
	exit(3);
	}

/* open the pipe (server must have made it already): */

if((n = DosOpen(
		argv[1],
		&hp,
		&action,
		0L,
		FILE_NORMAL,
		FILE_OPEN,
		OPEN_ACCESS_READONLY | OPEN_SHARE_DENYNONE,
		0L
		)))
	{
	printf("ERROR %d opening pipe %s\n",n,argv[1]);
	exit(1);
	}

else{

	while(1)
		{

	/* loop until user presses the ESCape key: */

		if(kbhit())
			{
			i = getch();
			if(i == 27)break;
			}

	/* read a 64K data block: */

		if(DosRead(hp, buffer, 64000, &n))break;
		printf(".");
		}

	/* all done: close the pipe: */

	DosClose(hp);
	}

/* clean up & quit: */

free(buffer);
printf("Done!\n");
}
