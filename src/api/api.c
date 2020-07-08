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
    return API_OK;
  }
  return API_INVALID_URL;
}

static ApiResult_h api_post(const char * url, const char * data, char * response, size_t len) {
  return API_OK;
}
