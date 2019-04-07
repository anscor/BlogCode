
#include "RedBlackTree.h"
#include <iostream>

RedBlackTree::Node::Node(int val) {
    this->val = val;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
    color = RED;
}

RedBlackTree::Node::~Node() {
    this->val = 0;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
}

RedBlackTree::RedBlackTree() {
    leaf = new Node(0);
    leaf->color = BLACK;
    root = nullptr;
    dBlackParent = nullptr;
}

void RedBlackTree::DeleteRoot(Node* root) {
    if (!root) return;
    if (root->left != leaf) DeleteRoot(root->left);
    if (root->right != leaf) DeleteRoot(root->right);
    delete root;
}

RedBlackTree::~RedBlackTree() {
    DeleteRoot(root);
    delete leaf;
}

void RedBlackTree::InitNode(Node* root) {
    root->left = leaf;
    root->right = leaf;
    root->parent = leaf;
    root->color = RED;
}

void RedBlackTree::RotateL(Node* root) {

    // 处理子关系
    Node* temp = root->right;
    root->right = temp->left;
    temp->left = root;

    // 处理父关系
    if (root->right != leaf) root->right->parent = root;
    Node* p = root->parent;

    // 将旋转好的树接回原来root的位置
    if (p == leaf) {
        temp->parent = leaf;
        root->parent = temp;
        this->root = temp;
    } else {
        temp->parent = p;
        root->parent = temp;
        if (root == p->left)
            p->left = temp;
        else
            p->right = temp;
    }
}

void RedBlackTree::RotateR(Node* root) {
    // 处理子关系
    Node* temp = root->left;
    root->left = temp->right;
    temp->right = root;

    // 处理父关系
    if (root->left != leaf) root->left->parent = root;
    Node* p = root->parent;

    // 将旋转好的树接回原来root的位置
    if (p == leaf) {
        temp->parent = leaf;
        root->parent = temp;
        this->root = temp;
    } else {
        temp->parent = p;
        root->parent = temp;
        if (root == p->left)
            p->left = temp;
        else
            p->right = temp;
    }
}

int RedBlackTree::Insert(int val) {
    // 如果当前为空树，则直接创建一个新的节点做为根节点
    // 插入成功
    if (!root) {
        root = new Node(val);
        InitNode(root);
        root->color = BLACK;
        return 1;
    }

    Node* temp = root;

    while (1) {
        // 如果在树中找到了值为val的节点，则不进行插入，此次插入操作失败，返回0
        if (temp->val == val) return 0;

        // 如果当前节点值小于val，则应插入当前节点的右子树中
        if (temp->val < val) {
            // 如果当前节点的右子树为叶节点，则直接插入新的节点并返回
            if (temp->right == leaf) {
                Node* t = new Node(val);
                InitNode(t);
                temp->right = t;
                t->parent = temp;

                // 插入新节点后进行平衡性判断与调整
                InsertCase1(t);
                return 1;
            }
            // 否则向右子树插入
            else
                temp = temp->right;
        }
        // 否则表示当前节点的值大于val，则应插入当前节点的左子树中
        else {
            // 如果当前节点的左子树为叶节点，则直接插入新的节点并返回
            if (temp->left == leaf) {
                Node* t = new Node(val);
                InitNode(t);
                temp->left = t;
                t->parent = temp;

                // 插入新节点后进行平衡性判断与调整
                InsertCase1(t);
                return 1;
            }
            // 否则向左子树插入
            else
                temp = temp->left;
        }
    }
    return 0;
}

void RedBlackTree::InsertCase1(Node* root) {
    // 树为空，直接返回
    if (!root) return;
    // 当前节点为根节点，染黑当前节点并返回
    if (root->parent == leaf) {
        root->color = BLACK;
        return;
    }
    // 否则进入情形2判断
    InsertCase2(root);
}

void RedBlackTree::InsertCase2(Node* root) {
    // 如果父节点为黑色，那么插入操作不会对树的性质产生影响
    // 插入后的树仍旧满足5条性质，直接返回即可
    if (root->parent->color == BLACK) return;
    // 否则进入情形3判断
    else
        InsertCase3(root);
}

void RedBlackTree::InsertCase3(Node* root) {
    // 情形3则代表父节点为红色，那么父节点必定也有父节点（即父节点不可能为根节点，性质1）
    // 那么必定存在祖父节点
    // 父节点
    Node* p = root->parent;
    // 祖父节点
    Node* g = p->parent;
    // 叔父节点
    // 如果父节点为祖父节点的左子节点，那么叔父节点就应为祖父节点的右子节点，反之亦然
    Node* u = g->left == p ? g->right : g->left;

    // 如果叔父节点为红色（如果叔父节点为叶节点，则不可能为红色）
    if (u->color == RED) {
        // 重绘祖父节点为红色
        g->color = RED;
        // 重绘父节点、叔父节点为黑色
        p->color = BLACK;
        u->color = BLACK;

        // 进行祖父节点的调整
        InsertCase1(g);
    }
    // 进入情形4判断
    else
        InsertCase4(root);
}

void RedBlackTree::InsertCase4(Node* root) {
    // 情形4同情形3，一定存在祖父节点
    // 此时叔父节点为黑色，如果叔父节点不存在，即为叶节点，也为黑色，合并讨论
    // 并且此时当前节点为父节点的右（左）子节点，父节点为祖父节点的左（右）子节点
    // 即 祖父 - 父 - 当前 三个节点关系呈“折线”型

    // 父节点
    Node* p = root->parent;
    // 祖父节点
    Node* g = p->parent;
    // 叔父节点
    // 如果父节点为祖父节点的左子节点，那么叔父节点就应为祖父节点的右子节点，反之亦然
    Node* u = g->left == p ? g->right : g->left;

    if (p->right == root && g->left == p) {
        RotateL(p);
        InsertCase5(root->left);
    } else if (p->left == root && g->right == p) {
        RotateR(p);
        InsertCase5(root->right);
    } else
        InsertCase5(root);
}

void RedBlackTree::InsertCase5(Node* root) {
    // 此情形同情形3，一定存在祖父节点
    // 此时叔父节点为黑色，如果叔父节点不存在，即为叶节点，也为黑色，合并讨论
    // 并且此时当前节点为父节点的左（右）子节点，父节点为祖父节点的左（右）子节点
    // 即 祖父 - 父 - 当前 三个节点关系呈“直线”型

    // 父节点
    Node* p = root->parent;
    // 祖父节点
    Node* g = p->parent;
    // 叔父节点
    // 如果父节点为祖父节点的左子节点，那么叔父节点就应为祖父节点的右子节点，反之亦然
    Node* u = g->left == p ? g->right : g->left;

    if (p->left == root && g->left == p)
        RotateR(g);
    else
        RotateL(g);
    g->color = RED;
    p->color = BLACK;
}

int RedBlackTree::Find(int val) {
    Node* temp = root;
    while (temp) {
        if (temp == leaf) return 0;
        if (temp->val == val) return 1;
        if (temp->val < val)
            temp = temp->right;
        else
            temp = temp->left;
    }
    return 0;
}

RedBlackTree::Node* RedBlackTree::FindLeftMax(Node* root) {
    Node* temp = root->left;
    while (temp) {
        if (temp->right == leaf) return temp;
        temp = temp->right;
    }
}

int RedBlackTree::Remove(int val) {

    // 删除时，讨论节点子节点时叶子节点不被当做子节点
    // 即当一个节点两个子节点均为叶子节点时，则称其没有子节点
    // 其余情况类似

    // 空树删除失败
    if (!root) return 0;

    Node* temp = root;
    // 替代节点，真正被删除的节点
    // 如果待删除节点有两个子节点时，t为待删除节点的前驱
    // 否则t为待删除节点本身
    Node* t;
    while (1) {
        // 查找到了叶子节点也没有找到值为val的节点
        // 表示树内没有值为val的节点
        // 返回0，表示删除失败
        if (temp == leaf) return 0;

        // 当前节点的值小于val，表示值为val的节点只可能存在于右子树中
        if (temp->val < val) temp = temp->right;
        // 当前节点的值大于val，表示值为val的节点只可能存在于左子树中
        else if (temp->val > val)
            temp = temp->left;

        // 当前即为要删除的节点
        else {
            // 待删除节点有两个子节点（非叶节点）
            // 则将当前节点的值更改为其前驱节点的值
            // 并删除其前驱节点
            if (temp->left != leaf && temp->right != leaf) {
                t = FindLeftMax(temp);
                temp->val = t->val;
            }
            // 如果待删除节点只有一个子节点或没有子节点
            // 那么真正被删除的节点就是当前节点
            else
                t = temp;
            break;
        }
    }

    // 在树中找到了值为val的节点，且找出了真正要删除的节点
    // 其一定只有一个子节点或没有子节点

    // 删除节点为根节点
    if (t == root) {
        // 删除根节点
        delete root;
        // 根节点置空，便于再进行插入
        root = nullptr;
        return 1;
    }

    // 删除节点的父节点
    Node* p = t->parent;
    // 删除节点的子节点（最多只有一个节点）
    Node* s = t->left == leaf ? t->right : t->left;

    // 先删除节点（先将其从树中去除），再进行调整

    // 父节点指向删除节点的子节点
    if (t == p->left)
        p->left = s;
    else
        p->right = s;

    // 如果子节点不是叶节点，那么要设置其父节点为删除节点父节点
    if (s != leaf) s->parent = p;

    // 设置双黑节点的父节点为删除节点的父节点
    dBlackParent = p;

    // 如果删除节点与其子节点均为黑色
    // 删除后会破坏性质5，所以要进行“双黑修正”，此时双黑位于子节点上
    // 从情形1开始判断
    if (t->color == BLACK && s->color == BLACK) RemoveCase1(s);

    // 如果子节点不是叶节点，那么要设置其颜色为黑色
    if (s != leaf) s->color = BLACK;
    // 真正删除节点
    delete t;
    // 清除双黑节点父节点
    dBlackParent = nullptr;
    return 1;
}

void RedBlackTree::RemoveCase1(Node* root) {
    // 双黑节点为新的根节点，直接返回
    if (dBlackParent == leaf) return;
    // 否则进入情形2的判断
    RemoveCase2(root);
}

void RedBlackTree::RemoveCase2(Node* root) {
    // 兄弟节点
    Node* b =
        dBlackParent->left == root ? dBlackParent->right : dBlackParent->left;

    // 情形2处理的情况
    if (b->color == RED) {
        b->color = BLACK;
        // 将父节点重绘为红色
        dBlackParent->color = RED;
        // 以父节点为根旋转
        if (dBlackParent->left == root)
            RotateL(dBlackParent);
        else
            RotateR(dBlackParent);
        // 进入情形4的判断
        RemoveCase4(root);
    }
    // 不是情形2进入情形3的判断
    else
        RemoveCase3(root);
}

void RedBlackTree::RemoveCase3(Node* root) {
    // 兄弟节点
    Node* b =
        dBlackParent->left == root ? dBlackParent->right : dBlackParent->left;

    // 情形3处理的情况
    if (dBlackParent->color == BLACK && b->color == BLACK &&
        b->left->color == BLACK && b->right->color == BLACK) {
        // 重绘兄弟节点为红色
        b->color = RED;
        // 双黑向上传递
        root = dBlackParent;
        dBlackParent = dBlackParent->parent;
        // 从情形1开始判断父节点
        RemoveCase1(root);
    }
    // 不是情形3进入情形4的判断
    else
        RemoveCase4(root);
}

void RedBlackTree::RemoveCase4(Node* root) {
    // 兄弟节点
    Node* b =
        dBlackParent->left == root ? dBlackParent->right : dBlackParent->left;

    if (dBlackParent->color == RED && b->color == BLACK &&
        b->left->color == BLACK && b->right->color == BLACK) {
        // 交换兄弟节点和父节点的颜色
        b->color = RED;
        dBlackParent->color = BLACK;
    }
    // 不是情形4进入情形5的判断
    else
        RemoveCase5(root);
}

void RedBlackTree::RemoveCase5(Node* root) {
    // 兄弟节点
    Node* b =
        dBlackParent->left == root ? dBlackParent->right : dBlackParent->left;

    // 当前节点为父节点的左子节点、兄弟节点为黑色、兄弟节点的左子节点为红色、兄弟节点的右子节点为黑色
    if (dBlackParent->left == root && b->left->color == RED &&
        b->right->color == BLACK) {
        RotateR(b);
    }
    // 与上类似，只是左右对调
    else if (dBlackParent->right == root && b->right->color == RED &&
             b->left->color == BLACK) {
        RotateL(b);
    }

    // 进入情形6的处理
    RemoveCase6(root);
}

void RedBlackTree::RemoveCase6(Node* root) {
    // 兄弟节点
    Node* b =
        dBlackParent->left == root ? dBlackParent->right : dBlackParent->left;

    // 交换兄弟节点与父节点的颜色、
    // 因为兄弟节点为黑色，所以直接设置即可
    b->color = dBlackParent->color;
    dBlackParent->color = BLACK;

    // 当前节点为父节点的左子节点
    if (dBlackParent->left == root) {
        // 兄弟节点的右子节点设置为黑色
        b->right->color = BLACK;
        // 在父节点进行左旋
        RotateL(dBlackParent);
    }
    // 当前节点为父节点的右子节点
    else {
        // 兄弟节点的左子节点设置为黑色
        b->left->color = BLACK;
        // 在父节点进行右旋
        RotateR(dBlackParent);
    }
}

void RedBlackTree::Print(Node* root) {
    if (!root) return;
    if (root->left != leaf) Print(root->left);
    std::cout << root->val << ' ';
    if (root->right != leaf) Print(root->right);
}