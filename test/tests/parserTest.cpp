#include "catch.hpp"
#include <string>
extern "C" {
#include "parser.h"
#include "terminal.h"
}

TEST_CASE( "Single Terminal Encode", "[parser]" )
{
  SECTION("JSON Encode of Single Terminal") {
    int id = 3;
    CardType_t cards = k_card_visa;
    TransactionType_t transaction_type = k_tt_cheque | k_tt_savings;
    TerminalData_t terminal_data = { id, cards, transaction_type };

    char buffer[128] = { '\0' };
    int length = 128;

    REQUIRE(parse_terminal(terminal_data, buffer, length));

    std::string result(buffer);
    std::string expected("{\"id\":3,\"cardType\":[\"Visa\"],\"TransactionType\":[\"Cheque\",\"Savings\"]}");

    REQUIRE(result == expected);
  }

  SECTION("JSON encode big ID") {
    int id = 1337;
    CardType_t cards = k_card_visa;
    TransactionType_t transaction_type = k_tt_cheque | k_tt_savings;
    TerminalData_t terminal_data = { id, cards, transaction_type };

    char buffer[128] = { '\0' };
    int length = 128;

    REQUIRE(parse_terminal(terminal_data, buffer, length));

    std::string result(buffer);
    std::string expected("{\"id\":1337,\"cardType\":[\"Visa\"],\"TransactionType\":[\"Cheque\",\"Savings\"]}");

    REQUIRE(result == expected);
  }

  SECTION("JSON encode card types") {
    int id = 3;
    CardType_t cards = k_card_master_card | k_card_eftpos;
    TransactionType_t transaction_type = k_tt_cheque | k_tt_savings;
    TerminalData_t terminal_data = { id, cards, transaction_type };

    char buffer[128] = { '\0' };
    int length = 128;

    REQUIRE(parse_terminal(terminal_data, buffer, length));

    std::string result(buffer);
    std::string expected("{\"id\":3,\"cardType\":[\"MasterCard\",\"EFTPOS\"],\"TransactionType\":[\"Cheque\",\"Savings\"]}");

    REQUIRE(result == expected);
  }

  SECTION("JSON encode transaction types") {
    int id = 3;
    CardType_t cards = k_card_master_card | k_card_eftpos;
    TransactionType_t transaction_type = k_tt_credit;
    TerminalData_t terminal_data = { id, cards, transaction_type };

    char buffer[128] = { '\0' };
    int length = 128;

    REQUIRE(parse_terminal(terminal_data, buffer, length));

    std::string result(buffer);
    std::string expected("{\"id\":3,\"cardType\":[\"MasterCard\",\"EFTPOS\"],\"TransactionType\":[\"Credit\"]}");

    REQUIRE(result == expected);
  }

  SECTION("JSON buffer too small") {
    int id = 3;
    CardType_t cards = k_card_master_card | k_card_eftpos;
    TransactionType_t transaction_type = k_tt_credit;
    TerminalData_t terminal_data = { id, cards, transaction_type };

    char buffer[10] = { '\0' };
    int length = 10;

    REQUIRE(parse_terminal(terminal_data, buffer, length) == false);
  }

  SECTION("JSON encode with empty cards") {
    int id = 3;
    CardType_t cards = 0;
    TransactionType_t transaction_type = k_tt_credit;
    TerminalData_t terminal_data = { id, cards, transaction_type };

    char buffer[128] = { '\0' };
    int length = 128;

    REQUIRE(parse_terminal(terminal_data, buffer, length));

    std::string result(buffer);
    std::string expected("{\"id\":3,\"cardType\":[],\"TransactionType\":[\"Credit\"]}");

    REQUIRE(result == expected);
  }

  SECTION("JSON encode with invalid cards") {
    int id = 3;
    CardType_t cards = 0xff00;
    TransactionType_t transaction_type = k_tt_credit;
    TerminalData_t terminal_data = { id, cards, transaction_type };

    char buffer[128] = { '\0' };
    int length = 128;

    REQUIRE(parse_terminal(terminal_data, buffer, length));

    std::string result(buffer);
    std::string expected("{\"id\":3,\"cardType\":[],\"TransactionType\":[\"Credit\"]}");

    REQUIRE(result == expected);
  }

  SECTION("JSON encode with empty transaction types") {
    int id = 3;
    CardType_t cards = k_card_master_card | k_card_eftpos;
    TransactionType_t transaction_type = 0;
    TerminalData_t terminal_data = { id, cards, transaction_type };

    char buffer[128] = { '\0' };
    int length = 128;

    REQUIRE(parse_terminal(terminal_data, buffer, length));

    std::string result(buffer);
    std::string expected("{\"id\":3,\"cardType\":[\"MasterCard\",\"EFTPOS\"],\"TransactionType\":[]}");

    REQUIRE(result == expected);
  }

  SECTION("JSON encode with invalid transaction types") {
    int id = 3;
    CardType_t cards = k_card_master_card | k_card_eftpos;
    TransactionType_t transaction_type = 0xff00;
    TerminalData_t terminal_data = { id, cards, transaction_type };

    char buffer[128] = { '\0' };
    int length = 128;

    REQUIRE(parse_terminal(terminal_data, buffer, length));

    std::string result(buffer);
    std::string expected("{\"id\":3,\"cardType\":[\"MasterCard\",\"EFTPOS\"],\"TransactionType\":[]}");

    REQUIRE(result == expected);
  }
}