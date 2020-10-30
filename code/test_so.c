#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

//動態連結庫路徑
#define LIB_CACULATE_PATH "./libcaculate.so"

//函式指標
typedef int (*CAC_FUNC)(int, int);

int main()
{
	void *handle;
	char *error;
	CAC_FUNC cac_func = NULL;
	//開啟動態連結庫
	handle = dlopen(LIB_CACULATE_PATH, RTLD_LAZY);
	if (!handle)
	{
		fprintf(stderr, "%s\n", dlerror());
		exit(EXIT_FAILURE);
	}

	//清除之前存在的錯誤
	dlerror();
	
	//獲取一個函式
	*(void **) (&cac_func) = dlsym(handle, "add");
	if ((error = dlerror()) != NULL)
	{
		fprintf(stderr, "%s\n", error);
		exit(EXIT_FAILURE);
	}
	printf("add: %d\n", (*cac_func)(2,7));

	cac_func = (CAC_FUNC)dlsym(handle, "sub");
	printf("sub: %d\n", cac_func(9,2));

	cac_func = (CAC_FUNC)dlsym(handle, "mul");
	printf("mul: %d\n", cac_func(3,2));

	cac_func = (CAC_FUNC)dlsym(handle, "div");
	printf("div: %d\n", cac_func(8,2));

	//關閉動態連結庫
	dlclose(handle);
	exit(EXIT_SUCCESS);
}
