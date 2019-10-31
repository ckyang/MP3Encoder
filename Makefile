###################################################
#
# Makefile for MP3Encoder
# Created: [Mon Oct 31 16:33:25 2019]
# Clark Yang
#
###################################################

#
# Macros
#

CC = /usr/bin/g++
CC_OPTIONS = -std=gnu++14
#LNK_OPTIONS = -L ./dylib/ -lcrypto -levent_core -levent_pthreads -levent -levent_extra -lssl 


#
# INCLUDE directories for MP3Encoder
#

INCLUDE = -I.


#
# Build MP3Encoder
#

MP3Encoder : \
		./main.o
	$(CC) $(LNK_OPTIONS) \
		./main.o\
		-o MP3Encoder

clean : 
		rm \
		./main.o\
		MP3Encoder

#
# Build the parts of MP3Encoder
#

./main.o : main.cpp
	$(CC) $(CC_OPTIONS) main.cpp -c $(INCLUDE) -o ./main.o

