#!/usr/bin/env python3

import socket
import os
import sys
import datetime
from typing import List

import multiprocessing

server_listen_addr = '0.0.0.0'
server_listen_port = 9090

process_pool: List[multiprocessing.Process]  = []

def handle_client(client_sock: socket.socket, addr):
    with client_sock:
        curr_dt = datetime.datetime.now().strftime("%Y-%m-%d_%H:%M:%S")
        f_name = curr_dt + f"_{addr[0]}_{addr[1]}.txt"
        print(f_name)
        with open(f_name, 'w+') as f_stream:
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
            print("waiting for new client...")
            try:
                client_socket, client_addr = server_socket.accept()
            except KeyboardInterrupt as e:
                print("KeyboardInterrupt occured while accept, quit now!")
                exit(-1)
            finally:
                # 关闭所有子进程
                for item in process_pool:
                    if item.is_alive:
                        item.close()
            print(f"accepted client: {client_addr}")
            p = multiprocessing.Process(target=handle_client, args=(client_socket, client_addr))
            p.start()
            process_pool.append(p)

            # 父进程关闭掉客户端fd
            client_socket.close()



    
