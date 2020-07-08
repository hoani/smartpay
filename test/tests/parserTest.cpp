#include "catch.hpp"
#include <cstring>
#include <iostream>
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
  std::memset(buffer, 0, sizeof buffer);


  SECTION("JSON Encode of Single Terminal") {

    bool res = parse_terminal(terminal_data, buffer, length);
    std::cout << buffer << std::endl;
    REQUIRE(res);

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

TEST_CASE( "Multiple Terminal Encode", "[parser]" )
{
  // Setup
  TerminalData_t terminal_data[10] = {
    { 1, k_card_visa, k_tt_cheque },
    { 2, k_card_master_card, k_tt_savings },
    { 3, k_card_eftpos, k_tt_credit }
  };

  char buffer[256];
  int length = 256;
  std::memset(buffer, 0, sizeof buffer);

  SECTION("JSON Encode 3 Terminals") {

    REQUIRE(parse_terminal_list(terminal_data, 3, buffer, length));

    std::string result(buffer);
    std::string expected("{\"terminals\":[\
{\"id\":1,\"cardType\":[\"Visa\"],\"TransactionType\":[\"Cheque\"]},\
{\"id\":2,\"cardType\":[\"MasterCard\"],\"TransactionType\":[\"Savings\"]},\
{\"id\":3,\"cardType\":[\"EFTPOS\"],\"TransactionType\":[\"Credit\"]}\
]}");

    REQUIRE(result == expected);
  }

  SECTION("JSON Zero Terminals") {

    REQUIRE(parse_terminal_list(terminal_data, 0, buffer, length));

    std::string result(buffer);
    std::string expected("{\"terminals\":[]}");

    REQUIRE(result == expected);
  }

  SECTION("JSON Encode 1 Terminal") {

    REQUIRE(parse_terminal_list(terminal_data, 1, buffer, length));

    std::string result(buffer);
    std::string expected("{\"terminals\":[\
{\"id\":1,\"cardType\":[\"Visa\"],\"TransactionType\":[\"Cheque\"]}\
]}");

    REQUIRE(result == expected);
  }

  SECTION("JSON Encode Terminals, buffer not long enough") {

    REQUIRE(parse_terminal_list(terminal_data, 3, buffer, 32) == false);
  }
}
