===========================
Two-Party Computation (YAO)
===========================

1. Compile:
$ make 
(Makefile produces 2pc.exe and mpc.exe)

2. Server run:
$ ./2pc.exe configs10000.txt
(configs10000.txt is a configuration file for the server run
when 10000 items are considered for two-party computation.)

3. Client run:
$ ./2pc.exe configc10000.txt
(configc10000.txt is a configuration file for the client run
when 10000 items are considered for two-party computation.)


=============================
Multi-Party Computation (GMW)
=============================

1. Compile:
$ make 
(Makefile produces 2pc.exe, mpc.exe, circtool.exe)

2. Server run:
$ ./mpc.exe mconfigs10000.txt
(mconfigs10000.txt is a configuration file for the server run
when 10000 items are considered for multi-party computation.)

3. Client run:
$ ./mpc.exe mconfigc10000.txt
(mconfigc10000.txt is a configuration file for the client run
when 10000 items are considered for multi-party computation.)


