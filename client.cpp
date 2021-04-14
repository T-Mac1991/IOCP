#include <iostream>
#include <WinSock2.h>
using namespace std;

#pragma comment(lib,"ws2_32.lib")

int main()
{
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(6000);
    server.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

    SOCKET client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    int flag;
    flag = connect(client, (sockaddr*)&server, sizeof(server));
    if (flag < 0) {
        cout << "error!" << endl;
        return -1;
    }
    while (1) {
        cout << "sent hello!!!!" << endl;
        char buffer[1024];
        strcpy_s(buffer, "hello");
        send(client, buffer, 1024, 0);

        memset(buffer, NULL, sizeof(buffer));

        cout << "recv: " << endl;
        int rev = recv(client, buffer, 1024, 0);
        if (rev == 0)
            cout << "recv nothing!" << endl;
        cout << buffer << endl;
        Sleep(2000);
    }

    closesocket(client);
    WSACleanup();
    return 0;
}



// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
