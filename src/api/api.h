#ifndef __HOANI_API_H__
#define __HOANI_API_H__

#include <stdlib.h>
#include "parser.h"
#include "store.h"

typedef enum {
  API_OK = 0,
  API_INVALID_URL,
  API_NOT_FOUND,
  API_INTERNAL_ERROR
} ApiResult_h;

typedef struct {
  ApiResult_h (*get)(const char * url, char * response, size_t len);
  ApiResult_h (*post)(const char * url, const char * data, char * response, size_t len);
} ApiInterface;

void api_init(const ParserInterface * parser);

extern ApiInterface Api;

#endif // __HOANI_API_H__