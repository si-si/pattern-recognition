
CC = gcc

LIBS = -L/usr/lib/mysql -lmysqlclient -lz -lcrypt -lnsl -lm -L/usr/lib64 -lssl -lcrypto

OBJ = main.o db.o lcs.o sort.o

.c.o:
	$(CC) -g -c $<
main: $(OBJ)
	$(CC) -g -o main $(OBJ) $(LIBS)

clean:
	rm *.o
