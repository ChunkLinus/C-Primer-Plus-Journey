#include<stdio.h>
#include"order.h"

int main(void)
{
    int tid;
    float tbounty;
    struct order*head=NULL;

    printf("please enter the game:\n");
    while(scanf("%d %f", &tid, &tbounty) == 2) {
        head = AddOrder(head, tid, tbounty);
        printf("next\n");
    }
    
    // 2. 打印阶段
    PrintOrders(head);
    
    // ================= 新增：清理缓冲区 =================
    int c;
    while ((c = getchar()) != '\n' && c != EOF); 
    // 这行代码的意思是：只要读取到的不是回车符（\n）也不是文件结束符，就把通道里的字符吃掉扔了
    // ====================================================

    // 3. 删除阶段
    int number;
    printf("delete mode. Enter id to delete:\n");
    while(scanf("%d", &number) == 1) {
        head = DeleteOrder(head, number);
    }
    
    PrintOrders(head);
    printf("over\n");
    return 0;
}
