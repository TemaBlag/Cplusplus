#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <errno.h>
#include <time.h>
//#include <winsock2.h>
#include <ws2tcpip.h>
#include <io.h>
#pragma comment (lib, "ws2_32.lib")
//http://localhost:8000

typedef enum
{
	eHTTP_UNKNOW = 0,
	eHTTP_CONNECT,
	eHTTP_DELETE,
	eHTTP_GET,
	eHTTP_HEAD,
	eHTTP_OPTIONS,
	eHTTP_PATCH,
	eHTTP_POST,
	eHTTP_PUT,
	eHTTP_TRACE,
}eHTTPMethod;




typedef struct 
{
	eHTTPMethod type;
	char  path[255] ;
}sHTTPHeader;

#define SERVER_PORT "8000"
#define MAX_CONNECTION 1000
int create_socket (const char*);
void* get_client_addr(struct sockaddr*);
void parse_http_request(const char* apstrRequest, sHTTPHeader* apHeader);
void send_message(int aSock, const char* apstrMessage);
void send_404(int aSock);

void http_request(int aSock)
{
	const int request_buffer_size = 65536;
	char request[65536];

	int bytes_recvd = recv(aSock, request, request_buffer_size - 1, 0);

	if (bytes_recvd < 0)
	{
		fprintf(stderr, "error recvd\n");
		return;
	}
	request[bytes_recvd] = '\0';

	printf("request:\n%hS\n", request);

	sHTTPHeader req;
	parse_http_request(request, &req);

	if (req.type == eHTTP_GET)
	{
		send_message(aSock,  "sensor 1: 10<br> sensor 2: 20<br>");
	}
	else
	{
		send_404(aSock);
	}

}

void parse_http_request(const char* apstrRequest, sHTTPHeader* apHeader)
{
	int type_length = 0;
	char type[255] = {0};
	int index = 0;

	apHeader->type = eHTTP_UNKNOW;

	scanf_s(&apstrRequest[index],"%s", type);

	type_length = strlen(type);

	if (type_length == 3)
	{
		if (type[0] == 'G' && type[1] == 'E' && type[2] == 'T')
			apHeader->type = eHTTP_GET;

		index += type_length + 1;
		sscanf_s(&apstrRequest[index],"%s", apHeader->path);
	}
}

void send_message(int aSock, const char* apstrMessage)
{
	char buffer[65536] = { 0 };
	char* s1 = "HTTP/1.1 200 OK\n\n";
	char* s2 = "<h1>";
	
	strcat_s(buffer,strlen(s1), s1);
	strcat_s(buffer, strlen(s2), s2);
	strcat_s(buffer,strlen(apstrMessage), apstrMessage);
	strcat_s(buffer, strlen(s2), s2);

	int len = strlen(buffer);
	send(aSock,buffer, len, 0);
}

void send_404(int aSock)
{
	const char* buffer = "HTTP/1.1 404 \n\n";
	int len = strlen(buffer);
	send(aSock, buffer, len, 0);
}

int main() {
	int sock;
	sock = create_socket(SERVER_PORT);
	if (sock < 0) 
	{
		fprintf(stderr, "error create socket\n");
		return -1;
	}
	printf("server created!\n");

	struct sockaddr_storage client_addr;
	int client_d;
	//char client_ip
	while (1) 
	{ 
		socklen_t s_size = sizeof(client_addr);
		client_d = accept(sock, (struct sockaddr*)&client_addr, &s_size);// индефикатор сокета клиента
	
		if (client_d == -1)
		{
			fprintf(stderr, "error accept\n");
			return -1;
		}

		char ip[INET6_ADDRSTRLEN];
		inet_ntop(client_addr.ss_family, get_client_addr((struct sockaddr*)&client_addr), ip, sizeof ip);
		printf("server:got connection from %s\n", ip);

		//read
		http_request(client_d);
		_close(client_d);
	}
	return 0;
}
void *get_client_addr(struct sockaddr *sa) 
{
	if (sa->sa_family == AF_INET)
	{
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}
	    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}



int create_socket(const char* apstrPort)
{
	struct addrinfo hints;
	struct addrinfo *servinfo;
	struct addrinfo *p;

	memset(&hints, 0, sizeof(hints));

	//IPv4 or IPv6
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	int r = getaddrinfo(NULL, apstrPort, &hints, &servinfo);
	if (r != 0) 
	{
		fprintf(stderr, "error getaddrinfo()\n");
		return -1;
	}

	int sock;
	int yes;
	for (p = servinfo; p != NULL; p = p->ai_next)
	{
		sock = socket(p->ai_family, p->ai_socktype, p->ai_protocol); // номер дескриптора 
		if (sock == -1)
		{
			continue;
		}
		else if ((setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1))
		{
			fprintf(stderr, "error setsockopt\n");
			_close(sock);
			freeaddrinfo(servinfo);
			return -2;
		}

		if (bind(sock, p->ai_addr, p->ai_addrlen) == -1)
		{
			_close(sock);
			continue;
		}
		break;
	}
		freeaddrinfo(servinfo);

		if (p == NULL) 
		{
			fprintf(stderr, "failed to find adress\n");
			return -3;
		}

		if (listen(sock, MAX_CONNECTION) == -1)
		{
			fprintf(stderr, "error listen\n");
			return -4;
		}
	return sock;
}
