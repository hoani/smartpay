#include "catch.hpp"
#include <cstring>
#include <iostream>
extern "C" {
#include "store.h"
#include "terminal.h"
}

// TODO Add fields for malformed JSON - for now we will skip this case.
TEST_CASE( "Storage Terminal", "[store]" )
{
  store_init();
  SECTION("Store is empty") {
    TerminalData_t terminal;

    REQUIRE(store_count() == 0);
    REQUIRE(store_get(0, &terminal) == false);
  }

  SECTION("Store add") {
    TerminalData_t terminal = { 0, k_card_eftpos, k_tt_credit };
    int index = store_add(terminal);

    TerminalData_t stored_terminal;

    REQUIRE(store_count() == 1);
    REQUIRE(index == 0);
    REQUIRE(store_get(index, &stored_terminal) == true);
    REQUIRE(stored_terminal.id == index);
    REQUIRE(stored_terminal.card_type == terminal.card_type);
    REQUIRE(stored_terminal.transaction_type == terminal.transaction_type);
  }

  SECTION("Store add ignored id") {
    TerminalData_t terminal = { 999, k_card_eftpos, k_tt_credit };
    int index = store_add(terminal);

    TerminalData_t stored_terminal;

    REQUIRE(index == 0);
    REQUIRE(store_get(index, &stored_terminal) == true);
    REQUIRE(stored_terminal.id == index);
  }

  SECTION("Store add many") {
    TerminalData_t terminal = { 0, k_card_eftpos, k_tt_credit };
    int index = store_add(terminal);
    index = store_add(terminal);
    index = store_add(terminal);
    index = store_add(terminal);

    TerminalData_t stored_terminal;

    REQUIRE(store_count() == 4);
    REQUIRE(index == 3);
    REQUIRE(store_get(0, &stored_terminal) == true);
    REQUIRE(store_get(1, &stored_terminal) == true);
    REQUIRE(store_get(2, &stored_terminal) == true);
    REQUIRE(store_get(3, &stored_terminal) == true);
    REQUIRE(store_get(4, &stored_terminal) == false);
  }
}


