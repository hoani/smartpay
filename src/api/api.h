#ifndef __HOANI_API_H__
#define __HOANI_API_H__

typedef enum {
  API_OK = 0,
  API_INVALID_URL
} ApiResult_h;

typedef struct {
  ApiResult_h (*get)();
} ApiInterface;

extern ApiInterface Api;

#endif // __HOANI_API_H__