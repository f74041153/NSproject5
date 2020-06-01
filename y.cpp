#include<iostream>
#include<fstream>
#include <unistd.h>  
#include <sys/types.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <arpa/inet.h>

using namespace std;

void _write(string path){
    string text = "rw test!\n";
	ofstream ofs;
	ofs.open(path);
	if(!ofs){	
		cout << "[permission denied] fail to write " << path << endl;
	}else{
		ofs << text;
		ofs.close();
	}
}

void _read(string path){
	ifstream ifs;
	ifs.open(path);
	if(!ifs){
		cout << "[permission denied] fail to read " << path << endl;
	}else{
		string str;
		while(getline(ifs, str)){
			cout << str << endl;
		}
	}
}

int main(){

	string allowed_wpath = "./w.txt", test_wpath = "~/w.txt";
	string allowed_rpath = "./w.txt", test_rpath = "~/w.txt";

	_write(allowed_wpath);
	_write(test_wpath);

	_read(allowed_rpath);
	_read(test_rpath);


	struct sockaddr_in server; 
	int sock;  

	if((sock = socket(AF_INET, SOCK_STREAM, 0)) != -1){ 
		server.sin_family = AF_INET;  
		server.sin_port = htons(23);
		inet_pton(AF_INET, "140.112.172.1", &server.sin_addr.s_addr);
		if(connect(sock, (struct sockaddr *)&server, sizeof(server)) != 0){
			cout << "[permission denied] fail to create connection" << endl;
		}
		close(sock);
	}else{	
		cout << "[permission denied] fail to create socket" << endl;
	}

	return 0;
}
