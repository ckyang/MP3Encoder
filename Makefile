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
LNK_OPTIONS = lib/libmp3lame.a

#
# INCLUDE directories for MP3Encoder
#

INCLUDE = -I. -Iinc/

#
# Build MP3Encoder
#

MP3Encoder : \
		./main.o
		$(CC)\
		./main.o\
		$(LNK_OPTIONS)\
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

