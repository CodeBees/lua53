// cplusplusInvokeLua.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <tchar.h>
#include <Windows.h>
#include <string>


int main()
{

	//

	//vscode-debug.dll


	HMODULE hdll = nullptr;


	do
	{


		TCHAR szModulePath[MAX_PATH];

		GetModuleFileName(NULL, szModulePath, MAX_PATH);


		std::wstring  strModelpath = szModulePath;

		std::wstring strDLLPath = strModelpath.substr(0, strModelpath.find_last_of('\\') + 1);
		strDLLPath = strDLLPath + L"vscode-debug.dll";

		hdll = LoadLibrary(strDLLPath.c_str());
		if (hdll == nullptr)
		{
			printf("���ض�̬��vscode-debug.dllʧ��");
			int code = GetLastError();
			break;
		}

		lua_State * L = nullptr;

		/* ��ʼ�� Lua */
		L = luaL_newstate();

		/* ����Lua������ */
		luaL_openlibs(L);

		/* ���нű� */

		//lua�ű�ʵ��·��
		if (LUA_OK != luaL_dofile(L, "./script/func.lua"))
		{
			printf("����lua�ű�ʧ��");
			return  -1;
		}


		//��ȡlua�е�showinfo����  
		lua_getglobal(L, "showinfo");
		//cpp �����޲�����lua�������޷���ֵ  
		lua_pcall(L, 0, 0, 0);
		//����������ջ��Ҳ���Բ�����  



		const char * pstr = "�����������";
		lua_getglobal(L, "showstr");
		lua_pushstring(L, pstr);
		//cpp ����һ�������ĵ�lua�������޷���ֵ  
		lua_pcall(L, 1, 0, 0);


		lua_getglobal(L, "add");
		//����������ѹջ  
		lua_pushinteger(L, 2);
		lua_pushinteger(L, 3);
		lua_pcall(L, 2, 1, 0);
		printf("lua add function return val is %d \n", static_cast<int>(lua_tointeger(L, -1)));


		/* ���Lua */
		lua_close(L);


	} while (false);

	if(hdll!=nullptr)
	{
		FreeLibrary(hdll);
	}

	return 0;
}
