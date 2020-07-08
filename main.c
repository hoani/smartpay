#include "server.h"
#include "api.h"
#include "parser.h"

#define PORT 11337

int main () {
  api_init(&Parser);
  return server_start(PORT, &Api);
}