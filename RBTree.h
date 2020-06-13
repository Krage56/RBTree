//
// Created by krage56 on 13.06.2020.
//

#ifndef RED_BLACK_TREE_RBTREE_H
#define RED_BLACK_TREE_RBTREE_H

template <typename ValueType, typename KeyType>
class RBTree {
    enum color{
        red,
        black
    };
    class Node{
    public:
        Node(const KeyType& key, const ValueType& value, Node* child_left = nullptr, Node* child_right = nullptr);
        ~Node();
        friend class RBTree;
    private:
        KeyType key;
        ValueType value;
        RBTree::color nodeColor = RBTree::color::red;//по умолчанию изначально вставляется красный потомок
    };
};


#endif //RED_BLACK_TREE_RBTREE_H
