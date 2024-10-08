#include <iostream>
#include <cstring>
#include <string>
#include <sys/socket.h> 
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <thread>
#include <map>


using namespace std;
#define PORT 8080
#define BUFFER_SIZE 1024  

map<int, int> client_map;   

void handle_client(int client_socket){
    char buffer[BUFFER_SIZE];
    int target_client = client_map[client_socket];
    while(true){
        memset(buffer, 0, sizeof(buffer));
        ssize_t bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0);

        if(bytes_received <= 0){
            cout << "Client disconnected!" << endl;
            close(client_socket);
            return;
        }
        
        cout << "received message!" << endl;

        if(client_map.find(target_client) != client_map.end()){ 
            send(target_client, buffer, strlen(buffer), 0);
        } else {
            cout << "Client have not paired!" << endl;
        }
    }

}
int main(){
    int server_socket;
    struct sockaddr_in server_address;

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(server_socket < 0){
        cerr << "Socket creation failed!" << endl;
        return -1;
    }

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(PORT);

    if(bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) < 0){
        cerr << "Bind failed!" << endl;
        return -1;
    }

    if(listen(server_socket, 3) < 0){
        cerr << "Listen failed!" << endl;
        return -1;
    }

    cout << "Server is listening on port " << PORT << "..." << endl;

    while(true){
        struct sockaddr_in client_addr;
        socklen_t addr_len = sizeof(client_addr);
        int new_socket = accept(server_socket, (struct sockaddr*)&client_addr, &addr_len);

        if(new_socket < 0){
            cerr << "Accept failed!" << endl;
            return -1;
        }

        cout << "new client connected: " << inet_ntoa(client_addr.sin_addr) << endl;

        if(client_map.empty()){
            client_map[new_socket] = -1;    // first client, tempory no pare
        } else {
            for(auto& pair : client_map){
                if(pair.second == -1){
                    cout << "clients have paired!" << endl;
                    client_map[new_socket] = pair.first;
                    client_map[pair.first] = new_socket;
                    break;
                }
            }
        }

        thread client_thread(handle_client, new_socket);
        client_thread.detach();
    }
    close(server_socket);
    return 0;
}