#ifndef REDBLACKTREE_H_
#define REDBLACKTREE_H_

class RedBlackTree {
  private:
    // 枚举节点颜色：只有黑色与红色
    enum COLOR { BLACK, RED };

    class Node {
      public:
        Node* parent; // 父节点
        Node* left;   // 左子节点
        Node* right;  // 右子节点
        COLOR color;  // 节点颜色
        int val;      // 节点的值

        Node(int val = 0);
        ~Node();
    };

    // 叶节点，只有一个实例，其中的值没有意义（默认为0）、其父、左子、右子节点均为nullptr
    Node* leaf;
    // 树的根节点，通过此指针可以得到整颗树
    Node* root;
    // 双黑节点的父节点，只有在删除操作后进行双黑修正时值才有意义，其余情况下均为nullptr
    Node* dBlackParent;

    // 初始化树节点，将其父、左子、右子节点均设置为leaf，颜色为红
    void InitNode(Node* node);

    // 在销毁树时递归地释放整颗树
    void DeleteRoot(Node* root);

    // 左旋
    void RotateL(Node* root);

    // 右旋
    void RotateR(Node* root);

    // 插入操作之后调整的几种情形
    // 情形1，当前节点为根
    void InsertCase1(Node* root);

    // 情形2，当前节点父节点为黑色
    void InsertCase2(Node* root);

    // 情形3，当前节点父节点与叔父节点均为红色
    void InsertCase3(Node* root);

    // 情形4，父节点为红色，叔父节点为黑色（包括为叶节点情形），当前节点为父节点的右（左）子节点，父节点为祖父节点的左（右）子节点
    // 即 祖父 - 父 - 当前 三个节点关系呈“折线”型
    void InsertCase4(Node* root);

    // 情形5，父节点为红色，叔父节点为黑色（包括为叶节点情形），当前节点为父节点的左（右）子节点，父节点为祖父节点的左（右）子节点
    // 即 祖父 - 父 - 当前 三个节点关系呈“直线”型
    void InsertCase5(Node* root);

    // 寻找root的前驱节点
    Node* FindLeftMax(Node* root);

    // 删除操作后，双黑修正的情形
    // 情形1，双黑节点已经是新的根节点
    void RemoveCase1(Node* root);
    // 情形2，兄弟节点为红色
    void RemoveCase2(Node* root);
    // 情形3，父节点、兄弟节点、兄弟节点的子节点均为黑色
    void RemoveCase3(Node* root);
    // 情形4，父节点为红色，兄弟节点、兄弟节点的子节点均为黑色
    void RemoveCase4(Node* root);
    // 情形5，当前节点为父节点的左（右）子节点、兄弟节点为黑色、兄弟节点的左（右）子节点为红色、兄弟节点的右（左）子节点为黑色
    // 即 父节点 - 兄弟节点 - 兄弟节点的红色子节点
    // 三者呈“折线”型（兄弟节点另一子节点为黑色）
    // 情形5处理后，将问题转化为情形6
    void RemoveCase5(Node* root);
    // 情形6，当前节点为父节点的左（右）子节点、兄弟节点为黑色、兄弟节点的左（左）子节点为红色
    // 即存在兄弟节点的红色子节点，使 父节点 - 兄弟节点 - 兄弟节点的红色子节点
    // 三者呈“直线”型（兄弟节点另一子节点可以为任意颜色）
    void RemoveCase6(Node* root);

    // 中序遍历树
    void Print(Node* root);

  public:
    RedBlackTree();
    ~RedBlackTree();

    // 在树中查找值为val的节点
    // 如果树中存在值为val的节点，返回1，表示查找成功
    // 否则返回0，表示查找失败，树中不存在值为val的节点
    int Find(int val);

    // 向以root为根节点的树中插入值为val的新节点
    // 如果成功插入则返回1，
    // 如果树中已经存在值为val的节点则不进行插入，此次插入操作失败，返回0
    int Insert(int val);

    // 在以root为根节点的树中删除值为val的节点
    // 如果该节点存在则删除，返回1，表示删除成功
    // 否则返回0，表示不存在值为val的节点，删除失败
    int Remove(int val);

    // 中序遍历树
    void Print();
};

#endif // !REDBLACKTREE_H_