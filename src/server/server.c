#include <microhttpd.h>
#include <stdio.h>
#include "server.h"

static ApiInterface * _api = NULL;

int answer_to_connection(
  void *cls,
  struct MHD_Connection *connection,
  const char *url,
  const char *method,
  const char *version,
  const char *upload_data,
  size_t *upload_data_size,
  void **con_cls // connection
  ){
  const char *page  = "<html><body>Hello, browser!</body></html>";
  struct MHD_Response *response;
  int ret;

  printf(url);
  printf("\n");
  printf(method);
  printf("\n");

  if ((0 != strcmp (method, "GET")) || (_api == NULL)) {
    return MHD_NO;
  }

  if (_api->get() == API_OK) {
    response = MHD_create_response_from_buffer (strlen (page),
                                          (void*) page, MHD_RESPMEM_PERSISTENT);
    ret = MHD_queue_response (connection, MHD_HTTP_OK, response);
    MHD_destroy_response (response);

    return ret;
  }

  return MHD_NO;
}

int server_start(int port, ApiInterface * api) {
  struct MHD_Daemon *daemon;

  _api = api;

  daemon = MHD_start_daemon (MHD_USE_SELECT_INTERNALLY, port, NULL, NULL,
                             &answer_to_connection, NULL, MHD_OPTION_END);
  if (NULL == daemon){
    return 1;
  }
  printf("Press ENTER to exit \n");
  getchar();

  MHD_stop_daemon (daemon);

  return 0;
}