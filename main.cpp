#include <iostream>
#include "platform.h"
#include <microhttpd.h>
#include <sqlite3.h>

#include <string>

#include "request.h"
#include "database.h"

using namespace std;

struct Handle_Page_pass {
  Request * request;
  Database * db;
};

static int Handle_Page (void *cls,
			struct MHD_Connection *connection,
			const char *url,
			const char *method,
			const char *version,
			const char *upload_data, size_t *upload_data_size, void **ptr) {
  
  static int aptr;
  struct MHD_Response *response;
  int ret;
  
  Handle_Page_pass * pass =  reinterpret_cast<Handle_Page_pass*>(cls);
  
  if(&aptr != *ptr) {
    *ptr = &aptr;
    return MHD_YES;
  }
  *ptr = NULL;
  
  string res = pass->request->handle(method, url, string(upload_data, *upload_data_size), connection);
  
  response = MHD_create_response_from_data((size_t)strlen(res.c_str()), (void*) res.c_str(), MHD_NO, MHD_YES);
  ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
  MHD_destroy_response(response);
  return ret;
  
}

int main (int argc, char *argv[]) {
  Request * request = new Request;
  Database * db = new Database ();
  Handle_Page_pass passIn {request, db};
  MHD_Daemon * httpd = MHD_start_daemon(MHD_USE_THREAD_PER_CONNECTION | MHD_USE_DEBUG,
		       6870, // port
		       NULL, NULL, &Handle_Page, &passIn, MHD_OPTION_END);
  if(httpd == NULL) {
    cerr << "Unable to start httpd\n";
    return 1;
  }
  while(1)
    sleep(100);
  MHD_stop_daemon(httpd);
  delete request;
  delete db;
  return 0;
}
