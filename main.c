#include"typedefine.h" 
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main() {
	// 註冊 Winsock DLL
	WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    //创建套接字
    SOCKET sock = socket(PF_INET, SOCK_STREAM, 0);
    // PF_INET 表示 IPv4 地址
    //SOCK_STREAM 表示面向连接的数据传输方式。
    //SOCK_DGRAM 表示无连接的数据传输方式。
    //可以将 protocol 的值设为 0，系统会自动推演出应该使用什么协议
	
	int recvi; 
	char c[40]="GET /index.html HTTP/1.1";
    struct sockaddr_in sockAddr;
    //向服务器发起请求
    memset(&sockAddr, 0, sizeof(sockAddr));  
	//每个字节都用0填充
    sockAddr.sin_family = PF_INET;
    //使用IPv4地址
    sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    //具体的IP地址
	sockAddr.sin_port = htons(80);
    //端口
	connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
    //接收服务器传回的数据
    send(sock,c,strlen(c),0);
    char szBuffer[MAXBYTE] = {0};
    recvi=recv(sock, szBuffer, MAXBYTE, NULL);
    //输出接收到的数据
    printf("Message form server: %s\n%d\n", szBuffer,recvi);
    //关闭套接字
    closesocket(sock);
    //终止使用 DLL
    WSACleanup();
    
    system("pause");
    
    return 0;
}
