#include <stdio.h>
#include <stdlib.h>

// 1. 定义二叉树节点（从“单行道”变成“双岔路”）
struct TreeNode {
    int id;
    struct TreeNode* left;  // 左手牵着比自己小的人
    struct TreeNode* right; // 右手牵着比自己大的人
};

// 2. 制造新节点的工厂函数
struct TreeNode* CreateNode(int id) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->id = id;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// 3. 核心战术：递归插入新节点
struct TreeNode* Insert(struct TreeNode* root, int id) {
    // 结局条件：如果当前位置是空的，就在这里安营扎寨！
    if (root == NULL) {
        return CreateNode(id);
    }

    // 寻路逻辑：如果新来的 id 比当前指挥官小，发往左营
    if (id < root->id) {
        root->left = Insert(root->left, id);
    } 
    // 寻路逻辑：如果新来的 id 比当前指挥官大，发往右营
    else if (id > root->id) {
        root->right = Insert(root->right, id);
    }
    
    // 如果相等，这里什么都不做（假设不存重复元素）
    
    return root; // 返回当前节点的地址
}

// 4. 核心战术：中序遍历（全军点名）
void InorderTraversal(struct TreeNode* root) {
    if (root != NULL) {
        InorderTraversal(root->left);  // 先把左营的兵点完
        printf("%d ", root->id);       // 点指挥官自己的名
        InorderTraversal(root->right); // 最后点右营的兵
    }
}

int main() {
    struct TreeNode* root = NULL;

    // 录入一批杂乱无章的数据
    int data[] = {50, 30, 70, 20, 40, 60, 80};
    int n = sizeof(data) / sizeof(data[0]);

    printf("Start inserting data...\n");
    for (int i = 0; i < n; i++) {
        root = Insert(root, data[i]);
    }

    // 见证奇迹的时刻：打印出来的数据会自动按从小到大排序
    printf("Inorder Traversal (Sorted): \n");
    InorderTraversal(root);
    printf("\n");

    return 0;
}