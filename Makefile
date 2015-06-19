iou.exe : iou.o main.o
	g++ -ansi -Wall -o iou.exe main.o iou.o

main.o : main.cpp iou.h iou.cpp
	g++ -ansi -Wall -c main.cpp

iou.o : iou.h iou.cpp
	g++ -ansi -Wall -c iou.cpp

clean : 
	rm -f iou.exe iou.o main.o
