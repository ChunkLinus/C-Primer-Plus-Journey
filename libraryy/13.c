#include <stdio.h>
#include <stdlib.h> // 提供 exit() 和 EXIT_FAILURE

int main() {
    FILE *fp; // 我们的“文件钥匙”，贯穿全场
    char buffer[256];
    int num;

    printf("========== 第一阶段：花式写入文本文件 (w 模式) ==========\n");
    // 【1. 打开文件写入】 "w" 模式：文件不存在则创建，存在则清空重写
    fp = fopen("ch13_demo.txt", "w");
    if (fp == NULL) {
        fprintf(stderr, "错误：无法创建文件！\n"); // 报错最好用 stderr
        exit(EXIT_FAILURE); 
    }

    // 【2. 字符串写入】 fputs：整句写入，不会自动加换行，需手动加 '\n'
    fputs("Hello General!\n", fp);
    fputs("This is the C Primer Plus Chapter 13 Review.\n", fp);

    // 【3. 格式化写入】 fprintf：和 printf 一模一样，只是存进了硬盘
    fprintf(fp, "Mission ID: %d, Status: %s\n", 404, "Active");

    // 【4. 逐字符写入】 fputc：一次只写一个字符
    fputc('A', fp);
    fputc('\n', fp);

    // 【5. 写入完毕，拔钥匙关门】 这一步极其重要，确保数据从内存刷新到硬盘
    fclose(fp);
    printf("--> ch13_demo.txt 写入并关闭成功。\n\n");


    printf("========== 第二阶段：花式读取文本文件 (r 模式) ==========\n");
    // 【6. 打开文件读取】 "r" 模式：只读。文件必须存在，否则返回 NULL
    fp = fopen("ch13_demo.txt", "r");
    if (fp == NULL) {
        fprintf(stderr, "错误：找不到要读取的文件！\n");
        exit(EXIT_FAILURE);
    }

    // 【7. 格式化读取】 fscanf：遇到空格或换行就会停下
    // 注意：读取字符串不需要 &，读取整数必须加 &
    fscanf(fp, "%s", buffer); 
    printf("1. fscanf 读到的第一个词: %s\n", buffer); 
    
    // 【8. 按行读取】 fgets：接着上面的位置，读满一行（包含换行符）或达到最大长度
    // sizeof(buffer) 防止数组越界，非常安全
    fgets(buffer, sizeof(buffer), fp);
    printf("2. fgets 读完第一行剩下的部分: %s", buffer);

    // 【9. 逐字符读取直到末尾】 fgetc 与 EOF 判断
    printf("3. fgetc 逐字读取剩下的所有内容:\n");
    int ch; // 注意！接收 fgetc 必须用 int，因为 EOF(通常是-1) 可能超出 char 的范围
    while ((ch = fgetc(fp)) != EOF) {
        putchar(ch); // 打印到屏幕
    }
    fclose(fp);
    printf("\n--> 读取演示完毕，文件关闭。\n\n");


    printf("========== 第三阶段：光标控制与修改 (r+ 模式) ==========\n");
    // 【10. 读写模式】 "r+" 模式：可读可写，但不清空原文件
    fp = fopen("ch13_demo.txt", "r+");
    if (fp != NULL) {
        // 【11. 定位光标】 fseek：(文件指针, 偏移字节数, 起点)
        // SEEK_END = 文件末尾，SEEK_SET = 文件开头，SEEK_CUR = 当前位置
        fseek(fp, 0L, SEEK_END); // 光标移动到最后
        
        // 【12. 获取光标位置】 ftell：返回当前光标离文件开头有多少个字节
        long fileSize = ftell(fp);
        printf("文件总大小为: %ld 字节\n", fileSize);

        // 【13. 倒回开头】 rewind：等价于 fseek(fp, 0L, SEEK_SET);
        rewind(fp);

        // 【14. 精确修改】 把光标向后移动 6 个字节 (刚好跳过 "Hello ")
        fseek(fp, 6L, SEEK_SET);
        fputs("C_God", fp); // 覆盖写入，把 "General" 变成了 "C_God  "
        
        fclose(fp);
        printf("--> 文件内部光标定位与修改完成。\n\n");
    }


    printf("========== 第四阶段：二进制大挪移 (rb / wb 模式) ==========\n");
    // 【15. 二进制模式】 "rb" 和 "wb"：通常用于复制图片、音频或结构体数组
    // 虽然这里是文本文件，但二进制读取会原封不动复制底层字节
    FILE *src = fopen("ch13_demo.txt", "rb");
    FILE *dest = fopen("ch13_demo_copy.bin", "wb");
    
    if (src != NULL && dest != NULL) {
        size_t bytesRead;
        // 【16. 块读写】 fread / fwrite：一次性搬运一大块内存
        // 参数：(存放数据的数组, 每个元素的大小, 要读的元素个数, 文件指针)
        while ((bytesRead = fread(buffer, sizeof(char), sizeof(buffer), src)) > 0) {
            fwrite(buffer, sizeof(char), bytesRead, dest);
        }
        printf("--> 二进制复制完成，生成了 ch13_demo_copy.bin\n");
        fclose(src);
        fclose(dest);
    }

    printf("========== 所有第13章任务执行完毕！ ==========\n");
    return 0;
}