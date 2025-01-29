#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT_8080
#define MAX_PRODUCTS 20
#define MAX_CLIENTS 5

typedef struct{
char perigrafh[50];
float timh;
int item_c; //metrhrhts antikeimenwn
int item_r; //zhtoumena antikeimena
int item_s; //pwlhthenta antikeimena
char failed[100][50]; // disarestimenoi
int failed_c; //disarestimenoi metrhths
} Product;

Product Katalogos[MAX_PRODUCTS];

//Arxikopoihsh katalogou

void arxikopoihsh_katalogou() 
{
for (int i=0; i< MAX_PRODUCTS; i++) 
  {
   printf(katalogos[i].perigrafh , 50 , "Product %d" , i);
   katalogos[i].timh = (rand() % 100) +1 ;
   katalogos[i].item_c =2;
   katalogos[i].item_r = 0;
   katalogos[i].item_s =0;
   katalogos[i].failed_c =0;
  }
}

//Synarthsh gia diaxeirish paraggelias apo ton pelath
void diax_parag(int cl_socket, char *cl_name) 
{
int product_id;
read(cl_socket , &product_id , sizeof(product_id));

if (product_id < 0 || product_id >= MAX_PRODUCTS) {
char error_msg[] = "Mh egkyro proion.\n";
write (cl_socket , error_msg , strlen(error_msg));
return ;
}

katalogos{product_id].item_c++ ;
if (katalogos[product_id].item_c > 0 ) {
//Se periptwsh epityxoys paraggelias
katalogos[product_id].item_c --;
katalogos[product_id].item_s++;
char epityxes_msg[100];
printf(epityxes_msg , 100 ,"H paraggelias einai epityxhs: %s" , katalogos[product_id].perigrafh , katalogos[product_id].timh);
write(cl_socket , apotyxes_msg , strlen(apotyxes_msg));
}
sleep(1);
}

//ektypwsh anaforas
void ektypwsh_anaforas() {

  printf("ektypwsh anaforas: ") ;
int synolika_r =0;
int synolikes_epit = 0;
int synolikes_apot =0;
float synoliko_eis =0;

for( int = 0; i < MAX_PRODUCTS ; i++) 
  {
printf("Proion: %s\n", katalogos[i].perigrafh) ;
printf("Aithmata : %d\n" , katalogos[i].item_r);
printf("Pwlhthenta : %d\n" , katalogos[i].item_s);
printf("Disarestimenoi pelates : ");
for (int j=0 ; j< katalogos[i].failed_c ; j++ )
{
printf("%s" , katalogos[i].failed[j]);
}

synolika_r += katalogos[i].item_r ;
synolikes_epit += katalogos[i].item_s ;
synolikes_apot += katalogos[i].failed_c;
synoliko_eis = katalogos[i].item_s * katalogos[i].timh;
}

printf("Synolika aithmata : %d\n" , synolika_r);
printf("Synolikes epityxhmenes pwlhseis: %d\n" , synolikes_epit);
printf("Synolikes apotyxhmenes : %d\n" , synolikes_apot);
printf("Synoliko eisodhma: %f\n" , synoliko_eis);
}
//main tou server
int main() {
int server_fd; 
int cl_socket;
struct sockaddr_in address;
int addrlen = sizeof(address);
//dhmiourgia socket
//Dhmiourgoume ena tcp socket gia syndesh IPv4, kai ama apotyxei h dhmiourgia emfanizei to analogo mhnyma
if (server_fd = socket(AF_INET , SOCK_STREAM, 0)) == 0 )
{
perror("apetyxe to socket");
exit(APOTYXIA_EXIT);
}
  

address.sin_family=AF_INET; //Xrhsh IPV4
address.sin_addr.s_addr = INADDR_ANY; //O server tha dexetai syndeseis apo opoiadhpote dieythynsh
address.sin_port = htons(PORT); // orizoume to port pou kaname define pio panw

//Bind 
if (bind(server_fd, (struct sockaddr *) &address , sizeof(address)) < 0) { //Me to bind syndeoume to socket sto port 8080
perror ( "Apetyxe to bind");
exit(APOTYXIA_EXIT);
}

//Listen
if (listen(server_fd,MAX_CLIENTS) < 0) { //o server akouei gia eiserxomenes syndeseis , kai emfanizei mhnyma apotyxias se periptwsh pou den akousei katholou syndeseis
perror("Listen failed");
exit(APOTYXIA_EXIT);
}
arxikopoihsh_katalogou();
printf("O server trexei sto %d\n ", PORT);

while(1) {
if((cl_socket =accept(server_fd , (struct sockaddr* )&address , (socklen_t *)&addrlen)) <0 ) { //dexetai syndesh apo pelath kai epistrefei to socket
perror("Apetyxe to accept");
exit(APOTYXIA_EXIT);
}

char cl_onoma[50];
read(cl_socket, cl_onoma , sizeof(cl_onoma));
printf("Syndethhke me ton pelath: %s\n",cl_onoma); // Mhnyma epityxias ston pelath

for (int i=0; i< 10; i++) {
diax_paraggelias(cl_socket , cl_onoma);
}
close(cl_socket);
}
ektypwsh_anaforas();
return 0;
}
