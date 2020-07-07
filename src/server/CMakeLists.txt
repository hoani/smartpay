add_library(Server STATIC server.c)

find_library(MHD_LIB microhttpd)
find_path(MHD_PATH microhttpd.h)

target_link_libraries(Server PRIVATE "${MHD_LIB}")

target_include_directories(Server
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    PRIVATE "${MHD_PATH}"
)
