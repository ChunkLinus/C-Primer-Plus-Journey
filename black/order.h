#ifndef ORDER_H
#define ORDER_H

// 数据类型的定义
struct order {
    int id;
    float bounty;
    struct order* next;
};

// 操作这些数据的函数声明（接口）
struct order* AddOrder(struct order* head, int id, float bounty);
void PrintOrders(struct order* head);
struct order* DeleteOrder(struct order* head, int target_id);

#endif