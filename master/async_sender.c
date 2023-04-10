#include <stdio.h>

#include "../master/async_sender.h"

void async_sender() {
    for (int i = 0; i < SLAVE_NODE_NUM; i++) {
        #if TCP
            printf("TCP%d\n", i);
        #elif COOP
            printf("COOP%d\n", i);
        #elif NOCOOP
            printf("NOCOOP%d\n", i);
        #endif
    }
    return;
}