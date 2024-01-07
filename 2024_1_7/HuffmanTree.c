#include<stdio.h>
#include<stdlib.h>

typedef struct TreeNode{
    int weight;
    int parent;
    int lchild;
    int rchild;
}TreeNode;

typedef struct HFTree{
    TreeNode* data;
    int length;
}HFTree;

HFTree* initHFTree(int* weight, int length){
    HFTree* T = (HFTree*)malloc(sizeof(HFTree));
    T->data = (TreeNode*)malloc(sizeof(TreeNode) * (2 * length - 1));
    for(int i = 0; i < length; i++){
        T->data[i].parent = 0;
        T->data[i].weight = weight[i];
        T->data[i].lchild = -1;
        T->data[i].rchild = -1;
    }
    T->length = length;
    return T;
}

int* getMin(HFTree* T){
    int min = 99999;
    int secondMin = 99999;
    int minIndex;
    int secondIndex;
    for(int i = 0; i < T->length; i++){
        if(T->data[i].parent == 0){ //容易忘记-----------------------------------------------------------------------------
            if(T->data[i].weight < min){
                min = T->data[i].weight;
                minIndex = i;
            }
        }
    }
    for(int i = 0; i < T->length; i++){
        if(T->data[i].parent == 0){//容易忘记-----------------------------------------------------------------------------
            if(T->data[i].weight < secondMin && i != minIndex){
                secondMin = T->data[i].weight;
                secondIndex = i;
            }
        }
    }
    int* res = (int*)malloc(sizeof(int) * 2);
    res[0] = minIndex;
    res[1] = secondIndex;
    return res;
}

void createHFTree(HFTree* T){
    int minIndex;
    int secondIndex;
    int length = 2 * T->length - 1;
    for(int i = T->length; i < length; i++){
        int* res = getMin(T);
        T->data[i].weight = T->data[res[0]].weight + T->data[res[1]].weight;
        T->data[i].parent = 0;
        T->data[i].lchild = res[0];
        T->data[i].rchild = res[1];
        T->data[res[0]].parent = i;
        T->data[res[1]].parent = i;
        T->length++;
    }
}

void preOrder(HFTree* T, int index){
    if(index != -1){
        printf("%d ", T->data[index].weight);
        preOrder(T, T->data[index].lchild);
        preOrder(T, T->data[index].rchild);
    }
}

int main(int argc, char* argv[]){
    int weight[7] = {5,1,3,6,11,2,4};
    HFTree* T = initHFTree(weight, 7);
    createHFTree(T);
    preOrder(T, T->length - 1);
    return 0;
}

