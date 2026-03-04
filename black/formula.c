#include <stdio.h>
#include <stdlib.h>
#include "order.h"

// 1. 添加新订单
struct order* AddOrder(struct order* head, int id, float bounty) {
    // 局部变量：在函数内部招募新兵，并分配内存
    struct order* now = (struct order*)malloc(sizeof(struct order));
    now->id = id;
    now->bounty = bounty;
    now->next = NULL; // 新兵的后面暂时没有别人

    // 判断队伍是否为空
    if (head == NULL) {
        head = now; // 队伍没人，新兵直接当排头（头节点）
    } else {
        // 队伍有人，派局部探子 temp 从头开始往后找队尾
        struct order* temp = head;
        
        // 只要当前人的后面还有人，探子就继续往下走
        while (temp->next != NULL) { 
            temp = temp->next;
        }
        
        // 循环结束时，temp 一定停在队伍的最后一个人身上
        temp->next = now; // 让最后一个人牵住新兵
    }
    
    return head; // 将最新的头指针汇报给 main 函数
}

// 2. 打印订单
void PrintOrders(struct order* head) {
    // 局部探子 now 负责点名
    struct order* now = head;
    while (now != NULL) {
        printf("%d %f\n", now->id, now->bounty);
        now = now->next;
    }
}

// 3. 执行暗杀（删除）
struct order* DeleteOrder(struct order* head, int target_id) {
    // 局部探子，每次执行任务才设立
    struct order* pre = NULL;
    struct order* now = head;

    // 索敌：没走到死胡同 且 没找到目标，就一直往后走
    while (now != NULL && now->id != target_id) {
        pre = now;
        now = now->next;
    }

    // 结局1：扑空了
    if (now == NULL) { // 注意这里是双等号 ==
        printf("ni ma si le: target not found\n");
        return head; // 没找到，原样返回头指针
    }

    // 结局2：找到了，开始处理
    if (pre == NULL) {
        // 擒贼先擒王：目标刚好是第一个节点
        head = now->next; 
    } else {
        // 搭连心桥：目标在队伍中间或末尾
        pre->next = now->next; 
    }

    // 抹除目标
    free(now);
    
    return head;
}