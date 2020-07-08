add_library(Fakes STATIC
  parserFake.c
)

target_include_directories(Fakes
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
  PRIVATE Parser Terminal
)


target_link_libraries(Fakes PRIVATE Parser Terminal)

