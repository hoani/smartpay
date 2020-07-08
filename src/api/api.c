#include <stdio.h>
#include <string.h>
#include "api.h"

static const ParserInterface * _parser;

static ApiResult_h api_get(const char * url, char * response, size_t len);
static ApiResult_h api_post(const char * url, const char * data, char * response, size_t len);

ApiInterface Api = {
  api_get,
  api_post
};

void api_init(const ParserInterface * parser) {
  _parser = parser;
}

static ApiResult_h api_get(const char * url, char * response, size_t len) {
  if (0 == strcmp(url, "/")) {
    return API_OK;
  }
  if (0 == strcmp(url, "/terminals")) {
    // TODO: Tidy this up - this is really hacky
    TerminalData_t terminals[100];
    int num = store_count();
    int terminal_num = 0;
    for (int i = 0; i < num; i++) {
      if (store_get(i, &(terminals[terminal_num]))) {
        terminal_num++;
      }
    }
    // TODO return internal error here for failure to parse
    _parser->terminal_list(terminals, terminal_num, response, len);
    return API_OK;
  }
  if (strstr(url, "/terminals/") != NULL) {
    int id = -1;
    TerminalData_t terminal;
    if (sscanf(url, "/terminals/%d", &id) == 1) {
      if (store_get(id, &terminal)) {
        // TODO return internal error here for failure to parse
        _parser->terminal(terminal, response, len);
        return API_OK;
      }
    }
    return API_NOT_FOUND;
  }
  return API_INVALID_URL;
}

static ApiResult_h api_post(const char * url, const char * data, char * response, size_t len) {
  if (0 == strcmp(url, "/terminals")) {
    TerminalData_t terminal = _parser->json(data);

    int id = store_add(terminal);

    if (id == k_invalid_id) {
      return API_INTERNAL_ERROR;
    }

    (void) sprintf(response, "%d", id);

    return API_OK;
  }
  return API_INVALID_URL;
}
