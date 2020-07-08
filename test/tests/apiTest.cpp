#include "catch.hpp"
#include <cstring>
#include <iostream>
extern "C" {
#include "api.h"
#include "store.h"
#include "parserFake.h"
}

TEST_CASE( "Api GET cases", "[Api]" )
{
  char buffer[256];
  int length = 256;
  std::memset(buffer, 0, sizeof buffer);

  api_init(&ParserFake);
  store_init();

  SECTION("Api get root returns OK") {
    REQUIRE(Api.get("/", buffer, length) == API_OK);
  }

  SECTION("Api get terminals returns OK") {
    REQUIRE(Api.get("/terminals", buffer, length) == API_OK);
  }

  SECTION("Api get invalid endpoint returns invalid url") {
    REQUIRE(Api.get("/invalid", buffer, length) == API_INVALID_URL);
  }

  SECTION("Api get particular terminal returns OK") {
    TerminalData_t terminal = { 0, k_card_eftpos, k_tt_credit };
    int index = store_add(terminal);

    REQUIRE(Api.get("/terminals/0", buffer, length) == API_OK);
  }

  SECTION("Api get invalid terminal returns not found") {
    TerminalData_t terminal = { 0, k_card_eftpos, k_tt_credit };
    int index = store_add(terminal);

    REQUIRE(Api.get("/terminals/99", buffer, length) == API_NOT_FOUND);
  }
}