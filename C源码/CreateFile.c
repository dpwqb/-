#include <stdio.h>
#include <Windows.h>
#pragma comment(lib,"advapi32.lib")
BOOL SetPrivilege(HANDLE hToken,LPCTSTR lpszPrivilege,BOOL bEnablePrivilege)
{
	TOKEN_PRIVILEGES tp={0};
	LUID luid;
	if(!LookupPrivilegeValue(NULL,lpszPrivilege,&luid))
	{
		printf("�޷�����Ȩ��ֵ\n");
		return FALSE;
	}
	tp.PrivilegeCount=1;
	tp.Privileges[0].Luid=luid;
	tp.Privileges[0].Attributes=bEnablePrivilege?SE_PRIVILEGE_ENABLED:0;
	if(!AdjustTokenPrivileges(hToken,FALSE,&tp,sizeof(TOKEN_PRIVILEGES),NULL,NULL))
	{
		printf("�޷�����������Ȩ\n");
		return FALSE;
	}
	if(GetLastError()==ERROR_NOT_ALL_ASSIGNED)
	{
		printf("�޷����������������Ȩ\n");
		return FALSE;
	}
	return TRUE;
}
BOOL ParameterError()	//���������������
{
	printf("������ʽ����");
	exit(1);
}
ULONGLONG FileSize(LPCSTR fsb)	//�������/s����ת��ΪByteֵ������
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
	char fileName[MAX_PATH];	//�ļ�·�������ƣ�
	ULONGLONG fileSize;	//�ļ���С
	BOOL isTUI=FALSE;
	switch(argc)
	{
	case 1:	//�޲����У�����TUI����
		printf("\n\t��ȷ���Թ���ԱȨ�����У�\n\
�����ڵ�ǰĿ¼�����򸲸�ָ�����ƺ���Ч���ݿռ��С���ļ�\n\
CLI�����봫�ݡ�/h���������ɲ鿴������ʹ�÷���\n\n\
�����봴�����ļ���С������+��λ���磺1.44M����");
		fileSize=FileSize((LPCSTR)gets(fileName));
		printf("�������ļ�·��(��Ҫ���˫����)��");
		gets(fileName);
		isTUI=TRUE;
		break;
	case 2:	//һ����������Ƿ�Ϊ/h����
	{
		LPCSTR selfName=strrchr(argv[0],'\\')?strrchr(argv[0],'\\')+1:argv[0];
		if(!strcmp(argv[1],"/h"))
		{
			printf("\
\n\t(c) ��dpoqb.top������������Ȩ����\n\
%s [/s] [FileSize] [/n] [File_Path&Name]\n\
\t            /s������ָ���ļ�����Ч���ݳ��ȡ�\n\
\t      FileSize�����ڵ���0KB��С��16EB��ֵ�����ֺ���Ҫ��ӵ�λ�����ޣ�K|M|G|T����\n\
\t            /n������ָ��Ŀ���ļ�·�������ơ�\n\
\tFile_Path&Name���ļ���·�����������ո���������ţ���\n\
\n����\t%s /n \"T:\\Create New File.bin\" /s 3.99g\n\
\tִ�д�����������T�̴���һ����СΪ3.99GB������Ϊ��Create New File.bin�����ļ���\n\
\nע���������������д˳��򣬼�ΪTUI���棬�ɰ�ָʾ�������ݡ�\n\
",selfName,selfName);
			return 0;
		}
		ParameterError();
	}
	case 5:	//�ĸ�����
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
		printf("�޷��򿪽�������\n");
		if(isTUI)
			system("pause");
		return 3;
	}
	if(!SetPrivilege(hToken,SE_MANAGE_VOLUME_NAME,TRUE))
	{
		printf("��ȡSE_MANAGE_VOLUME_NAMEȨ��ʧ��\n\t�����Ƿ��Թ���ԱȨ�����У�\n");
		CloseHandle(hToken);
		if(isTUI)
			system("pause");
		return 2;
	}
	HANDLE hFile=CreateFileA(fileName,GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	if(hFile==INVALID_HANDLE_VALUE)
	{
		printf("�޷�����%s�ļ�\n",fileName);
		CloseHandle(hToken);
		if(isTUI)
			system("pause");
		return 1;
	}
	LARGE_INTEGER liDistanceToMove;
	liDistanceToMove.QuadPart=fileSize;
	SetFilePointerEx(hFile,liDistanceToMove,NULL,FILE_BEGIN);	//����hFile���ļ�ָ����ļ���ʼλ�����Ų��fileSize����С�Ŀռ�
	if(SetEndOfFile(hFile))	//����hFile���ļ���ָ������λ������Ϊ�ļ�����λ��
		if(SetFileValidData(hFile,fileSize))	//���á�hFile���ļ�����Ч���ݳ���Ϊ��fileSize��
			printf("%s�ļ�����Ч���ݳ������óɹ�\n",fileName);
		else
			printf("�ɹ���չ%s�ļ��Ĵ�С�����޷���������Ч���ݳ���\n",fileName);
	else
		printf("�ɹ�����%s�ļ������޷���չ���ļ���С\n",fileName);
	CloseHandle(hFile);
	CloseHandle(hToken);
	if(isTUI)
		system("pause");
	return 0;
}