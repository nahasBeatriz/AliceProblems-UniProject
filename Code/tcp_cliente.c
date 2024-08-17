#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUFSIZE 1024

void DieWithSystemMessage(const char *msg) {
    perror(msg);
    exit(1);
}

void DieWithUserMessage(const char *msg, const char *detail) {
    fprintf(stderr, "%s: %s\n", msg, detail);
    exit(1);
}

int main(int argc, char *argv[]) {
    if (argc < 2 || argc > 3)
        DieWithUserMessage("Parameter(s)",
            "<Server Address> [<Server Port>]");

    char *serverIP = argv[1];
    in_port_t serverPort = (argc == 3) ? atoi(argv[2]) : 7;
    // A função socket cria e retorna um descritor de arquivo
    int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock < 0)
        DieWithSystemMessage("socket() failed");

    struct sockaddr_in serverAddress;                   //Endereço local
    memset(&serverAddress, 0, sizeof(serverAddress));   //Limpa a memória antes de rodar
    serverAddress.sin_family = AF_INET;                 //Especifica o tipo de endereço, nesse caso é IPV4  

    int returnVal = inet_pton(AF_INET, serverIP, &serverAddress.sin_addr.s_addr);
    if (returnVal == 0)
        DieWithUserMessage("inet_pton() failed", "Invalid address string");
    else if (returnVal < 0)
        DieWithSystemMessage("inet_pton() failed");

    serverAddress.sin_port = htons(serverPort);
    //conecta o socket do cliente com o socket do servidor
    if (connect(sock, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
        DieWithSystemMessage("connect() failed");

    char buffer[BUFSIZE];
    //o recv recebe a mensagem de um socket nesse caso do servidor
    ssize_t numBytes = recv(sock, buffer, BUFSIZE - 1, 0);
    if (numBytes < 0)
        DieWithSystemMessage("recv() failed");
    else if (numBytes == 0)
        DieWithUserMessage("recv()", "connection closed prematurely");

    buffer[numBytes] = '\0';
    printf("Recebemos a data e a hora do servidor: %s\n", buffer);

    close(sock);
    exit(0);
}
