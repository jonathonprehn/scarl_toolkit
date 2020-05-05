gcc -o ./../obj/arclcli.o -c arclcli.c
gcc -o ./../obj/arclregister.o -c arclregister.c
gcc -o ./../obj/arclmemory.o -c arclmemory.c
gcc -o ./../bin/arclcli.exe ./../obj/arclcli.o ./../obj/arclregister.o ./../obj/arclmemory.o