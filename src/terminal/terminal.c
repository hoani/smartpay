//
// Terminal - Provides a lightweight struct for representing a terminal
//


#include "terminal.h"

const int k_invalid_id = -1;

const CardType_t k_card_visa = 0x0001;
const CardType_t k_card_master_card = 0x0002;
const CardType_t k_card_eftpos = 0x0004;

const CardType_t k_tt_cheque = 0x0001;
const CardType_t k_tt_savings = 0x0002;
const CardType_t k_tt_credit = 0x0004;