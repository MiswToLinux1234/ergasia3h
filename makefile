CC = gcc
CFLAGS = Wall -pthread
LDFLAGS = 
EXEC = server
SRCS = Eshop.c
OBJS = $(SRCS: .c = .o)

#kanonas gia metaglwtissh kai syndesh
all: $(EXEC)

#Kanonas dhmiourgias ektelesiou arxeiou
$(EXEC); $(OBJS)
  $(CC) $(OBJS) -o $(EXEC) $(LDFLAGS)
  
#Metaglwtissh apo .c se .o antikeimeno 
  
  %.o: %.c
   $(CC) $(CFLAGS) -c $< -o $@
   
#Katharismos arxeiou kai tou ektelsimou
   
   clean: 
   rm -f $(OBJS) $(EXEC)
   
#Ektelesh arxeiou

   run: $(EXEC)
    ./$(EXEC)
