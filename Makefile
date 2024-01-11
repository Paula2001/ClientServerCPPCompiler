bserver:
	g++ server.cpp ./serverHelpers/socket.c ./serverHelpers/readFromclient.c -o server && ./server 4000
bclient:
	g++ client.cpp ./clientHelpers/clientCommunication.c -o client && ./client