#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "parser.h"

static bool add_string(char * buff, size_t length, char * str);
static bool add_start(char * buff, size_t length);
static bool add_end(char * buff, size_t length);
static bool add_comma(char * buff, size_t length);
static bool add_id(int id, char * buff, size_t length);
static bool add_card_type(CardType_t card, char * buff, size_t length);
static bool add_transaction_type(TransactionType_t tt, char * buff, size_t length);
static bool append_item(char * buff, size_t length, bool add_comma, char * name);


bool parse_terminal(TerminalData_t terminal, char * buff, size_t length) {
  if (add_start(buff, length) == false) {
    return false;
  }
  if (add_id(terminal.id, buff, length) == false) {
    return false;
  }
  if (add_comma(buff, length) == false) {
    return false;
  }
  if (add_card_type(terminal.card_type, buff, length) == false) {
    return false;
  }
  if (add_comma(buff, length) == false) {
    return false;
  }
  if (add_transaction_type(terminal.transaction_type, buff, length) == false) {
    return false;
  }

  return add_end(buff, length);
}

// Helper functions

static bool add_start(char * buff, size_t length) {
  return add_string(buff, length, "{");
}

static bool add_comma(char * buff, size_t length) {
  return add_string(buff, length, ",");
}

static bool add_end(char * buff, size_t length) {
  return add_string(buff, length, "}");
}

static bool add_id(int id, char * buff, size_t length) {
  char id_str[24] = { '\0' };
  (void) sprintf(id_str, "\"id\":%d", id);
  return add_string(buff, length, id_str);
}

static bool add_card_type(CardType_t card, char * buff, size_t length) {
  char field_str[64];
  const size_t field_length = 64;
  memset(field_str,'\0',field_length);
  bool include_comma = false;

  if (add_string(field_str, field_length, "\"cardType\":[") == false) {
    return false;
  }

  // Iterate through all card types and check if the bit fields match.
  // TODO: This data mappinng shouldn't really be defined here
  const CardType_t card_bits[3] = { k_card_visa, k_card_master_card, k_card_eftpos };
  const char names[3][16] = { "\"Visa\"", "\"MasterCard\"", "\"EFTPOS\"" };

  for (size_t i = 0; i < sizeof(card_bits); i++ ) {
    if (card & card_bits[i]) {
      if (append_item(field_str, field_length, include_comma, (char *) names[i]) == false) {
        return false;
      }
      include_comma = true;
    }
  }

  if (add_string(field_str, field_length, "]") == false) {
    return false;
  }

  return add_string(buff, length, field_str);
}

static bool add_transaction_type(TransactionType_t tt, char * buff, size_t length) {
  char field_str[64];
  const size_t field_length = 64;
  bool include_comma = false;
  memset(field_str,'\0',field_length);

  if (add_string(field_str, field_length, "\"TransactionType\":[") == false) {
    return false;
  }

  // Iterate through all transaction types and check if the bit fields match.
  // TODO: This data mappinng shouldn't really be defined here
  const TransactionType_t tt_bits[3] = { k_tt_cheque, k_tt_savings, k_tt_credit };
  const char names[3][16] = { "\"Cheque\"", "\"Savings\"", "\"Credit\"" };

  for (size_t i = 0; i < sizeof(tt_bits); i++ ) {
    if (tt & tt_bits[i]) {
      if (append_item(field_str, field_length, include_comma, (char *) names[i]) == false) {
        return false;
      }
      include_comma = true;
    }
  }

  if (add_string(field_str, field_length, "]") == false) {
    return false;
  }

  return add_string(buff, length, field_str);
}

static bool append_item(char * buff, size_t length, bool include_comma, char * name) {
  if (include_comma) {
    if (add_comma(buff, length) == false) {
      return false;
    }
  }
  if (add_string(buff, length, name) == false) {
    return false;
  }
  return true;
}

static bool add_string(char * buff, size_t length, char * str) {
  if (strlen(buff) + strlen(str) >= length) {
    return false;
  }

  strcat(buff, str);
  return true;
}
