#include <iostream>
#include <vector>
#include <memory>
#include <queue>
#include <functional>

// 트리 노드 정의
template <typename T>
struct TreeNode {
    T value;
    std::vector<std::shared_ptr<TreeNode<T>>> children;

    TreeNode(T val) : value(val) {}
};

// 트리 클래스 정의
template <typename T>
class Tree {
public:
    std::shared_ptr<TreeNode<T>> root;

    Tree(T rootValue) : root(std::make_shared<TreeNode<T>>(rootValue)) {}

    // 노드 추가
    void addChild(std::shared_ptr<TreeNode<T>> parent, T childValue) {
        parent->children.push_back(std::make_shared<TreeNode<T>>(childValue));
    }

    // 트리 순회 (BFS)
    void traverse(std::function<void(T)> visit) {
        if (!root) return;

        std::queue<std::shared_ptr<TreeNode<T>>> queue;
        queue.push(root);

        while (!queue.empty()) {
            auto node = queue.front();
            queue.pop();
            visit(node->value);

            for (auto& child : node->children) {
                queue.push(child);
            }
        }
    }
};

int main() {
    // 트리 생성
    Tree<int> tree(1);

    // 자식 노드 추가
    auto node1 = tree.root;
    tree.addChild(node1, 2);
    tree.addChild(node1, 3);
    auto node2 = node1->children[0];
    tree.addChild(node2, 4);
    tree.addChild(node2, 5);
    auto node3 = node1->children[1];
    tree.addChild(node3, 6);
    tree.addChild(node3, 7);

    // 트리 순회 및 출력
    tree.traverse([](int value) {
        std::cout << value << " ";
    });

    return 0;
}
