#include <stdio.h>
#include <unistd.h>
#include <sys/utsname.h>

int main() {
    char hostname[256];
    if (gethostname(hostname, sizeof(hostname)) == 0) {
        printf("Computer's network name: %s\n", hostname);
    } else {
        perror("Error getting network name");
    }
    struct utsname uname_data;
    if (uname(&uname_data) == 0) {
        printf("Operating System: %s\n", uname_data.sysname);
        printf("Node (Computer) Name: %s\n", uname_data.nodename);
        printf("OS Version: %s\n", uname_data.release);
        printf("Kernel Version: %s\n", uname_data.version);
        printf("Processor Architecture: %s\n", uname_data.machine);
    } else {
        perror("Error getting system information");
    }
    return 0;
}
