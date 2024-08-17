#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>

#define BUFSIZE 1024
#define MAXPENDING 5

void DieWithUserMessage(const char *msg, const char *detail) {
    perror(msg);
    fprintf(stderr, "%s\n", detail);
    exit(1);
}

void HandleTCPClient(int clientSocket) {
    char buffer[BUFSIZE];
    // Pega a data e a hora do servidor(computador que está rodando o server)
    time_t currentTime = time(NULL);
    struct tm *localTime = localtime(&currentTime);
    strftime(buffer, BUFSIZE, "%Y-%m-%d %H:%M:%S", localTime);

    // Envia a data e hora para o cliente socket com o send()
    ssize_t numBytesSent = send(clientSocket, buffer, strlen(buffer), 0);
 
    if (numBytesSent < 0) {
        DieWithUserMessage("send() failed", "Unable to send data");
    }
    close(clientSocket);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        DieWithUserMessage("Parameter(s)", "<Server Port>");
    }
    in_port_t serverPort = atoi(argv[1]);

    // A função socket cria e retorna um descritor de arquivo
    int serverSocket;
    if ((serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        DieWithUserMessage("socket() failed", "Unable to create socket");
    }
    struct sockaddr_in serverAddress;                   //Endereço local
    memset(&serverAddress, 0, sizeof(serverAddress));   //Limpa a memória para ter certeza que não tem nada antes de iniciar
    serverAddress.sin_family = AF_INET;                 //Especifica o tipo de endereço, nesse caso é IPV4  
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);  //Define o endereço de IP que o servidor vai usar
    serverAddress.sin_port = htons(serverPort);         //Define o numero da porta

    //Bind associa um endereço a um socket criado
    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
        DieWithUserMessage("bind() failed", "Unable to bind to port");
    }
    //prepara as conexões de entrada em uma fila de conexões pendentes
    if (listen(serverSocket, MAXPENDING) < 0) {
        DieWithUserMessage("listen() failed", "Unable to listen for connections");
    }
    for (;;) {
        struct sockaddr_in clientAddress;
        socklen_t clientAddressLen = sizeof(clientAddress);
        //o accept() extrai a primeira conexão da fila de pendentes criada pelo listen()
        int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddressLen);
        if (clientSocket < 0) {
            DieWithUserMessage("accept() failed", "Unable to accept client connection");
        }
        char clientName[INET_ADDRSTRLEN];
        //o Ntop transforma os dados de binário para string
        if (inet_ntop(AF_INET, &clientAddress.sin_addr.s_addr, clientName, sizeof(clientName)) != NULL) {
            printf("Handling client %s/%d\n", clientName, ntohs(clientAddress.sin_port));
        } else {
            puts("Unable to get client address");
        }
        HandleTCPClient(clientSocket);
    }
    close(serverSocket);
    return 0;
}
