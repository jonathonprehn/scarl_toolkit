g++ -std=c++11 -o ./../obj/arclcli.o -c arclcli.cpp -lstdc++ 
g++ -std=c++11 -o ./../obj/arclregister.o -c arclregister.cpp -lstdc++
g++ -std=c++11 -o ./../obj/arclmemory.o -c arclmemory.cpp -lstdc++
g++ -std=c++11 -o ./../bin/arclcli.exe ./../obj/arclregister.o ./../obj/arclmemory.o ./../obj/arclcli.o -lstdc++