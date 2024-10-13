#!/usr/bin/env python3

import socket
import os
import sys
import datetime

import multiprocessing

server_listen_addr = '0.0.0.0'
server_listen_port = 9090

def handle_client(client_sock: socket.socket, addr):
    with client_sock:
        with open('esp8266.txt', 'w+') as f_stream:
            while True:
                data = client_sock.recv(1024)
                if not data:
                    print(f"client {addr} close!")
                    break
                print(f"data from client: {data}")

                curr_dt = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")             
                f_stream.write(curr_dt + "->" + " [" + data.decode('utf-8') + "]")
                f_stream.write("\r\n")
                f_stream.flush()
                # echo back
                # client_sock.sendall(data)
            

if __name__ == "__main__":
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as server_socket:
        server_socket.bind((server_listen_addr, server_listen_port))
        server_socket.listen()
        print(f"listen on {server_listen_addr}, port: {server_listen_port}")

        while True:
            print("waiting for new client...");
            client_socket, client_addr = server_socket.accept()
            print(f"accepted client: {client_addr}")
            p = multiprocessing.Process(target=handle_client, args=(client_socket, client_addr))
            p.start()

            # 父进程关闭掉客户端fd
            client_socket.close()



    
