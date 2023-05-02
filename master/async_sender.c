#include <stdio.h>

#include "../master/async_sender.h"
#include "../utils/config.h"

void *async_sender(config_t *config) {
    for (int i = 0; i < SLAVE_NODE_NUM; i++) {
        #if TCP
            printf("TCP%d\n", i);
        #elif COOP
            printf("COOP%d\n", i);
        #elif NOCOOP
            printf("NOCOOP%d\n", i);
        #endif
    }
}