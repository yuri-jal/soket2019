//4-2

#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <sys/types.h>
#define PORT 10000
#define IPADDR "127.0.0.1"
#define BUFSIZE 100

int main(){
	int c_socket; 
	struct sockaddr_in c_addr;
	int n;
	char sendbuffer[BUFSIZE];
	char rcvBuffer[BUFSIZE];//서버에서 보내준 메세지를 저장하는 변수
	char *str;
	//1. 클라이언트 소켓 생성
	c_socket = socket(PF_INET, SOCK_STREAM, 0); //서버와 동일한 설정으로 생성
	//2.소켓 정보 초기화
	memset(&c_addr, 0, sizeof(c_addr));
	c_addr.sin_addr.s_addr = inet_addr(IPADDR); //접속할 IP 설정 (127.0.0.1)
	c_addr.sin_family = AF_INET;
	c_addr.sin_port = htons(PORT);

	//3. 서버에 접속
	if(connect(c_socket, (struct sockaddr *) &c_addr, sizeof(c_addr)) == -1){
		//서버 접속에 실패하면 
		printf("Cannot Connect\n"); //Cannot connect 메세지 출력
		close(c_socket); //자원 회수
		return -1;  //프로세스 종료
	}
	while(1){
		fgets(sendbuffer,sizeof(sendbuffer),stdin);
		write(c_socket,sendbuffer,strlen(sendbuffer));
		if(strncasecmp(sendbuffer,"quit",4)==0)
		{
			break;		
		}
		//5. 서버에서 보낸 메시지 읽기 
		n = read(c_socket, rcvBuffer, sizeof(rcvBuffer));
		strcpy(str,rcvBuffer);
		
		rcvBuffer[n] = '\0'; //문자열 뒷부분 깨짐 방지
		printf("received data: %s\n", rcvBuffer); //서버에서 받은 메세지 출력
		printf("rcvBuffer lens:%d\n",strlen(str+8));
		
		close(c_socket);
	}
	return 0;	
}

