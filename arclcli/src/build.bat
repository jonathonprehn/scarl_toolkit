g++ -o ./../obj/arclcli.o -c arclcli.cpp
g++ -o ./../obj/arclregister.o -c arclregister.cpp
g++ -o ./../obj/arclmemory.o -c arclmemory.cpp
g++ -o ./../bin/arclcli.exe ./../obj/arclcli.o ./../obj/arclregister.o ./../obj/arclmemory.o