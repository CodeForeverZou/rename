// Rename.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
char strpath[128];


void m_strftime(time_t time, char *pctime) {
	struct tm *t;
	t = localtime(&time);
	//					  2018-08-22 17:20:40 %X_不能用:
	strftime(pctime, 128, "%Y-%m-%d %H-%M-%S", t);
}

void strcopy(char *str, char *temp) {
	while (*str != '\0')
	{
		*temp++ = *str++;
	}
}

void strconcat(char *str, char *temp) {
	int n = strlen(str);
	while (n-->0)*str++;
	while (*temp!='\0')
	{
		*str++ = *temp++;
	}
	*str = '\0';
}

void Fileread(char *fpath) {
	struct _finddata_t fileinfo;
	long fHandle;

	char str[180];
	char temp[128], temp2[128];


	fHandle = _findfirst(fpath, &fileinfo);
	if (fHandle!=-1)
	{
		//跳过自身和目录文件夹
		while (!strcmp(fileinfo.name, ".") || !strcmp(fileinfo.name, "..") || (fileinfo.attrib & _A_SUBDIR)) {
			if (_findnext(fHandle, &fileinfo)) break;
		}
		do
		{
			//忽略目录，只检查文件
			if (!(fileinfo.attrib & _A_SUBDIR))
			{
				m_strftime(fileinfo.time_write, str);

				strcpy(temp, strpath);
				strconcat(temp, fileinfo.name);

				strcpy(temp2, strpath);
				strconcat(temp2, str);
				strcat(temp2, ".jpg");

				rename(temp, temp2);
			}
		} while (!_findnext(fHandle, &fileinfo));
	}
}



void FileRename(char str[]) {
	char temp[180], newf[128], oldf[128];

	struct _finddata_t fileinfo;
	long fHandle;
	fHandle = _findfirst(str, &fileinfo);

	if (fHandle!=-1)
	{
		do
		{
			strcpy(newf, strpath);
			strcpy(oldf, strpath);

			strcat(oldf, fileinfo.name);
			
			m_strftime(fileinfo.time_write, temp);
			strcat(newf, temp);
			strcat(newf, " 1.jpg");
			
			rename(oldf, newf);
		} while (!_findnext(fHandle,&fileinfo));
	}
}

int main()
{
	char fpath[128];
	printf("请输入文件目录:");
	scanf("%s%*c", &fpath);

	char str2[7] = "\\*.jpg";		//只检查jpg文件
	strcat(fpath, str2);

	int l = strlen(fpath) - 5;
	strncpy(strpath, fpath, l);
	strpath[l + 1] = '\0';

	//char str[128] = "E:\\photos\\new begin\\game\\*.*";

	Fileread(fpath);		//主程序，批量重命名（按修改日期）
	//FileRename(fpath);		//辅助程序，万一时间日期相同，加序号1…


	/*
	char str[12] = "hello";
	char str1[12] = " world";
	strconcat(str, str1);
	printf("%s", str);
	*/	
	//		E:\\photos\\1\\2.jpg"   E:\\photos\\1\\2018-07-19 13:27:34.jpg"	char[128]

	rename("E:\\photos\\1\\1.jpg", "E:\\photos\\1\\2.jpg");
	system("pause");
    return 0;
}

