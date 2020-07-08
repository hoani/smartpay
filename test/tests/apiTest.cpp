#include "catch.hpp"
extern "C" {
#include "api.h"
#include "parserFake.h"
}

TEST_CASE( "Api cases", "[Api]" )
{
  char buffer[256];
  int length = 256;
  std::memset(buffer, 0, sizeof buffer);

  api_init(&ParserFake);

  SECTION("Api get root returns OK") {
    REQUIRE(Api.get("/", buffer, length) == API_OK);
  }

  SECTION("Api get terminals returns OK") {
    REQUIRE(Api.get("/terminals", buffer, length) == API_OK);
  }

  SECTION("Api get invalid endpoint returns invalid url") {
    REQUIRE(Api.get("/invalid", buffer, length) == API_INVALID_URL);
  }
}