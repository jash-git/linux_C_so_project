LINUX C 動態 載入/引用 函式庫/函數庫（so/dll）「linux_C_so_project」
編譯so
    gcc -fPIC -shared caculate.c -o libcaculate.so 
        libcaculate.so 
編譯執行檔
    gcc -rdynamic -o main test_so.c -ldl
