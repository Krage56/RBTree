//
// Created by krage56 on 13.06.2020.
//

#ifndef RED_BLACK_TREE_RBTREE_H
#define RED_BLACK_TREE_RBTREE_H

#include <cstddef>
#include <list>

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
            ValueType& getValue();
            friend class RBTree;

        protected:
            Node* insert(const KeyType& key, const ValueType& value);
            void setColor(RBTree::color new_color);
            void setKey(const KeyType& new_key);
            void setParent(Node* new_parent);
            void setLeftChild(Node* new_child);
            void setRightChild(Node* new_child);
            void setValue(ValueType& val);
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
    ~RBTree();
    void add(const KeyType& key, const ValueType& value);
    void remove(const KeyType& key);
    void remove_all(const KeyType& key);
    ValueType find(const KeyType& key)const;
    [[nodiscard]] size_t getCapacity()const;
    [[nodiscard]] bool isEmpty()const;
protected:
    Node* deleteNode(Node* node);
    void firstDelCase(Node* node);
    void secondDelCase(Node* node);
    void thirdDelCase(Node* node);
    void fourthDelCase(Node* node);
    void fifthDelCase(Node* node);
    void sixthDelCase(Node* node);
    void afterDelFix(Node* node);

    void leftRotate(Node* node);
    void rightRotate(Node* node);

    void firstAddCase(Node* node);
    void secondAddCase(Node* node);
    void thirdAddCase(Node* node);
    void fourthAddCase(Node* node);
    void fifthAddCase(Node* node);

    Node* find(const KeyType& key, Node* root);
    Node* getLastRight(Node* root);//Получить узел с наибольшим ключом
    Node* getLastLeft(Node* root);//Получить узел с наименьшим узлом
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
    firstAddCase(new_node);
    _cap += 1;
}

template<typename ValueType, typename KeyType>
void RBTree<ValueType, KeyType>::firstAddCase(RBTree::Node *node) {
    if(node == _root){
        node->nodeColor = RBTree<ValueType, KeyType>::color::black;
    }
    else{
        secondAddCase(node);
    }
}

template<typename ValueType, typename KeyType>
void RBTree<ValueType, KeyType>::secondAddCase(RBTree::Node *node) {
    if(node->getParent()->getColor() == color::black){
        return;
    }
    else {
        thirdAddCase(node);
    }
}

template<typename ValueType, typename KeyType>
void RBTree<ValueType, KeyType>::thirdAddCase(RBTree::Node *node) {
    Node* uncle = node->getUncle();
    if(uncle && uncle->getColor() == color::red){
        node->getParent()->setColor(color::black);
        uncle->setColor(color::black);
        Node* g = node->getGrandPa();
        g->setColor(color::red);
        firstAddCase(g);
    }
    else{
        fourthAddCase(node);
    }
}

template<typename ValueType, typename KeyType>
void RBTree<ValueType, KeyType>::fourthAddCase(RBTree::Node *node) {
    Node* g = node->getGrandPa();
    Node* p = node->getParent();
    if(node == p->getRightChild() && p == g->getLeftChild()){
        leftRotate(p);
        node = node->getLeftChild();
    }
    else if(node == p->getLeftChild() && p == g->getRightChild()){
        rightRotate(p);
        node = node->getRightChild();
    }
    fifthAddCase(node);
}

template<typename ValueType, typename KeyType>
void RBTree<ValueType, KeyType>::leftRotate(RBTree::Node *node) {
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
void RBTree<ValueType, KeyType>::fifthAddCase(RBTree::Node *node) {
    Node* g = node->getGrandPa();
    node->getParent()->setColor(color::black);
    g->setColor(color::red);
    if(node == node->getParent()->getLeftChild()
    && node->getParent() == g->getLeftChild()){
        rightRotate(g);
    }
    else{
        leftRotate(g);
    }
}

template<typename ValueType, typename KeyType>
void RBTree<ValueType, KeyType>::rightRotate(RBTree::Node *node) {
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
ValueType RBTree<ValueType, KeyType>::find(const KeyType &key) const{
    Node* result_node = find(key, _root);
    return result_node? result_node->getValue(): NULL;
}

template<typename ValueType, typename KeyType>
typename RBTree<ValueType, KeyType>::Node *RBTree<ValueType, KeyType>::find(const KeyType &key, RBTree::Node *root) {
    Node* node = root;
    while(node){
        if(key < node->getKey()){
            node = node->getLeftChild();
        }
        else if(key > node->getKey()){
            node = node->getRightChild();
        }
        else{
            return node;
        }
    }
    return nullptr;
}

template<typename ValueType, typename KeyType>
size_t RBTree<ValueType, KeyType>::getCapacity() const {
    return _cap;
}

template<typename ValueType, typename KeyType>
bool RBTree<ValueType, KeyType>::isEmpty() const {
    return _cap == 0;
}

template<typename ValueType, typename KeyType>
typename RBTree<ValueType, KeyType>::Node *RBTree<ValueType, KeyType>::getLastRight(Node* root) {
    Node* node = root;
    if(!node)
        return nullptr;
    while(node->getRightChild()){
        node = node->getRightChild();
    }
    return node;
}

template<typename ValueType, typename KeyType>
typename RBTree<ValueType, KeyType>::Node *RBTree<ValueType, KeyType>::getLastLeft(Node* root) {
    Node* node = root;
    if(!node)
        return nullptr;
    while(node->getLeftChild()){
        node = node->getLeftChild();
    }
    return node;
}

template<typename ValueType, typename KeyType>
RBTree<ValueType, KeyType>::~RBTree() {
    if(!_cap){
        return;
    }
    Node* node = _root;
    Node* leaf = nullptr;
    while(node){
        if(node->getLeftChild()){
            node = node->getLeftChild();
        }
        else if(node->getRightChild()){
            node = node->getRightChild();
        }
        else{
            leaf = node;
            node = node->getParent()? node->getParent(): nullptr;
            if(node && node->getRightChild() && node->getRightChild() == leaf){
                node->setRightChild(nullptr);
            }
            if(node && node->getLeftChild() && node->getLeftChild() == leaf){
                node->setLeftChild(nullptr);
            }
            delete leaf;
        }
    }
}

template<typename ValueType, typename KeyType>
void RBTree<ValueType, KeyType>::remove(const KeyType& key) {
    Node* node = find(key, _root);
    if(node){
        Node* free = deleteNode(node);
        delete(free);
        _cap -= 1;
    }
}

template<typename ValueType, typename KeyType>
void RBTree<ValueType, KeyType>::afterDelFix(RBTree::Node *node) {
    if(!node || node->getColor() == color::red){
        return;
    }
    firstDelCase(node);
}

template<typename ValueType, typename KeyType>
void RBTree<ValueType, KeyType>::firstDelCase(RBTree::Node *node) {
    if(node->getParent()){
        secondDelCase(node);
    }
}

template<typename ValueType, typename KeyType>
void RBTree<ValueType, KeyType>::remove_all(const KeyType &key) {
    Node* remove = find(key, _root);
    while(remove){
        //фактически удаляемый узел может быть другим
        Node* free = deleteNode(remove);
        delete(free);
        _cap -= 1;
        remove = find(key, _root);
    }
}

template<typename ValueType, typename KeyType>
typename RBTree<ValueType, KeyType>::Node * RBTree<ValueType, KeyType>::deleteNode(Node* node) {
    if(!node)
        return nullptr;
    if(node->getLeftChild() == nullptr &&
       node->getRightChild() == nullptr){
        Node* p = node->getParent();
        afterDelFix(node);
        if(p && node == p->getRightChild()){
            p->setRightChild(nullptr);
        }
        else if(p){
            p->setLeftChild(nullptr);
        }
    }
    else if(!node->getLeftChild()){
        Node* p = node->getParent();
        if(p){
            afterDelFix(node);
            if(p->getRightChild() == node){
                p->setRightChild(node->getRightChild());
            }
            if(p->getLeftChild() == node){
                p->setLeftChild(node->getRightChild());
            }
            node->getRightChild()->setParent(p);
        }
        else{
            node->setValue(node->getRightChild()->getValue());
            node->setKey(node->getRightChild()->getKey());
            node = deleteNode(node->getRightChild());
        }
    }
    else if(!node->getRightChild()){
        Node* p = node->getParent();
        if(p) {
            afterDelFix(node);
            if (p->getRightChild() == node) {
                p->setRightChild(node->getLeftChild());
            }
            if (p->getLeftChild() == node) {
                p->setLeftChild(node->getLeftChild());
            }
            node->getLeftChild()->setParent(p);
        }
        else{
            node->setValue(node->getLeftChild()->getValue());
            node->setKey(node->getLeftChild()->getKey());
            node = deleteNode(node->getLeftChild());
        }
    }
    else{
        if(!node->getRightChild()->getLeftChild()){
            Node* p = node->getParent();
            if(p){
                afterDelFix(node);
                if(p->getRightChild() == node){
                    p->setRightChild(node->getRightChild());
                    node->getRightChild()->setParent(p);
                }
                if(p->getLeftChild() == node){
                    p->setLeftChild(node->getRightChild());
                    node->getRightChild()->setParent(p);
                }
                node->getRightChild()->setLeftChild(node->getLeftChild());
                if(node->getLeftChild()){
                    node->getLeftChild()->setParent(node->getRightChild());
                }
            }
            else{
                node->setValue(node->getRightChild()->getValue());
                node->setKey(node->getRightChild()->getKey());
                node = deleteNode(node->getRightChild());
            }

        }//?
        else{
            Node* l = getLastLeft(node->getRightChild());
            node->setKey(l->getKey());
            node->setValue(l->getValue());
            l = deleteNode(l);//вызываем операцию удаления для самой левой ноды
            node = l;
        }
    }
    return node;
}

template<typename ValueType, typename KeyType>
void RBTree<ValueType, KeyType>::secondDelCase(RBTree::Node *node) {
    Node* s = node->getBrother();
    Node* p = node->getParent();
    if(s->getColor() == color::red){
        p->setColor(color::red);
        s->setColor(color::black);
    }
    if(p->getLeftChild() == node){
        leftRotate(p);
    }
    else{
        rightRotate(p);
    }
    thirdDelCase(node);
}

template<typename ValueType, typename KeyType>
void RBTree<ValueType, KeyType>::thirdDelCase(RBTree::Node *node) {
    Node* s = node->getBrother();
    if(node->getParent()->getColor() == color::black &&
    (!s->getLeftChild() || s->getLeftChild()->getColor() == color::black)
     && (!s->getRightChild() || s->getRightChild()->getColor() == color::black)){
        s->setColor(color::red);
        firstDelCase(node->getParent());
    }
    else{
        fourthDelCase(node);
    }
}

template<typename ValueType, typename KeyType>
void RBTree<ValueType, KeyType>::fourthDelCase(RBTree::Node *node) {
    Node* s = node->getBrother();
    if(s->getParent()->getColor() == color::red &&
            (!s->getLeftChild() || s->getLeftChild()->getColor() == color::black)
            && (!s->getRightChild() || s->getRightChild()->getColor() == color::black)){
        s->setColor(color::red);
        s->getParent()->setColor(color::black);
    }
    fifthDelCase(node);
}

template<typename ValueType, typename KeyType>
void RBTree<ValueType, KeyType>::fifthDelCase(RBTree::Node *node) {
    Node* s = node->getBrother();
    if(s->getColor() == color::black){
        if(node->getParent()->getLeftChild() == node){
            if((!s->getLeftChild() || s->getLeftChild()->getColor() == color::red)
               && (!s->getRightChild() || s->getRightChild()->getColor() == color::black)){
                s->setColor(color::red);
                s->getLeftChild()->setColor(color::black);
                rightRotate(s);
            }
        }
        //нужна ли эта коррекция?
//        else if(node->getParent()->getRightChild() == node){
//            if((!s->getLeftChild() || s->getLeftChild()->getColor() == color::black)
//               && (!s->getRightChild() || s->getRightChild()->getColor() == color::red)){
//                s->setColor(color::red);
//                s->getRightChild()->setColor(color::black);
//                leftRotate(s);
//            }
//        }
    }
    sixthDelCase(node);
}

template<typename ValueType, typename KeyType>
void RBTree<ValueType, KeyType>::sixthDelCase(RBTree::Node *node) {
    Node* s = node->getBrother();
    s->setColor(node->getParent()->getColor());
    node->getParent()->setColor(color::black);
    if(node->getParent()->getLeftChild() == node){
        s->getRightChild()->setColor(color::black);
        leftRotate(node->getParent());
    }
    else{
        s->getLeftChild()->setColor(color::black);
        rightRotate(node->getParent());
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

template<typename ValueType, typename KeyType>
ValueType &RBTree<ValueType, KeyType>::Node::getValue() {
    return value;
}

template<typename ValueType, typename KeyType>
void RBTree<ValueType, KeyType>::Node::setValue(ValueType& val) {
    value = val;
}

template<typename ValueType, typename KeyType>
void RBTree<ValueType, KeyType>::Node::setKey(const KeyType &new_key) {
    key = new_key;
}

#endif //RED_BLACK_TREE_RBTREE_H
