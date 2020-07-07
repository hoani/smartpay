#include "server.h"
#include "api.h"

#define PORT 8888

int main () {
  return server_start(PORT, &Api);
}