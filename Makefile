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

INCLUDE = -I.\
	-Iinc\
	-Iencoder\
	-Ifactory

#
# Build MP3Encoder
#

MP3Encoder : \
		./main.o\
		./encoder.o\
		./factory.o
		$(CC) \
		./main.o\
		./encoder.o\
		./factory.o\
		$(LNK_OPTIONS)\
		-o MP3Encoder

clean : 
		rm \
		./main.o\
		./encoder.o\
		./factory.o\
		MP3Encoder

#
# Build the parts of MP3Encoder
#

./main.o : main.cpp
	$(CC) $(CC_OPTIONS) main.cpp -c $(INCLUDE) -o ./main.o

./encoder.o : encoder/encoder.cpp
	$(CC) $(CC_OPTIONS) encoder/encoder.cpp -c $(INCLUDE) -o ./encoder.o

./factory.o : factory/factory.cpp
	$(CC) $(CC_OPTIONS) factory/factory.cpp -c $(INCLUDE) -o ./factory.o

