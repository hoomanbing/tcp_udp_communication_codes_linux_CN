# TCP_UDP_communication_codes_linux_CN
This repository contains TCP UDP protocol codes (socket programming) executed in a Linux Environment as part of the Computer Networks curriculum.

## Contents

1. **1_server_1_client_TCP_communication.c**
   - **Description**: Demonstrates a basic TCP communication between a single server and a single client.
   - **How it works**: The server waits for a connection from the client, receives a message, and sends a response back.

2. **1_server_1_client_UDP_communication.c**
   - **Description**: Shows a basic UDP communication between a single server and a single client.
   - **How it works**: The server listens for incoming datagrams from the client. The client sends a message without establishing a persistent connection.

3. **TCP_communication_of_one_message_n_times_between_server_client.c**
   - **Description**: Illustrates a TCP communication where the client sends one message multiple times to the server.
   - **How it works**: The server listens for connections, and the client sends a specific message to the server `n` times.

4. **n_messages_between_server_client_TCP.c**
   - **Description**: Demonstrates TCP communication where the client sends multiple messages to the server.
   - **How it works**: The server handles multiple messages from the client, processing each one in turn.
  
5. **concurrent_communication_server_client_tcp.c**
   - **Description**: Demonstrates TCP communication with concurrent connections between multiple clients and a single server.
   - **How it works**: The server can handle multiple client connections simultaneously, allowing for concurrent communication. This is typically implemented using threading or select/poll mechanisms.

6. **fork_process_server_client_tcp.c**
   - **Description**: Shows how to use fork processes for handling multiple client connections in TCP communication.
   - **How it works**: The server forks a new process for each incoming client connection, enabling parallel processing of client requests.

7. **5_messages_server_client_udp.c**
   - **Description**: Demonstrates a UDP communication where the client sends five messages to the server.
   - **How it works**: The server listens for five incoming messages from the client and processes each one without maintaining a connection state.

8. **n_server_n_client_udp.c**
   - **Description**: Shows UDP communication between multiple servers and multiple clients.
   - **How it works**: Multiple clients can send messages to multiple servers without establishing a connection, and each server can handle incoming datagrams independently.

9. **udp_1_server_many_clients.c**
   - **Description**: Illustrates a UDP communication setup with one server and multiple clients.
   - **How it works**: The server listens for datagrams from multiple clients and processes each message as it arrives, without maintaining a persistent connection.

## How to Run

To run these scripts, follow these steps:

**Clone the repository**:
   ```bash
   git clone https://github.com/yourusername/socket-programming-examples.git
   cd socket-programming-examples
