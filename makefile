
CC = gcc

LIBS = -L/usr/lib/mysql -lmysqlclient -lz -lcrypt -lnsl -lm -L/usr/lib64 -lssl -lcrypto

OBJ = main.o db.o

.c.o:
	$(CC) -c $<
main: $(OBJ)
	$(CC) -o main $(OBJ) $(LIBS)

clean:
	rm *.o
