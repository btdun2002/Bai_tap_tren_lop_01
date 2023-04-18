#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    int listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listener == -1)
    {
        perror("socket() failed");
        return 1;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(9000);
    if (bind(listener, (struct sockaddr *)&addr, sizeof(addr)))
    {
        perror("bind() failed");
        return 1;
    }
    if (listen(listener, 5))
    {
        perror("listener() failed");
        return 1;
    }
    printf("Initialized server.\n");

    struct sockaddr_in client_addr;
    int client_addr_len = sizeof(client_addr);
    int client = accpet(listener, (struct sockaddr *)&client_addr, &client_addr_len);
    printf("Accepted socket %d from IP: %s:%d", client, inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

    char buf[256];
    int recv_bytes;
    char ack_msg[256];
    memset(buf, 0, sizeof(buf));
    recv_bytes = recv(client, buf, sizeof(buf), 0);
    if (recv_bytes == -1)
    {
        perror("recv()failed");
        return 1;
    }
    buf[recv_bytes] = 0;
    printf("%d bytes received\b", recv_bytes);

    int pos = 0;
    char computer_name[64];
    strcpy(computer_name, buf);
    pos = strlen(computer_name) + 1;
    int num_drives = (recv_bytes - pos) + 1;
    int num_drives = (recv_bytes - pos) / 3;
    for (int i = 0; i < num_drives; i++)
    {
        char drive_letter = buf[pos];
        pos++;
        unsigned short drive_size;
        memcpy(&drive_size, buf + pos, sizeof(drive_size));
        pos += sizeof(drive_size);
    }
}