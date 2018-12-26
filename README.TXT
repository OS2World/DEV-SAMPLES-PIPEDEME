The Zaphodyne Named Pipe Demo   30 May 1990

	-or-

How to send lots of data transparently between processes within
or between OS/2 workstations!

(neat stuff, what?)

This demo contains source & executable for:

	PCLIENT.EXE     (the client)
	PSERVER.EXE     (the server)

If you have MSC version 5.1 or 6.0, and the OS/2 PTK you may compile
the supplied code using the relevant .CMD files, otherwise just use
the supplied .EXE files.

First, from an OS/2 window, run PSERVER, specifying a valid OS/2 pipe name,
for example:

	pserver \pipe\test.bin

Pserver will start (unless something is drastically wrong), and put up
the message "Waiting for Connection...".  Now run PCLIENT, specifying the
same pipe name, ex:

	pclient \pipe\test.bin

Assuming nothing breaks, you'll see lots of periods on the screen - each
of which represents the end-to-end transmission of a 64K data block.  On
my machine (a 16 mhz 386XS running OS/2 v 1.2) it does one full line (80) of
these in about 10 seconds, for an effective data rate of 8 MBits/sec.

This demo _should_ work over networks, simply specify the network server
name before \pipe\, eg:

	pserver \server\pipe\test.bin

And I'd be most interested in the results with different network hardware,
please BIXmail to jruley, or EMAIL to 76227,117 on CIS.

As to the source code, it is almost trivially short, but does illustrate the
process of making a pipe, establishing a connection, transferring data, and
terminating cleanly.  Please feel free to use it as a skeleton for your own
applications!

John D. Ruley
Zaphodyne Inc.
P.O. box 1111, Fairborn OH 45324

