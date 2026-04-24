#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

struct Data {
    int y;
    int x;
    int index;
    
    Data(int a, int b, int c): y(b), x(a), index(c) {}
};

struct TreeNode {
    Data data;
    TreeNode *left;
    TreeNode *right;
    
    TreeNode(Data a): data(a), left(nullptr), right(nullptr) {}
};

vector<Data> getNodeDataStruct(vector<vector<int>> &nodeinfo){
    vector<Data> nodes;

    for (int i=0; i<nodeinfo.size(); ++i){
        nodes.push_back(Data{
            nodeinfo[i][0],
            nodeinfo[i][1],
            i+1
        });
    }
    
    sort(nodes.begin(), nodes.end(), [](const auto &a, const auto &b){
        if (a.y == b.y){
            return a.x < b.x;
        }
        
        return a.y > b.y;
    });
    
    return nodes;
}

vector<TreeNode> getTree(vector<Data> &node){
    vector<TreeNode> tree;
    tree.reserve(node.size());

    for (auto &n: node){
        if (!tree.size()){
            tree.push_back(TreeNode{ n });
            continue;
        }

        TreeNode *p = &tree[0];

        int i=tree.size();
        do {
            if (p->data.x > n.x){
                if (p->left != nullptr){
                    p = p->left;
                    continue;
                }

                tree.push_back(TreeNode{ n });
                p->left = &tree[tree.size()-1];
                break;
            }else {
                if (p->right != nullptr){
                    p = p->right;
                    continue;
                }

                tree.push_back(TreeNode{ n });
                p->right = &tree[tree.size()-1];
                break;
            }
        }while (--i > 0);
    }
    
    return tree;
}

void preorder(TreeNode *tree, vector<int> &answer){
    if (tree == nullptr) return;
    
    answer.push_back(tree->data.index);
    
    if (tree->left != nullptr) preorder(tree->left, answer);
    if (tree->right != nullptr) preorder(tree->right, answer);
}

void postorder(TreeNode *tree, vector<int> &answer){
    if (tree == nullptr) return;
    
    if (tree->left != nullptr) postorder(tree->left, answer);
    if (tree->right != nullptr) postorder(tree->right, answer);
    
    answer.push_back(tree->data.index);
}

vector<vector<int>> solution(vector<vector<int>> nodeinfo) {
    vector<vector<int>> answer(2, vector<int>());
    vector<Data> nodes = getNodeDataStruct(nodeinfo);
    vector<TreeNode> tree = getTree(nodes);
    
    preorder(&tree[0], answer[0]);
    postorder(&tree[0], answer[1]);
    
    return answer;
}