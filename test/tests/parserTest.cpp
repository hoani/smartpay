#include "catch.hpp"
#include <string>
extern "C" {
#include "parser.h"
#include "terminal.h"
}

TEST_CASE( "Single Terminal Encode", "[parser]" )
{
  // Setup
  int id = 3;
  CardType_t cards = k_card_visa;
  TransactionType_t transaction_type = k_tt_cheque | k_tt_savings;
  TerminalData_t terminal_data = { id, cards, transaction_type };

  char buffer[128];
  int length = 128;
  memset(buffer,'\0',length);


  SECTION("JSON Encode of Single Terminal") {

    REQUIRE(parse_terminal(terminal_data, buffer, length));

    std::string result(buffer);
    std::string expected("{\"id\":3,\"cardType\":[\"Visa\"],\"TransactionType\":[\"Cheque\",\"Savings\"]}");

    REQUIRE(result == expected);
  }

  SECTION("JSON encode big ID") {
    terminal_data.id = 1337;

    REQUIRE(parse_terminal(terminal_data, buffer, length));

    std::string result(buffer);
    std::string expected("{\"id\":1337,\"cardType\":[\"Visa\"],\"TransactionType\":[\"Cheque\",\"Savings\"]}");

    REQUIRE(result == expected);
  }

  SECTION("JSON encode card types") {
    terminal_data.card_type = k_card_master_card | k_card_eftpos;

    REQUIRE(parse_terminal(terminal_data, buffer, length));

    std::string result(buffer);
    std::string expected("{\"id\":3,\"cardType\":[\"MasterCard\",\"EFTPOS\"],\"TransactionType\":[\"Cheque\",\"Savings\"]}");

    REQUIRE(result == expected);
  }

  SECTION("JSON encode transaction types") {
    terminal_data.transaction_type = k_tt_credit;

    REQUIRE(parse_terminal(terminal_data, buffer, length));

    std::string result(buffer);
    std::string expected("{\"id\":3,\"cardType\":[\"Visa\"],\"TransactionType\":[\"Credit\"]}");

    REQUIRE(result == expected);
  }

  SECTION("JSON buffer too small") {
    length = 10;

    REQUIRE(parse_terminal(terminal_data, buffer, length) == false);
  }

  SECTION("JSON encode with empty cards") {
    terminal_data.card_type = 0;

    REQUIRE(parse_terminal(terminal_data, buffer, length));

    std::string result(buffer);
    std::string expected("{\"id\":3,\"cardType\":[],\"TransactionType\":[\"Cheque\",\"Savings\"]}");

    REQUIRE(result == expected);
  }

  SECTION("JSON encode with invalid cards") {
    terminal_data.card_type = 0xff00;

    REQUIRE(parse_terminal(terminal_data, buffer, length));

    std::string result(buffer);
    std::string expected("{\"id\":3,\"cardType\":[],\"TransactionType\":[\"Cheque\",\"Savings\"]}");

    REQUIRE(result == expected);
  }

  SECTION("JSON encode with empty transaction types") {
    terminal_data.transaction_type = 0;

    REQUIRE(parse_terminal(terminal_data, buffer, length));

    std::string result(buffer);
    std::string expected("{\"id\":3,\"cardType\":[\"Visa\"],\"TransactionType\":[]}");

    REQUIRE(result == expected);
  }

  SECTION("JSON encode with invalid transaction types") {
    terminal_data.transaction_type = 0xff00;

    REQUIRE(parse_terminal(terminal_data, buffer, length));

    std::string result(buffer);
    std::string expected("{\"id\":3,\"cardType\":[\"Visa\"],\"TransactionType\":[]}");

    REQUIRE(result == expected);
  }
}