#include "api.h"

static ApiResult_h api_get();

ApiInterface Api = {
  api_get
};

static ApiResult_h api_get() {
  return API_OK;
}
