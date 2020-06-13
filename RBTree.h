//
// Created by krage56 on 13.06.2020.
//

#ifndef RED_BLACK_TREE_RBTREE_H
#define RED_BLACK_TREE_RBTREE_H

#include <cstddef>

template <typename ValueType, typename KeyType>
class RBTree {
    enum color{
        red,
        black
    };
    class Node{
        public:
            Node(const KeyType& key, const ValueType& value,
                    Node* parent = nullptr, Node* child_left = nullptr, Node* child_right = nullptr);
            ~Node();
            KeyType getKey();
            Node* getRightChild();
            Node* getLeftChild();
            Node* getParent();
            Node* getBrother();
            Node* getUncle();
            Node* getGrandPa();
            friend class RBTree;

        protected:
            void insert_next(const KeyType& key, const ValueType& value);
        private:
            KeyType key;
            ValueType value;
            Node* parent;
            Node* child_left;
            Node* child_right;
            RBTree::color nodeColor = RBTree::color::red;//по умолчанию изначально вставляется красный потомок
        };
public:
    void add(const KeyType& key, const ValueType& value);

protected:
    Node* BFS(Node* root);
private:
    Node* _root;
    size_t _cap;
    size_t _height;
};


#endif //RED_BLACK_TREE_RBTREE_H
