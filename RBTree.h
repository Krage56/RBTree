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
            ~Node() = default;
            KeyType getKey();
            RBTree::color getColor();
            Node* getRightChild();
            Node* getLeftChild();
            Node* getParent();
            Node* getBrother();
            Node* getUncle();
            Node* getGrandPa();
            friend class RBTree;

        protected:
            void insert_left(const KeyType& key, const ValueType& value);
            void insert_right(const KeyType& key, const ValueType& value);
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

private:
    Node* _root;
    size_t _cap;
    size_t _height;
};

template<typename ValueType, typename KeyType>
RBTree<ValueType, KeyType>::Node::Node(const KeyType &key,
        const ValueType &value, RBTree::Node *parent,
                                       RBTree::Node *child_left, RBTree::Node *child_right){
    this->key = key;
    this->value = value;
    this->child_left = child_left;
    this->child_right = child_right;
    this->parent = parent;
}

template<typename ValueType, typename KeyType>
KeyType RBTree<ValueType, KeyType>::Node::getKey() {
    return this->key;
}

template<typename ValueType, typename KeyType>
typename RBTree<ValueType, KeyType>::color RBTree<ValueType, KeyType>::Node::getColor() {
    return this->nodeColor;
}

template<typename ValueType, typename KeyType>
typename RBTree<ValueType, KeyType>::Node *RBTree<ValueType, KeyType>::Node::getRightChild() {
    return this->child_right;
}
template<typename ValueType, typename KeyType>
typename RBTree<ValueType, KeyType>::Node *RBTree<ValueType, KeyType>::Node::getLeftChild() {
    return this->child_left;
}
template<typename ValueType, typename KeyType>
typename RBTree<ValueType, KeyType>::Node *RBTree<ValueType, KeyType>::Node::getParent(){
    return this->parent;
}
template<typename ValueType, typename KeyType>
typename RBTree<ValueType, KeyType>::Node *RBTree<ValueType, KeyType>::Node::getBrother() {
    if(parent->child_right == this){
        return parent->child_left;
    }
    else{
        return parent->child_right;
    }
}

template<typename ValueType, typename KeyType>
typename RBTree<ValueType, KeyType>::Node *RBTree<ValueType, KeyType>::Node::getUncle() {
    return parent->getBrother();
}

template<typename ValueType, typename KeyType>
typename RBTree<ValueType, KeyType>::Node *RBTree<ValueType, KeyType>::Node::getGrandPa() {
    const short steps = 2; // высота подъёма вверх
    Node* current_node = this;
    short i = 0;
    while(current_node && i < steps){
        ++i;
        current_node = current_node->parent;
    }
    return current_node;
}

#endif //RED_BLACK_TREE_RBTREE_H
