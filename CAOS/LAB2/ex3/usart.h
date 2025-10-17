#include <stdint.h>

#ifndef USART_H
#define USART_H

#define USART1_BASE 0x40011000
#define TIMEOUT 1000

enum {
  USART_TX_ERROR = -1,
  USART_TX_INCOMPLETE = 0,
  USART_TX_COMPLETE = 1,
  USART_TX_BUSY = 2,
};

typedef struct {
    volatile uint32_t status_reg;
    volatile uint32_t data_reg;
} usart_reg;

static volatile usart_reg *const usart1_t = (usart_reg *)USART1_BASE;
static uint32_t usart_is_tx_ready(void);
uint32_t usart_tx_start(const uint8_t *data_bytes, uint32_t n_bytes);

#endif