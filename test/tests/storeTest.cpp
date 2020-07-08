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
}


