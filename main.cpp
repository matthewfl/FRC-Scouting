#include <iostream>
#include "platform.h"
#include <microhttpd.h>

#include "request.h"


static int Handle_Page (void *cls,
			struct MHD_Connection *connection,
			const char *url,
			const char *method,
			const char *version,
			const char *upload_data, size_t *upload_data_size, void **ptr) {
  
}

int main (int argc, char *argv[]) {
  MHD_Daemon * d;
  d = MHD_start_daemon(MHD_USE_THREAD_PER_CONNECTION | MHD_USE_DEBUG,
		       6870, // port
		       NULL, NULL, 
}
