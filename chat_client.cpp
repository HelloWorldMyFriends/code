#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>

#define PORT 8080
#define BUFFER_SIZE 1024

using namespace std;
// 接收服务器消息
void receive_messages(int socket) {
    char buffer[BUFFER_SIZE];

    while (true) {
        memset(buffer, 0, sizeof(buffer));
        ssize_t bytes_received = recv(socket, buffer, BUFFER_SIZE, 0);

        if (bytes_received <= 0) {
            cout << "server has disconnected!" << endl;
            close(socket);
            return;
        }

        cout << "receive messages:  " << buffer << endl;
    }
}

void send_messages(int socket){
    char buffer[BUFFER_SIZE];

    while(true){
        memset(buffer, 0, sizeof(buffer));
        cin.getline(buffer, BUFFER_SIZE);
        send(socket, buffer, strlen(buffer), 0);
    }
}

int main() {
    int client_socket;
    struct sockaddr_in server_addr;

    // 创建客户端套接字
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0) {
        cerr << "socket chreation falied!" << endl;
        return -1;
    }

    // 初始化服务器地址
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  // 服务器 IP

    // 连接到服务器
    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        cerr << "server connection failed!" << endl; 
        return -1;
    }

    cout << "server connection succeed!" << endl;

    // 创建线程接收服务器消息
    thread receive_thread(receive_messages, client_socket);
    receive_thread.detach();  // 分离线程以便独立运行

    // 发送消息给服务器
    // char message[BUFFER_SIZE];
    // while (true) {
    //     cin.getline(message, BUFFER_SIZE);
    //     send(client_socket, message, strlen(message), 0);
    // }
    thread send_thread(send_messages, client_socket);
    send_thread.join();

    close(client_socket);
    return 0;
}