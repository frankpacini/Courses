#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>

#define IOCTL_GETCHAR _IOR(0, 6, struct ioctl_getchar_t)

int main () {

  int fd = open ("/proc/keyboard_test", O_RDONLY);

  struct ioctl_getchar_t {
    char *ret_addr;
  } ioctl_getchar;

  char ch;
  ioctl_getchar.ret_addr = &ch;

  while(1) {
    ioctl (fd, IOCTL_GETCHAR, &ioctl_getchar);
    
    if(ch == '\b') {
      char str[4] = {'\b', ' ', '\b', '\0'};
      write(STDOUT_FILENO, str, sizeof(str)/sizeof(str[0]));
    } else {
      char str[2] = {ch, '\0'};
      write(STDOUT_FILENO, str, sizeof(str)/sizeof(str[0]));
    }
  }

  return 0;
}
