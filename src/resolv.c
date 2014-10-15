#include <stdio.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "config.h"

static void print_addr(struct in_addr *addr)
{
  fprintf(stdout, "%s\n", inet_ntoa(*addr));
}

static void print_addr_list(struct in_addr **list)
{
  struct in_addr **addresses = list;

  for (; addresses && *addresses; addresses++) {
    print_addr(*addresses);
  }
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

  char *hostname = *(argv + optind);
  struct hostent *hostinfo = gethostbyname(hostname);

  if (hostinfo == NULL) {
    fprintf(stderr, "Can not resolve %s\n", hostname);
    return 2;
  }

  if (all) {
    print_addr_list((struct in_addr **) hostinfo->h_addr_list);
  } else {
    print_addr((struct in_addr *) hostinfo->h_addr);
  }

  return 0;
}
