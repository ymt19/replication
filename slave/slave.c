#include <stdio.h>
#include <stdlib.h>

#include "../slave/async_reciever.h"
#include "../slave/semisync_reciever.h"

#define ASYNC       1
#define SEMISYNC    2

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("<slave_id>\n");
    }

    int slave_id;
    slave_id = atoi(argv[1]);

    // reciever起動
    #if REPLICATION == ASYNC
    printf("Asynchronous replication...\n");
    async_reciever(slave_id);
    #elif REPLICATION == SEMISYNC
    printf("SEMIsynchronous replication...\n");
    semisync_reciever(slave_id);
    #endif
}