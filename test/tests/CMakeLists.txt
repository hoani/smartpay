add_executable(Test
  TestMain.cpp
  apiTest.cpp
  parserTest.cpp
  storeTest.cpp
)

target_link_libraries(Test PRIVATE
  Catch
  Api
  Parser
  Terminal
  Store
)

target_compile_features(Test PRIVATE cxx_std_11)

