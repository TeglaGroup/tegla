#include <gio/gio.h>
#include <glib.h>

typedef struct {
  int tick_count;
} GameState;

GameState state = {0};

gboolean udp_socket_ready(GIOChannel *source, GIOCondition condition,
                          gpointer data) {
  GError *error = NULL;
  gchar buffer[1024];
  gsize bytes_read;

  bytes_read =
      g_io_channel_read_chars(source, buffer, sizeof(buffer) - 1, NULL, &error);
  if (error) {
    g_printerr("error reading from socket: %s\n", error->message);
    g_error_free(error);
    return FALSE;
  }

  buffer[bytes_read] = '\0';
  g_print("received: %s\n", buffer);

  return TRUE;
}

gboolean server_tick(gpointer user_data) {
  GameState *state = (GameState *)user_data;

  state->tick_count++;
  g_print("tick %d\n", state->tick_count);

  // do game logic here

  return TRUE;
}

int main(int argc, char *argv[]) {
  GMainLoop *loop = g_main_loop_new(NULL, FALSE);

  GError *error = NULL;
  GSocket *udp_socket =
      g_socket_new(G_SOCKET_FAMILY_IPV4, G_SOCKET_TYPE_DATAGRAM,
                   G_SOCKET_PROTOCOL_UDP, &error);

  if (!udp_socket) {
    g_printerr("failed to create socket: %s\n", error->message);
    return 1;
  }

  GInetAddress *addr = g_inet_address_new_any(G_SOCKET_FAMILY_IPV4);
  GSocketAddress *sock_addr = g_inet_socket_address_new(addr, 12345);
  
  g_object_unref(addr);

  if (!g_socket_bind(udp_socket, sock_addr, TRUE, &error)) {
    g_printerr("failed to bind: %s\n", error->message);
    return 1;
  }
  g_object_unref(sock_addr);

  GIOChannel *channel = g_io_channel_unix_new(g_socket_get_fd(udp_socket));
  g_io_add_watch(channel, G_IO_IN, (GIOFunc)udp_socket_ready, NULL);
  g_io_channel_unref(channel);

  // gameloop tick every 60 ms
  g_timeout_add(60, server_tick, &state);

  g_main_loop_run(loop);

  g_object_unref(udp_socket);
  g_main_loop_unref(loop);
  
  return 0;
}