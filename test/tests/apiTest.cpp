#include "catch.hpp"
extern "C" {
#include "api.h"
}

TEST_CASE( "Api cases", "[Api]" )
{
  SECTION("Api_get_returns_OK") {
    REQUIRE(Api.get() == API_OK);
  }
}