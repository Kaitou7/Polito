#include "usart.h"
#include <stddef.h>

static uint32_t usart_is_tx_ready(void){
    int ret = 0;

    if (usart1_t->status_reg &(1<<7))
        ret = 1;
    return ret;
}

uint32_t usart_tx_start(const uint8_t *data_bytes, uint32_t n_bytes){
    if (data_bytes == NULL)
        return USART_TX_ERROR;
    for (int i = 0; i<n_bytes; i++){
        int timeout = TIMEOUT;
        while(!usart_is_tx_ready()){
            if (timeout == 0)
                return USART_TX_BUSY;
            
            timeout--;
        }
        usart1_t->data_reg =(unsigned int) *data_bytes;
        data_bytes++;

        if (*data_bytes=='\0' && i<n_bytes-1){
                return USART_TX_INCOMPLETE;
        }
    }
    return USART_TX_COMPLETE;
}