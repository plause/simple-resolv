#include <stdio.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "config.h"

int main(int argc, char **argv)
{
  if (argc != 2) {
    fprintf(stderr, "Usage: %s HOSTNAME\n", PACKAGE);
    return 1;
  }

  char *hostname = *(argv + 1);
  struct hostent *hostinfo = gethostbyname(hostname);

  if (hostinfo == NULL) {
    fprintf(stderr, "Can not resolve %s\n", hostname);
    return 2;
  }

  struct in_addr *addr = (struct in_addr *) hostinfo->h_addr;

  fprintf(stdout, "%s\n", inet_ntoa(*addr));

  return 0;
}
