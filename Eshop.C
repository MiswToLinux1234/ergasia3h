#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <time.h>

#define PORT 8080
#define MAX_PRODUCTS 20
#define MAX_PELATES 5
#define AITHMATA_ANA_PELATH 10
#define SERVER_IP "127.0.0.1"

// Δομή προϊόντος
typedef struct {
    char perigrafh[50];
    float timh;
    int item_c;
    int item_r;
    int item_s;
    char failed_c[MAX_CLIENTS * AITHMATA_ANA_PELATH][50];
    int failed_cnt;
} Product;

Product catalog[MAX_PRODUCTS];
pthread_mutex_t lock;

// Αρχικοποίηση καταλόγου προϊόντων
void arxikopoihsh_catalog() {
    for (int i = 0; i < MAX_PRODUCTS; i++) {
        printf(catalog[i].perigrafh, "Product_%d", i);
        catalog[i].timh = (rand() % 1000) / 10.0;
        catalog[i].item_c = 2;
        catalog[i].item_r = 0;
        catalog[i].item_s = 0;
        catalog[i].failed_cnt = 0;
    }
}

// Επεξεργασία παραγγελίας
void diax_paraggelias(int cl_socket, int product_id, char *cl_name) {
    char apanthsh[1024];

    pthread_mutex_lock(&lock);
    
    if (product_id < 0 || product_id >= MAX_PRODUCTS) {
        printf(apanthsh, sizeof(apanthsh), "Invalid product ID.");
    } else {
        Product *product = &catalog[product_id];
        product->item_r++;

        if (product->item_count > 0) {
            product->item_c--;
            product->item_s++;
            printf(apanthsh, sizeof(apanthsh), "H paraggelias einai epityxhs. %f", product->timh);
        } else {
            printf(apanthsh, sizeof(apanthsh), "Product not available.");
            strcpy(product->failed_c[product->failed_cnt++], cl_name);
        }
    }
    pthread_mutex_unlock(&lock);

    send(cl_socket, apanthsh, strlen(apanthsh), 0);
    sleep(1);  // Xronos anamonhs
}

// Συναρτηση χειρισμού πελάτη
void *diax_pelath(void *socket_desc) {
    int cl_socket = *(int *)socket_desc;
    char buffer[1024] = {0};
    char cl_name[50];
    read(cl_socket, cl_name, 50);
    for (int i = 0; i < AITHMATA_ANA_PELATH; i++) {
        memset(buffer, 0, sizeof(buffer));
        read(cl_socket, buffer, 1024);
        int product_id = atoi(buffer);
        diax_paraggelias(cl_socket, product_id, cl_name);
    }
    close(cl_socket);
    free(socket_desc);
    return NULL;
}

// Diergasia Pelath
void *client_thread(void *arg) {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};
    char cl_name[50];
    printf(cl_name, sizeof(cl_name), "Pelaths_%ld", (long)arg);

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Apetyxe h dhmiourgia socket\n");
        exit(APOTYXIA_EXIT);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, SERVER_IP, &serv_addr.sin_addr) <= 0) {
       perror("Den yposthrizetai h syndesh \n");
        exit(APOTYXIA_EXIT);
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
       perror("Apetyxe h syndesh");
        exit(APOTYXIA_EXIT);
    }

    send(sock, cl_name, strlen(cl_name), 0);
    sleep(1);

    for (int i = 0; i < AITHMATA_ANA_PELATH; i++) {
        int product_id = rand() % MAX_PRODUCTS;
        printf(buffer, sizeof(buffer), "%d", product_id);
        send(sock, buffer, strlen(buffer), 0);
        memset(buffer, 0, sizeof(buffer));
        read(sock, buffer, 1024);
        printf("%s received: %s\n", client_name, buffer);
        sleep(1);
    }
    close(sock);
    return NULL;
}

int main() {
    srand(time(NULL));
    arxikopoihsh_catalog();
    pthread_mutex_init(&lock, NULL);

    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    
    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, MAX_CLIENTS);
    
    pthread_t clients[MAX_PELATES];
    for (long i = 0; i < MAX_PELATES; i++) {
        pthread_create(&pelates[i], NULL, client_thread, (void *)i);
    }

    while (1) {
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        pthread_t thread;
        int *new_sock = malloc(sizeof(int));
        *new_sock = new_socket;
        pthread_create(&thread, NULL, diax_pelath, (void*) new_sock);
        pthread_detach(thread);
    }
    pthread_mutex_destroy(&lock);
    return 0;
}
