#include <microhttpd.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "server.h"

static ApiInterface * _api = NULL;

const char *askpage  = "<html><body>Hello, ask!</body></html>";
const char *errorpage  = "<html><body>Hello, error!</body></html>";
const char *greetingpage  = "<html><body>Greeting Page!</body></html>";

#define ANSWER_STRING_MAX_LENGTH (2048)

enum ConnectionType {
  POST = 0,
  GET = 1
};

struct connection_info_struct
{
  enum ConnectionType connectiontype;
  char *answerstring;
};

static int send_page(struct MHD_Connection *connection, const char * page) {
  struct MHD_Response *response;
  response = MHD_create_response_from_buffer (strlen (page),
                                          (void*) page, MHD_RESPMEM_PERSISTENT);
  int result = MHD_queue_response (connection, MHD_HTTP_OK, response);
  MHD_destroy_response(response);

  return result;
}

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

  // Queue up incoming connections
  if(NULL == *con_cls) {
    struct connection_info_struct *con_info;

    con_info = malloc (sizeof (struct connection_info_struct));
    if (NULL == con_info) return MHD_NO;
    con_info->answerstring = NULL;

    if (0 == strcmp (method, "POST")) {
      con_info->connectiontype = POST;
    }
    else con_info->connectiontype = GET;
    *con_cls = (void*) con_info;
    return MHD_YES;
  }

  if (0 == strcmp (method, "GET")) {
    struct connection_info_struct *con_info = *con_cls;

    con_info->answerstring = malloc(ANSWER_STRING_MAX_LENGTH);
    con_info->answerstring[0] = '\0';

    _api->get(url, con_info->answerstring, ANSWER_STRING_MAX_LENGTH);

    int res = send_page(connection, con_info->answerstring);
    free(con_info->answerstring);
    free(con_info); // definately not the best way to do this...
    return res;
  }

  if (0 == strcmp (method, "POST")) {
    struct connection_info_struct *con_info = *con_cls;

    if (*upload_data_size != 0){
      con_info->answerstring = malloc(ANSWER_STRING_MAX_LENGTH);
      con_info->answerstring[0] = '\0';

      _api->post(url, upload_data, con_info->answerstring, ANSWER_STRING_MAX_LENGTH);
      *upload_data_size = 0;

      return MHD_YES;
    }
    else if (NULL != con_info->answerstring) {
      int res = send_page(connection, con_info->answerstring);
      free(con_info->answerstring);
      free(con_info); // also definately not the best way to do this...
      return res;
    }
  }

  return send_page(connection, errorpage);
}

int server_start(int port, ApiInterface * api) {
  struct MHD_Daemon *daemon;

  _api = api;

  daemon = MHD_start_daemon (MHD_USE_SELECT_INTERNALLY, port, NULL, NULL,
                             &answer_to_connection, NULL,
                             MHD_OPTION_END);
  if (NULL == daemon){
    return 1;
  }
  printf("Press ENTER to exit \n");
  getchar();

  MHD_stop_daemon (daemon);

  return 0;
}
