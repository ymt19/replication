#include <stdio.h>
#include <pthread.h>

#include "../master/async_sender.h"
#include "../master/semisync_sender.h"
#include "../utils/config.h"

#define ASYNC       1
#define SEMISYNC    2

int main(void) {
    // sender起動
    #if REPLICATION == ASYNC
    printf("Asynchronous replication...\n");
    async_sender();
    #elif REPLICATION == SEMISYNC
    printf("SEMIsynchronous replication...\n");
    semisync_sender();
    #endif

    // client起動（ログ書き込みmaster_log.csv）
    #if REPLICATION == ASYNC
     
    #elif REPLICATION == SEMISYNC
    
    #endif

    // 終了フラグを立てる

    return 0;
}