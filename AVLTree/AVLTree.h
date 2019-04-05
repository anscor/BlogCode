#ifndef AVLTREE_H_
#define AVLTREE_H_

class AVLTree {
  private:
    class AVLTreeNode {
      public:
        int val;              /// 当前节点所存的数值
        int height;           /// 当前节点的高度
        AVLTreeNode* left;    /// 左子树
        AVLTreeNode* right;   /// 右子树

        // 得到root节点的高度
        static int Height(AVLTreeNode* root);

        AVLTreeNode(int val = 0);
        ~AVLTreeNode();
    };

    // 内部树结构
    AVLTreeNode* root;

    // 计算root节点的高度
    void CalcHeight(AVLTreeNode* root);

    // 取得以root为根的树上的最大值节点
    AVLTreeNode* FindMax(AVLTreeNode* root);

    // 取得以root为根的树上的最小值节点
    AVLTreeNode* FindMin(AVLTreeNode* root);

    // LL情况，以root为根进行右旋转
    AVLTreeNode* RotateLL(AVLTreeNode* root);
    // LR情况，先以root节点左儿子为根进行左旋转，再以root为根进行右旋转
    AVLTreeNode* RotateLR(AVLTreeNode* root);
    // RR情况，以root为根进行左旋转
    AVLTreeNode* RotateRR(AVLTreeNode* root);
    // RL情况，先以root节点右儿子为根进行右旋转，再以root为根进行左旋转
    AVLTreeNode* RotateRL(AVLTreeNode* root);

    // 向AVL树内插入值为val的一个节点，返回插入该节点后，整个树的根节点
    // result返回插入结果，成功插入则返回1，如果该值已经存在则返回0
    AVLTreeNode* Insert(AVLTreeNode* root, int val, int& result);

    // 在AVL树中删除值为val的节点，如果不存在则跳过，返回删除该节点后，整个树的根节点
    // result返回删除结果，成功删除则返回1，如果该值不存在则返回0
    AVLTreeNode* Remove(AVLTreeNode* root, int val, int& result);

    // 在AVLTree销毁时，递归释放整颗树
    void DeleteRoot(AVLTreeNode* root);

    // 中序遍历整颗树
    void Print(AVLTreeNode* root);

  public:
    AVLTree();
    ~AVLTree();

    // 向AVL树内插入值为val的一个节点，若成功插入则返回1，若已存在些节点则返回0
    int Insert(int val);
    // 在AVL树中删除值为val的节点，若成功删除则返回1，若该节点不存在则返回0
    int Remove(int val);
    // 在AVL树中查找值为val的节点，该节点存在则返回1，否则返回0
    int Find(int val);

    // 中序遍历整颗树
    void Print();
};

#endif
