#ifndef __HOANI_TERMINAL_H__
#define __HOANI_TERMINAL_H__

#include <stdint.h>

typedef uint16_t CardType_t;

const CardType_t k_card_visa = 0x0001;
const CardType_t k_card_master_card = 0x0002;
const CardType_t k_card_eftpos = 0x0004;

typedef uint16_t TransactionType_t;

const CardType_t k_tt_cheque = 0x0001;
const CardType_t k_tt_savings = 0x0002;
const CardType_t k_tt_credit = 0x0004;

typedef struct {
  int id;
  CardType_t card_type;
  TransactionType_t transaction_type;
} TerminalData_t;

#endif //__HOANI_TERMINAL_H__