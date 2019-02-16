#Which object
OBJ = main

#source files
SOURCE = mysql_select.c

#Which commpiler
CC = gcc

#where are include files kept
INCLUDE = /usr/include/mysql

#the lib to link
LIB = mysqlclient

#where fo find the lib
LIBPATH = /usr/lib/mysql

#Option for development 
CFLAGS = -g -Wall 

#Option for release
#CFLAGS = -O -Wall -ansi

$(OBJ):$(SOURCE)
	$(CC) -o $(OBJ) $(SOURCE) $(CFLAGS) -I$(INCLUDE) -L$(LIBPATH) -l$(LIB)  -DDEBUG

clean:
	-rm -f *.o $(OBJ)




