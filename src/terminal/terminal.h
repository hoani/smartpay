#ifndef __HOANI_TERMINAL_H__
#define __HOANI_TERMINAL_H__

#include <stdint.h>

extern const int k_invalid_id;

typedef uint16_t CardType_t;

extern const CardType_t k_card_visa;
extern const CardType_t k_card_master_card;
extern const CardType_t k_card_eftpos;

typedef uint16_t TransactionType_t;

extern const CardType_t k_tt_cheque;
extern const CardType_t k_tt_savings;
extern const CardType_t k_tt_credit;

typedef struct {
  int id;
  CardType_t card_type;
  TransactionType_t transaction_type;
} TerminalData_t;

#endif //__HOANI_TERMINAL_H__