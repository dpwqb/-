#include <stdio.h>
#include <Windows.h>
BOOL SetPrivilege(HANDLE hToken,LPCTSTR lpszPrivilege,BOOL bEnablePrivilege)
{
	TOKEN_PRIVILEGES tp={0};
	LUID luid;
	if(!LookupPrivilegeValue(NULL,lpszPrivilege,&luid)){
		printf("无法查找权限值\n");
		return FALSE;
	}
	tp.PrivilegeCount=1;
	tp.Privileges[0].Luid=luid;
	tp.Privileges[0].Attributes=bEnablePrivilege?SE_PRIVILEGE_ENABLED:0;
	if(!AdjustTokenPrivileges(hToken,FALSE,&tp,sizeof(TOKEN_PRIVILEGES),NULL,NULL)){
		printf("无法调整令牌特权\n");
		return FALSE;
	}
	if(GetLastError()==ERROR_NOT_ALL_ASSIGNED){
		printf("无法分配所有请求的特权\n");
		return FALSE;
	}
	return TRUE;
}
int main(){
	printf("\n\t请以管理员权限运行！\n此程序用于在当前目录创建或覆盖名称为\"CreateFile.bin\"的指定预分配空间大小的文件\n单位：（KB）\n\t参考值：\n\t1TB→1073741824\n\t1GB→1048576\n\t1MB→1024\n请输入创建的文件大小：");
	LPCSTR fileName="CreateFile.bin";
	ULONGLONG fileSize;
	scanf("%d",&fileSize);
	fileSize*=1024;
	HANDLE hToken;
	if(!OpenProcessToken(GetCurrentProcess(),TOKEN_ADJUST_PRIVILEGES|TOKEN_QUERY,&hToken)){
		printf("无法打开进程令牌\n");
		system("pause");
		return 3;
	}
	if(!SetPrivilege(hToken,SE_MANAGE_VOLUME_NAME,TRUE)){
		printf("获取SE_MANAGE_VOLUME_NAME权限失败\n");
		CloseHandle(hToken);
		system("pause");
		return 2;
	}
	HANDLE hFile=CreateFileA(fileName,GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	if(hFile==INVALID_HANDLE_VALUE){
		printf("无法创建文件\n");
		CloseHandle(hToken);
		system("pause");
		return 1;
	}
	LARGE_INTEGER liDistanceToMove;
	liDistanceToMove.QuadPart=fileSize;
	SetFilePointerEx(hFile,liDistanceToMove,NULL,FILE_BEGIN);
	if(SetEndOfFile(hFile))
		if(SetFileValidData(hFile,fileSize))
			printf("有效数据长度设置成功\n");
		else
			printf("无法设置有效数据长度\n");
	else
		printf("无法拓展文件大小\n");
	CloseHandle(hFile);
	CloseHandle(hToken);
		system("pause");
	return 0;
}