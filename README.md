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

## How to Run

To run these scripts, follow these steps:

**Clone the repository**:
   ```bash
   git clone https://github.com/yourusername/socket-programming-examples.git
   cd socket-programming-examples
