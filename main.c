#include"typedefine.h" 
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main() {
	// �]�� Winsock DLL
	WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    //�����׽���
    SOCKET sock = socket(PF_INET, SOCK_STREAM, 0);
    // PF_INET ��ʾ IPv4 ��ַ
    //SOCK_STREAM ��ʾ�������ӵ����ݴ��䷽ʽ��
    //SOCK_DGRAM ��ʾ�����ӵ����ݴ��䷽ʽ��
    //���Խ� protocol ��ֵ��Ϊ 0��ϵͳ���Զ����ݳ�Ӧ��ʹ��ʲôЭ��
	
	int recvi; 
	char c[40]="GET /index.html HTTP/1.1";
    struct sockaddr_in sockAddr;
    //���������������
    memset(&sockAddr, 0, sizeof(sockAddr));  
	//ÿ���ֽڶ���0���
    sockAddr.sin_family = PF_INET;
    //ʹ��IPv4��ַ
    sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    //�����IP��ַ
	sockAddr.sin_port = htons(80);
    //�˿�
	connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
    //���շ��������ص�����
    send(sock,c,strlen(c),0);
    char szBuffer[MAXBYTE] = {0};
    recvi=recv(sock, szBuffer, MAXBYTE, NULL);
    //������յ�������
    printf("Message form server: %s\n%d\n", szBuffer,recvi);
    //�ر��׽���
    closesocket(sock);
    //��ֹʹ�� DLL
    WSACleanup();
    
    system("pause");
    
    return 0;
}
