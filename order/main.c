#include<stdio.h>
#include <stdlib.h>
struct order{
    int id;
    float bounty;
    struct order*next;
};
struct order* Orderadd(struct order);

int main()
{
    int tid;
    float tbounty;
    
    struct order*head=NULL;
    struct order *pre,*now;
    
    printf("please enter the id,q to quit");
    while(scanf("%d %f",&tid,&tbounty)==2)
    {
        now=(struct order*)malloc(sizeof(struct order));
        now->id=tid;
        now->bounty=tbounty;
        now->next=NULL;
        if(head==NULL){
            head=now;
        }
        else{
            pre->next=now;
        }
        pre=now;
        printf("next\n");
    }
    now=head;
    while(now!=NULL){
        printf("%d %f\n",now->id,now->bounty);
        now=now->next;
    }
    int number;
    printf("delete mode\n");
    
    // 持续接收暗杀名单
    while(scanf("%d", &number) == 1){
        
        // 1. 每次接到新任务，探子必须从头开始找！
        now = head;
        pre = NULL;

        // 2. 顺藤摸瓜：只要没走到死胡同 (now != NULL) 且 没找到目标 (now->id != number)
        // 探子就一直往后走
        while(now != NULL && now->id != number){
            pre = now;
            now = now->next;
        }

        // 3. 循环结束，验收成果
        // 如果 now 变成了 NULL，说明走到黑也没找到
        if (now == NULL) {
            printf("NO! 订单不存在\n");
            continue; // 直接去接下一个输入的数字
        }

        // 4. 找到了！开始执行搭桥和暗杀
        if (pre == NULL) {
            // 目标刚好是第一个节点（擒贼先擒王）
            head = now->next;
        } else {
            // 目标在中间或末尾（搭连心桥！）
            pre->next = now->next; 
        }

        // 5. 抹除目标
        free(now);
        printf("Deleted %d!\n", number);
    }

    printf("over");

    return 0;
}
