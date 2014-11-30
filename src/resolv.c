#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>
#include "config.h"

static void print_addr(struct in_addr *addr)
{
  fprintf(stdout, "%s\n", inet_ntoa(*addr));
}

static struct addrinfo *get_addresses(const char *node)
{
  struct addrinfo hints, *res;

  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_RAW;

  int gaierr = getaddrinfo(node, NULL, &hints, &res);

  if (gaierr != 0) {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(gaierr));
    exit(EXIT_FAILURE);
  }

  return res;
}

int main(int argc, char **argv)
{
  int all = 0;
  int c;

  while ((c = getopt(argc, argv, "a")) != -1) {
    switch (c) {
    case 'a':
      all = 1;
      break;
    case '?':
    default:
      return 1;
    }
  }

  if (argc - optind != 1) {
    fprintf(stderr, "Usage: %s [-a] HOSTNAME\n", PACKAGE);
    return 1;
  }

  struct addrinfo *res, *res0 = get_addresses(*(argv + optind));

  for (res = res0; res; res = res->ai_next) {
    print_addr(&(((struct sockaddr_in *) res->ai_addr)->sin_addr));

    if (!all)
      break;
  }

  freeaddrinfo(res0);

  return 0;
}
