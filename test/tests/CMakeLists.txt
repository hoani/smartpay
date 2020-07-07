add_executable(Test
  TestMain.cpp
  apiTest.cpp
)

target_link_libraries(Test PRIVATE
  Catch
  Api
)

target_compile_features(Test PRIVATE cxx_std_11)

