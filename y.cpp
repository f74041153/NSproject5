#include<iostream>
#include<fstream>
#include <unistd.h>  
#include <sys/types.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <arpa/inet.h>

using namespace std;

int main(){
	
	string text = "read write allow?\n";
	ofstream ofs;
	ofs.open("test.txt");
	ofs << text;
	ofs.close();

	struct sockaddr_in server; 
	int sock;  

	if((sock = socket(AF_INET, SOCK_STREAM, 0)) != -1){ 
		server.sin_family = AF_INET;  
		server.sin_port = htons(23);
		inet_pton(AF_INET, "140.112.172.1", &server.sin_addr.s_addr);
		if(connect(sock, (struct sockaddr *)&server, sizeof(server)) == 0){
			cout << "connect to ptt!" << endl;
		}
		close(sock);
	}

	return 0;
}
