#include<Winsock2.h>
#include<stdio.h>

void main(){
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	wVersionRequested=MAKEWORD(1,1);
	err=WSAStartup(wVersionRequested,&wsaData);
	if(err!=0){ return;}
	if(LOBYTE(wsaData.wVersion)!=1|| HIBYTE(wsaData.wVersion)!=1){
		WSACleanup();
		return;
	}
	SOCKET sockClient=socket(AF_INET,SOCK_DGRAM,0);
	SOCKADDR_IN addrSrv;//Server data structure
	addrSrv.sin_addr.S_un.S_addr=inet_addr("127.0.0.1");
	addrSrv.sin_family=AF_INET;
	addrSrv.sin_port=htons(6000);
	char recvBuf[100];//receive
	char sendBuf[100];//send
	char tempBuf[200];//temp buffer
	int len=sizeof(SOCKADDR);//initialize

	while(1){
		printf("Please input data:\n");
		gets(sendBuf);//get lines from keyboard
		sendto(sockClient,sendBuf,strlen(sendBuf)+1,0,(SOCKADDR*)&addrSrv,len);//send data

		recvfrom(sockClient,recvBuf,100,0,(SOCKADDR*)&addrSrv,&len);//receive
		if('q'==recvBuf[0]){
			sendto(sockClient,"q",strlen("q")+1,0, (SOCKADDR*)&addrSrv,len);
			printf("Chatend!\n");
			break;
		}
		sprintf(tempBuf,"%s say: %s",inet_ntoa(addrSrv.sin_addr),recvBuf);
		printf("%s\n",tempBuf);//temp buffer
	}
		closesocket(sockClient);
		WSACleanup();
}
