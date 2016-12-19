// cplusplusInvokeLua.cpp : 定义控制台应用程序的入口点。
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
			printf("加载动态库vscode-debug.dll失败");
			int code = GetLastError();
			break;
		}

		lua_State * L = nullptr;

		/* 初始化 Lua */
		L = luaL_newstate();

		/* 载入Lua基本库 */
		luaL_openlibs(L);

		/* 运行脚本 */

		//lua脚本实际路径
		if (LUA_OK != luaL_dofile(L, "./script/func.lua"))
		{
			printf("加载lua脚本失败");
			return  -1;
		}


		//获取lua中的showinfo函数  
		lua_getglobal(L, "showinfo");
		//cpp 调用无参数的lua函数，无返回值  
		lua_pcall(L, 0, 0, 0);
		//主动清理堆栈，也可以不调用  



		const char * pstr = "世界如此美好";
		lua_getglobal(L, "showstr");
		lua_pushstring(L, pstr);
		//cpp 调用一个参数的的lua函数，无返回值  
		lua_pcall(L, 1, 0, 0);


		lua_getglobal(L, "add");
		//参数从左到右压栈  
		lua_pushinteger(L, 2);
		lua_pushinteger(L, 3);
		lua_pcall(L, 2, 1, 0);
		printf("lua add function return val is %d \n", static_cast<int>(lua_tointeger(L, -1)));


		/* 清除Lua */
		lua_close(L);


	} while (false);

	if(hdll!=nullptr)
	{
		FreeLibrary(hdll);
	}

	return 0;
}

