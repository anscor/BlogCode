#include "AVLTree.h"
#include <iostream>

AVLTree::AVLTree() { root = nullptr; }

AVLTree::~AVLTree() { this->DeleteRoot(root); }

void AVLTree::DeleteRoot(AVLTreeNode* root) {
    // 递归释放树
    if (root) {
        if (root->left) DeleteRoot(root->left);
        if (root->right) DeleteRoot(root->right);
        delete root;
        root = nullptr;
    }
}

AVLTree::AVLTreeNode::AVLTreeNode(int val) {
    this->val = val;
    height = 0;
    left = right = nullptr;
}

AVLTree::AVLTreeNode::~AVLTreeNode() {}

int AVLTree::AVLTreeNode::Height(AVLTreeNode* root) {
    // 返回当前结点的高度，若为空则返回-1
    return root ? root->height : -1;
}

void AVLTree::CalcHeight(AVLTreeNode* root) {
    // 当前结点的高度为左、右子树最高者高度 + 1
    root->height = std::max(AVLTree::AVLTreeNode::Height(root->left),
                            AVLTree::AVLTreeNode::Height(root->right)) +
                   1;
}

// 左单旋转
AVLTree::AVLTreeNode* AVLTree::RotateL(AVLTreeNode* root) {
    AVLTree::AVLTreeNode* temp = root->left;
    root->left = temp->right;
    temp->right = root;

    // 旋转后root与temp结点高度发生了变化，需重新计算
    CalcHeight(temp);
    CalcHeight(root);
    return temp;
}

// 右单旋转
AVLTree::AVLTreeNode* AVLTree::RotateR(AVLTreeNode* root) {
    AVLTree::AVLTreeNode* temp = root->right;
    root->right = temp->left;
    temp->left = root;

    // 旋转后root与temp结点高度发生了变化，需重新计算
    CalcHeight(temp);
    CalcHeight(root);
    return temp;
}

AVLTree::AVLTreeNode* AVLTree::RotateLR(AVLTreeNode* root) {
    root->left = RotateR(root->left);
    return RotateL(root);
}

AVLTree::AVLTreeNode* AVLTree::RotateRL(AVLTreeNode* root) {
    root->right = RotateL(root->right);
    return RotateR(root);
}

AVLTree::AVLTreeNode* AVLTree::FindMax(AVLTreeNode* root) {
    if (!root) return nullptr;
    AVLTreeNode* temp = root;
    while (temp->right) temp = temp->right;
    return temp;
}

AVLTree::AVLTreeNode* AVLTree::FindMin(AVLTreeNode* root) {
    if (!root) return nullptr;
    AVLTreeNode* temp = root;
    while (temp->left) temp = temp->left;
    return temp;
}

AVLTree::AVLTreeNode* AVLTree::Insert(AVLTreeNode* root, int val, int& result) {
    result = 0;
    // 如果当前结点为空，则返回一个新建的结点
    if (!root) {
        root = new AVLTreeNode(val);
        result = 1;
        return root;
    }

    // 当前结点值比要插入的值大，则应向左子树进行插入
    if (root->val > val) {
        // 向左子树插入值为val的结点
        root->left = Insert(root->left, val, result);

        // 如果在向左子树插入结点后，引起了树的不平衡（即左子树比右子树高2个单位），则需进行旋转调整
        // 因为是向左子树插入，所以左子树的高度必定大于等于右子树的高度
        if (AVLTreeNode::Height(root->left) -
                AVLTreeNode::Height(root->right) ==
            2) {
            // 如果是插入的左子树的左子树，则对应LL情况，只需进行左单旋转即可
            if (val < root->left->val) root = RotateL(root);
            // 否则为LR情况，需进行两次旋转
            else
                root = RotateLR(root);
        }
    }
    // 当前结点值比要插入的值小，则应向右子树进行插入
    else if (val > root->val) {
        // 向左子树插入值为val的结点
        root->right = Insert(root->right, val, result);

        // 如果在向右子树插入结点后，引起了树的不平衡（即右子树比左子树高2个单位），则需进行旋转调整
        // 因为是向右子树插入，所以右子树的高度必定大于等于左子树的高度
        if (AVLTreeNode::Height(root->right) -
                AVLTreeNode::Height(root->left) ==
            2) {
            // 如果是插入的右子树的右子树，则对应RR情况，只需进行右单旋转即可
            if (val > root->right->val) root = RotateR(root);
            // 否则为RL情况，需进行两次旋转
            else
                root = RotateRL(root);
        }
    }

    // 回溯时计算出沿插入路径上所有结点的新高度
    CalcHeight(root);
    return root;
}

AVLTree::AVLTreeNode* AVLTree::Remove(AVLTreeNode* root, int val, int& result) {
    result = 0;
    if (!root) {
        return nullptr;
    }
    // 待删除结点位于右子树
    if (root->val < val) {
        // 在右子树中删除结点
        root->right = Remove(root->right, val, result);
        // 如果删除后引起了树的不平衡（即左子树的高度与右子树的高度差为2），则需要进行旋转调整
        if (AVLTreeNode::Height(root->left) -
                AVLTreeNode::Height(root->right) ==
            2) {
            // 如果右儿子的左子树的高度小于右儿子的右子树的高度，
            // 则删除的结点位于右儿子的左子树上，不平衡情况对应RR，
            // 进行右单旋转即可
            if (AVLTreeNode::Height(root->right->left) <
                AVLTreeNode::Height(root->right->right))
                root = RotateR(root);
            // 否则删除的结点位于右儿子的右子树上，不平衡情况对应RL，
            // 需进行两次旋转
            else
                root = RotateRL(root);
        }
    }
    // 待删除结点位于左子树
    else if (root->val > val) {
        // 在左子树中删除结点
        root->left = Remove(root->left, val, result);

        // 如果删除后引起了树的不平衡（即右子树的高度与左子树的高度差为2），则需要进行旋转调整
        if (AVLTreeNode::Height(root->right) -
                AVLTreeNode::Height(root->left) ==
            2) {
            // 如果左儿子的右子树的高度小于左儿子的左子树的高度，
            // 则删除的结点位于左儿子的右子树上，不平衡情况对应LL，
            // 进行左单旋转即可
            if (AVLTreeNode::Height(root->left->right) <
                AVLTreeNode::Height(root->left->left))
                root = RotateL(root);
            // 否则删除的结点位于左儿子的左子树上，不平衡情况对应LR，
            // 需进行两次旋转
            else
                root = RotateLR(root);
        }
    }
    // 否则应当删除当前结点
    else {
        result = 1;
        int t;
        // 当前结点有两个子结点，则从中选取高度大的一个子树进行替代，避免引起树的不平衡
        if (root->left && root->right) {
            // 左子树高度大于右子树时，选取左子树中最大值替代当前结点，并删除原最大值结点
            if (AVLTreeNode::Height(root->left) >
                AVLTreeNode::Height(root->right)) {
                AVLTreeNode* temp = FindMax(root->left);
                root->val = temp->val;
                root->left = Remove(root->left, temp->val, t);
            }
            // 否则，选取右子树中最小值替代当前结点，并删除原最小值结点
            else {
                AVLTreeNode* temp = FindMin(root->right);
                root->val = temp->val;
                root->right = Remove(root->right, temp->val, t);
            }
        }
        // 如果当前结点只有一个子结点或没有子结点，直接删除即可
        else {
            AVLTreeNode* temp = root;
            root = root->left ? root->left : root->right;
            delete temp;
        }
    }

    // 如果返回结点不为空时，回溯地计算出删除路径上所有结点的新高度
    if (root) CalcHeight(root);
    return root;
}

void AVLTree::Print(AVLTreeNode* root) {
    if (!root) return;
    if (root->left) Print(root->left);
    std::cout << root->val << ' ';
    if (root->right) Print(root->right);
}

int AVLTree::Insert(int val) {
    int result = 0;
    root = Insert(root, val, result);
    return result;
}

int AVLTree::Remove(int val) {
    int result = 0;
    root = Remove(root, val, result);
    return result;
}

int AVLTree::Find(int val) {
    AVLTreeNode* temp = root;
    while (temp) {
        // 如果当前结点为要查找的值，返回1表示该值存在，查找成功
        if (temp->val == val) return 1;
        // 如果当前结点值小于要查找的值，则表示要查找的值位于右子树上，查找右子树
        if (temp->val < val)
            temp = temp->right;
        // 如果当前结点值大于要查找的值，则表示要查找的值位于左子树上，查找左子树
        else
            temp = temp->left;
    }
    // 如果函数没有返回，则代表该值不存在，返回0表示查找失败
    return 0;
}

void AVLTree::Print() { Print(root); }
