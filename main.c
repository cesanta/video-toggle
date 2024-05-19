#include "hal.h"
#include "mongoose.h"

#if MG_ARCH == MG_ARCH_UNIX || MG_ARCH == MG_ARCH_WIN32
#define LISTENING_URL "http://0.0.0.0:8003"
#else
#define LISTENING_URL "http://0.0.0.0:80"
#endif

// HTTP server event handler function
void ev_handler(struct mg_connection *c, int ev, void *ev_data) {
  if (ev == MG_EV_HTTP_MSG) {
    struct mg_http_message *hm = (struct mg_http_message *) ev_data;
    if (mg_match(hm->uri, mg_str("/api/led/toggle"), NULL)) {
      gpio_toggle(LED1);
      mg_http_reply(c, 200, "", "true\n");
    } else {
      struct mg_http_serve_opts opts = {.root_dir = "/web_root",
                                        .fs = &mg_fs_packed};
      mg_http_serve_dir(c, hm, &opts);
    }
  }
}

int main(void) {
  hal_init();

  struct mg_mgr mgr;  // Declare event manager
  mg_mgr_init(&mgr);  // Initialise event manager
  mg_http_listen(&mgr, LISTENING_URL, ev_handler,
                 NULL);  // Setup listener
  for (;;) {             // Run an infinite event loop
    mg_mgr_poll(&mgr, 1000);
  }
  return 0;
}
