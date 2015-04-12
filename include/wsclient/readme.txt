使用说明:
该库为web service客户端封装动态库，用于调用web service接口,
如果接口变更需要更新lib和include头文件(客户端的库和头文件都可以通过gsoap工具根据服务器上的接口定义文件(.wsdl)自动生成)

示例代码如下:
#include "soapsapProxy.h"	// 接口代理类(必须)
#include "sap.nsmap"		// 命名空间(必须)

// web service地址
const char server[] = "http://172.23.16.11/cgi-bin/sapserver";

int main(int argc, char **argv)
{
	// 接口代理类 
	sapProxy theSap;
	// 设置地址
	theSap.soap_endpoint = server;
	// 返回结果类型
	sap__AuthResult theAuthResult;
	// 调用接口
	int ret = theSap.CmAuthByUser(72,12,"ffffff",&theAuthResult);
	// 输出结果
	printf("Server:%s AuthResult:%d ret:%d\n",server,theAuthResult,ret);
	return 0;
}

