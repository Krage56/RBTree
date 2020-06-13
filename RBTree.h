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
                    Node* parent = nullptr, Node* child_left = nullptr,
                    Node* child_right = nullptr);
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
            Node* insert(const KeyType& key, const ValueType& value);
            void setColor(RBTree::color new_color);
            void setParent(Node* new_parent);
            void setLeftChild(Node* new_child);
            void setRightChild(Node* new_child);
        private:
            KeyType key;
            ValueType value;
            Node* parent;
            Node* child_left;
            Node* child_right;
            RBTree::color nodeColor = RBTree::color::red;//по умолчанию изначально вставляется красный потомок
        };
public:
    RBTree();
    ~RBTree()= default;//потом заменить на последовательное удаление узлов
    void add(const KeyType& key, const ValueType& value);

protected:
    void left_rotate(Node* node);
    void right_rotate(Node* node);
    void first_add_case(Node* node);
    void second_add_case(Node* node);
    void third_add_case(Node* node);
    void fourth_add_case(Node* node);
    void fifth_add_case(Node* node);
private:
    Node* _root;
    size_t _cap;
    size_t _height;
};

template<typename ValueType, typename KeyType>
RBTree<ValueType, KeyType>::RBTree() {
    _root = nullptr;
    _cap = 0;
    _height = 0;
}

template<typename ValueType, typename KeyType>
void RBTree<ValueType, KeyType>::add(const KeyType &key, const ValueType &value) {
    Node* new_node = nullptr;//указатель на новый объект
    if(_cap == 0){
        _root = new Node(key, value);
        new_node = _root;
    }
    else{
        new_node = _root->insert(key, value);
    }
    first_add_case(new_node);
    _cap += 1;
}

template<typename ValueType, typename KeyType>
void RBTree<ValueType, KeyType>::first_add_case(RBTree::Node *node) {
    if(node == _root){
        node->nodeColor = RBTree<ValueType, KeyType>::color::black;
    }
    else{
        second_add_case(node);
    }
}

template<typename ValueType, typename KeyType>
void RBTree<ValueType, KeyType>::second_add_case(RBTree::Node *node) {
    if(node->getParent()->getColor() == color::black){
        return;
    }
    else {
        third_add_case(node);
    }
}

template<typename ValueType, typename KeyType>
void RBTree<ValueType, KeyType>::third_add_case(RBTree::Node *node) {
    Node* uncle = node->getUncle();
    if(uncle && uncle->getColor() == color::red){
        node->getParent()->setColor(color::black);
        uncle->setColor(color::black);
        Node* g = node->getGrandPa();
        g->setColor(color::red);
        first_add_case(g);
    }
    else{
        fourth_add_case(node);
    }
}

template<typename ValueType, typename KeyType>
void RBTree<ValueType, KeyType>::fourth_add_case(RBTree::Node *node) {
    Node* g = node->getGrandPa();
    Node* p = node->getParent();
    if(node == p->getRightChild() && p == g->getLeftChild()){
        left_rotate(p);
        node = node->getLeftChild();
    }
    else if(node == p->getLeftChild() && p == g->getRightChild()){
        right_rotate(p);
        node = node->getRightChild();
    }
    fifth_add_case(node);
}

template<typename ValueType, typename KeyType>
void RBTree<ValueType, KeyType>::left_rotate(RBTree::Node *node) {
    Node* new_parent = node->getRightChild();
    new_parent->setParent(node->getParent());
    if(node->getParent() && node == node->getParent()->getRightChild()){
        node->getParent()->setRightChild(new_parent);
    }
    else if (node->getParent()){
        node->getParent()->setLeftChild(new_parent);
    }
    node->setRightChild(new_parent->getLeftChild());
    new_parent->setLeftChild(node);
    node->setParent(new_parent);
    if(node->getRightChild())
        node->getRightChild()->setParent(node);

    if(node == _root){
        _root = new_parent;
    }
}

template<typename ValueType, typename KeyType>
void RBTree<ValueType, KeyType>::fifth_add_case(RBTree::Node *node) {
    Node* g = node->getGrandPa();
    node->getParent()->setColor(color::black);
    g->setColor(color::red);
    if(node == node->getParent()->getLeftChild()
    && node->getParent() == g->getLeftChild()){
        right_rotate(g);
    }
    else{
        left_rotate(g);
    }
}

template<typename ValueType, typename KeyType>
void RBTree<ValueType, KeyType>::right_rotate(RBTree::Node *node) {
    Node* new_parent = node->getLeftChild();
    new_parent->setParent(node->getParent());
    if(node->getParent() && node == node->getParent()->getRightChild()){
        node->getParent()->setRightChild(new_parent);
    }
    else if (node->getParent()){
        node->getParent()->setLeftChild(new_parent);
    }
    node->setLeftChild(new_parent->getRightChild());
    if(new_parent->getRightChild())
        new_parent->getRightChild()->setParent(node);
    new_parent->setRightChild(node);
    node->setParent(new_parent);
    if(node == _root){
        _root = new_parent;
    }
}

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

template<typename ValueType, typename KeyType>
typename RBTree<ValueType, KeyType>::Node *RBTree<ValueType, KeyType>::Node::insert(const KeyType &key, const ValueType &value) {
    Node* current_node = this;
    if(current_node->key > key){
        if(!current_node->child_left){
            current_node->child_left =
                    new Node(key, value, current_node);
            return current_node->child_left;
        }
        else{
            return current_node->child_left->insert(key, value);
        }
    }
    else{
        if(!current_node->child_right){
            current_node->child_right =
                    new Node(key, value, current_node);
            return current_node->child_right;
        }
        else{
            return current_node->child_right->insert(key, value);
        }
    }
}

template<typename ValueType, typename KeyType>
void RBTree<ValueType, KeyType>::Node::setColor(RBTree::color new_color) {
    this->nodeColor = new_color;
}

template<typename ValueType, typename KeyType>
void RBTree<ValueType, KeyType>::Node::setParent(RBTree::Node *new_parent) {
    parent = new_parent;
}

template<typename ValueType, typename KeyType>
void RBTree<ValueType, KeyType>::Node::setLeftChild(RBTree::Node *new_child) {
    child_left = new_child;
}

template<typename ValueType, typename KeyType>
void RBTree<ValueType, KeyType>::Node::setRightChild(RBTree::Node *new_child) {
    child_right = new_child;
}

#endif //RED_BLACK_TREE_RBTREE_H
