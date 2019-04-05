#ifndef AVLTREE_H_
#define AVLTREE_H_

class AVLTree {
  private:
    class AVLTreeNode {
      public:
        int val;              /// 当前结点所存的数值
        int height;           /// 当前结点的高度
        AVLTreeNode* left;    /// 左子树
        AVLTreeNode* right;   /// 右子树

        // 得到root结点的高度
        static int Height(AVLTreeNode* root);

        AVLTreeNode(int val = 0);
        ~AVLTreeNode();
    };

    // 内部树结构
    AVLTreeNode* root;

    // 计算root结点的高度
    void CalcHeight(AVLTreeNode* root);

    // 取得以root为根的树上的最大值结点
    AVLTreeNode* FindMax(AVLTreeNode* root);

    // 取得以root为根的树上的最小值结点
    AVLTreeNode* FindMin(AVLTreeNode* root);

    // LL情况，以root为根进行左单旋转
    AVLTreeNode* RotateL(AVLTreeNode* root);
    // LR情况，先以root结点左儿子为根进行右单旋转，再以root为根进行左单旋转
    AVLTreeNode* RotateLR(AVLTreeNode* root);
    // RR情况，以root为根进行右单旋转
    AVLTreeNode* RotateR(AVLTreeNode* root);
    // RL情况，先以root结点右儿子为根进行左单旋转，再以root为根进行右单旋转
    AVLTreeNode* RotateRL(AVLTreeNode* root);

    // 向AVL树内插入值为val的一个结点，返回插入该结点后，整个树的根结点
    // result返回插入结果，成功插入则返回1，如果该值已经存在则返回0
    AVLTreeNode* Insert(AVLTreeNode* root, int val, int& result);

    // 在AVL树中删除值为val的结点，如果不存在则跳过，返回删除该结点后，整个树的根结点
    // result返回删除结果，成功删除则返回1，如果该值不存在则返回0
    AVLTreeNode* Remove(AVLTreeNode* root, int val, int& result);

    // 在AVLTree销毁时，递归释放整颗树
    void DeleteRoot(AVLTreeNode* root);

    // 中序遍历整颗树
    void Print(AVLTreeNode* root);

  public:
    AVLTree();
    ~AVLTree();

    // 向AVL树内插入值为val的一个结点，若成功插入则返回1，若已存在些结点则返回0
    int Insert(int val);
    // 在AVL树中删除值为val的结点，若成功删除则返回1，若该结点不存在则返回0
    int Remove(int val);
    // 在AVL树中查找值为val的结点，该结点存在则返回1，否则返回0
    int Find(int val);

    // 中序遍历整颗树
    void Print();
};

#endif
