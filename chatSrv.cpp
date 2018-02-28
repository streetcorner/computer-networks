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
	SOCKET sockSrv=socket(AF_INET,SOCK_DGRAM,0);
	SOCKADDR_IN addrSrv;//strut to save local information
	addrSrv.sin_addr.S_un.S_addr=htonl(INADDR_ANY);
	addrSrv.sin_family=AF_INET;
	addrSrv.sin_port=htons(6000);

	bind(sockSrv,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR));//bind

	char recvBuf[100];//receive
	char sendBuf[100];//send massage
	char tempBuf[200];//midle data
	SOCKADDR_IN addrClient;//srv
	int len=sizeof(SOCKADDR);//initialize
	while(1){
        //recv
		recvfrom(sockSrv,recvBuf,100,0,(SOCKADDR*)&addrClient,&len);//receive
		if('q'==recvBuf[0])//if the first char is 'q',then quit
		{
			sendto(sockSrv,"q",strlen("q")+1,0,(SOCKADDR*)&addrClient,len);//send to the other "q"
			printf("Chat end!\n");//end chat
			break;
		}
		sprintf(tempBuf,"%s say:%s",inet_ntoa(addrClient.sin_addr),recvBuf);//information
		printf("%s\n",tempBuf);//printf the send massage
		printf("Please input data:\n");

		gets(sendBuf);//get a line from the keyboard and put it into sendBuf
		//send
		sendto(sockSrv,sendBuf,strlen(sendBuf)+1,0,(SOCKADDR*)&addrClient,len);
	}
	closesocket(sockSrv);
	WSACleanup();
}
