bserver:
	g++ server.cpp ./serverHelpers/socket.c ./serverHelpers/readFromclient.c -o server && ./server 4000
bclient:
	g++ client.cpp ./clientHelpers/clientCommunication.cpp -o client && ./client
tbclient:
	strace -f g++ client.cpp ./clientHelpers/clientCommunication.cpp -o client && ./client
tbserver:
	strace -f g++ server.cpp ./serverHelpers/socket.c ./serverHelpers/readFromclient.c -o server && ./server 4000