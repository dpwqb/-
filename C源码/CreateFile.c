#include <stdio.h>
#include <Windows.h>
BOOL SetPrivilege(HANDLE hToken,LPCTSTR lpszPrivilege,BOOL bEnablePrivilege)
{
	TOKEN_PRIVILEGES tp={0};
	LUID luid;
	if(!LookupPrivilegeValue(NULL,lpszPrivilege,&luid))
	{
		printf("无法查找权限值\n");
		return FALSE;
	}
	tp.PrivilegeCount=1;
	tp.Privileges[0].Luid=luid;
	tp.Privileges[0].Attributes=bEnablePrivilege?SE_PRIVILEGE_ENABLED:0;
	if(!AdjustTokenPrivileges(hToken,FALSE,&tp,sizeof(TOKEN_PRIVILEGES),NULL,NULL))
	{
		printf("无法调整令牌特权\n");
		return FALSE;
	}
	if(GetLastError()==ERROR_NOT_ALL_ASSIGNED)
	{
		printf("无法分配所有请求的特权\n");
		return FALSE;
	}
	return TRUE;
}
BOOL ParameterError()	//参数错误结束程序
{
	printf("参数格式错误！");
	exit(1);
}
ULONGLONG FileSize(LPCSTR fsb)	//将传入的/s参数转换为Byte值并返回
{
	char *xb;
	double fs=strtod(fsb,&xb);
	if(fs<0)
		ParameterError();
	if(xb[0]>='a'&&xb[0]<='z')
		xb[0]-=32;
	if(!xb[1])
		switch(xb[0])
		{
		case 'K':
			return (ULONGLONG)(fs*1024);
		case 'M':
			return (ULONGLONG)(fs*1048576);
		case 'G':
			return (ULONGLONG)(fs*1073741824);
		case 'T':
			return (ULONGLONG)(fs*1099511627776);
		}
	ParameterError();
}
int main(int argc,LPCSTR argv[])
{
	char fileName[MAX_PATH];	//文件路径（名称）
	ULONGLONG fileSize;	//文件大小
	BOOL isTUI=FALSE;
	switch(argc)
	{
	case 1:	//无参运行，进入TUI界面
		printf("\n\t请确保以管理员权限运行！\n\
用于在当前目录创建或覆盖指定名称和有效数据空间大小的文件\n\
CLI运行请传递“/h”参数即可查看命令行使用方法\n\n\
请输入创建的文件大小（数字+单位，如：1.44M）：");
		fileSize=FileSize(gets(fileName));
		printf("请输入文件路径(不要添加双引号)：");
		gets(fileName);
		isTUI=TRUE;
		break;
	case 2:	//一个参数检测是否为/h参数
	{
		LPCSTR selfName=strrchr(argv[0],'\\')?strrchr(argv[0],'\\')+1:argv[0];
		if(!strcmp(argv[1],"/h"))
		{
			printf("\
\n\t(c) →dpoqb.top←，保留所有权利。\n\
%s [/s] [FileSize] [/n] [File_Path&Name]\n\
\t            /s：用于指定文件的有效数据长度。\n\
\t      FileSize：大于等于0KB且小于16EB的值，数字后需要添加单位（仅限：K|M|G|T）。\n\
\t            /n：用于指定目标文件路径和名称。\n\
\tFile_Path&Name：文件的路径（若包含空格请添加引号）。\n\
\n例：\t%s /n \"T:\\Create New File.bin\" /s 3.99g\n\
\t执行此行命令后会在T盘创建一个大小为3.99GB且名称为“Create New File.bin”的文件。\n\
\n注：若不带参数运行此程序，即为TUI界面，可按指示输入数据。\n\
",selfName,selfName);
			return 0;
		}
		ParameterError();
	}
	case 5:	//四个参数
	{
		char ptmp[5]={'\0'};
		strcat(strcat(ptmp,argv[1]),argv[3]);
		if(!(strcmp(ptmp,"/s/n")&&strcmp(ptmp,"/n/s")))
			if(!strcmp(argv[1],"/s"))
			{
				fileSize=FileSize(argv[2]);
				strcpy(fileName,argv[4]);
			}else{
				fileSize=FileSize(argv[4]);
				strcpy(fileName,argv[2]);
			}
		else
			ParameterError();
	}
		break;
	default:
		ParameterError();
		break;
	}
	HANDLE hToken;
	if(!OpenProcessToken(GetCurrentProcess(),TOKEN_ADJUST_PRIVILEGES|TOKEN_QUERY,&hToken))
	{
		printf("无法打开进程令牌\n");
		if(isTUI)
			system("pause");
		return 3;
	}
	if(!SetPrivilege(hToken,SE_MANAGE_VOLUME_NAME,TRUE))
	{
		printf("获取SE_MANAGE_VOLUME_NAME权限失败\n\t请检查是否以管理员权限运行！\n");
		CloseHandle(hToken);
		if(isTUI)
			system("pause");
		return 2;
	}
	HANDLE hFile=CreateFileA(fileName,GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	if(hFile==INVALID_HANDLE_VALUE)
	{
		printf("无法创建%s文件\n",fileName);
		CloseHandle(hToken);
		if(isTUI)
			system("pause");
		return 1;
	}
	LARGE_INTEGER liDistanceToMove;
	liDistanceToMove.QuadPart=fileSize;
	SetFilePointerEx(hFile,liDistanceToMove,NULL,FILE_BEGIN);	//将“hFile”文件指针从文件起始位置向后挪“fileSize”大小的空间
	if(SetEndOfFile(hFile))	//将“hFile”文件的指针所在位置设置为文件结束位置
		if(SetFileValidData(hFile,fileSize))	//设置“hFile”文件的有效数据长度为“fileSize”
			printf("%s文件的有效数据长度设置成功\n",fileName);
		else
			printf("成功拓展%s文件的大小，但无法设置其有效数据长度\n",fileName);
	else
		printf("成功创建%s文件，但无法拓展其文件大小\n",fileName);
	CloseHandle(hFile);
	CloseHandle(hToken);
	if(isTUI)
		system("pause");
	return 0;
}