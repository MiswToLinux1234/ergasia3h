#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h)

#define PORT 8080

int main () {
  int cl_socket;
struct sockaddr_in serv_addr;
char cl_onoma[50];
printf("Valte onoma pelath: ");
scanf("%s", cl_onoma);

if ((cl_socket = socket(AF_INET , SOCK_STREAM , 0)) < 0) {
printf("Apetyxe h dhmiourgia tou socket" );
return -1;
}

serv_addr.sin_family = AF_INET;
serv_addr.sin_port = htons(PORT);

if (inet_pton(AF_INET , "127.0.0.1" , &serv_addr.sin_addr) <=0) {
printf("Mh egkyrh dieuthhnsh");
return -1;
}

if (connect(cl_socket , (struct sockaddr*)&serv_addr , sizeof(serv_addr)) <0) {
printf("Apetyxe h syndesh");
return -1;
}

write(cl_socket, cl_onoma , strlen(cl_onoma) +1);

 for (int i=0; i<10; i++) {
int product_id = rand() % 20;
write(cl_socket , &product_id, sizeof(product_id));
char buffer[1024] ={0};
read(cl_socket , buffer,1024);
printf("Apanthsh server: %s ", buffer);
sleep(1);
 }
close(cl_socket);
return 0;
}
