cl -AL -c pserver.c
link pserver, /NOD, NUL, os2 llibcep
markexe WINDOWCOMPAT pserver.exe
cl -AL -c pclient.c
link pclient, /NOD, NUL, os2 llibcep
markexe WINDOWCOMPAT pclient.exe
