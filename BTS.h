//  BTS.h
//  Binary Tree Search

#ifndef BTS_h
#define BTS_h

#include <iostream>
#include <iterator>
#include <queue>

template <typename T>
class BTS
{
private:
    struct node
    {
        T data;
        node* parent;
        node* left;
        node* right;
        
        node(T d) : data(d), left(nullptr), right(nullptr), parent(nullptr) {};
        node(T d, node* p, node* l, node* r) : data(d), left(l), right(r), parent(p) {};
        
        node * next()
        {
            node* x = this;
            if (x->right)
                return minnode(x->right);
            node* y = x->parent;
            while (y && x == y->right)
            {
                x = y;
                y = y->parent;
            }
            return y;
        }
    };
    
    node* root;
    
public:
    BTS(node * n) { root = new node(n->data, n->parent, n->left, n->right); }
    
    // Вставка
    void insert(T data)
    {
        node* parent = nullptr;
        node* cur = new node(data, nullptr, nullptr, nullptr);
        
        if (!root)
          root = cur;
        else
        {
            node* help = root;
            while (help != nullptr)
            {
                parent = help;
                if (cur->data > help->data)
                    help = help->right;
                else help = help->left;
            }
            
            if (cur->data < parent->data)
                parent->left = cur;
            else
                parent->right = cur;
        }
        cur->parent = parent;
    }
    
    
    // Удаление
    bool remove(T data)
    {
        node* parent = nullptr;
        node* cur = root;
        while (cur != nullptr)
        {
            if (data < cur->data)
            {
                parent = cur;
                cur = cur->left;
            }
            else if (data > cur->data)
            {
                parent = cur;
                cur = cur->right;
            }
            else
                break;
        }
        
        if (cur == nullptr)
            return false;
        
        if (cur->left == nullptr)
        {
            if (parent == nullptr)
            {
                root = cur->right;
            }
            else
            {
                if (data < parent->data)
                    parent->left = cur->right;
                else
                    parent->right = cur->right;
            }
            
            delete cur;
        }
        else
        {
            node* parentOfRightMost = cur;
            node* rightMost = cur->left;
            
            while (rightMost->right != nullptr)
            {
                parentOfRightMost = rightMost;
                rightMost = rightMost->right;
            }
            
            cur->data = rightMost->data;
            
            if (parentOfRightMost->right == rightMost)
                parentOfRightMost->right = rightMost->left;
            else
                parentOfRightMost->left = rightMost->left;
            
            delete rightMost;
        }
        return true;
    }
    
    // Поиск элемента и возврат указателя на него
    node* find(T data)
    {
        node* cur = root;
        while ((cur != nullptr) && (cur->data != data))
        {
            if (data < (cur->data))
                cur = cur->left;
            else
                cur = cur->right;
        }
        return cur;
    }
    
    // Поиск первого элемента большего или равного заданному числу
    node* find_bigger(T data)
    {
        if (root != nullptr)
        {
            if (root->data >= data)
                return new node(root);
            else if (root->right != nullptr)
                return new node(root->right);
            else if (root->parent->left == root)
                return new node(root->parent);
            else
                return nullptr;
        }
        else
            return nullptr;
    }
    
    // Поиск первого элемента меньшего или равного заданному числу
    node* find_smaller(T data)
    {
        if (root != nullptr)
        {
            if (root->data <= data)
                return new node(root);
            else if (root->left != nullptr)
                return new node(root->left);
            else if (root->parent->right == root)
                return new node(root->parent);
            else
                return nullptr;
        }
        else
            return nullptr;
    }
    
    // Вывод на экран по слоям с использованием очереди
    void print_layer()
    {
        std::queue<node*> q;
        node* r;
        q.push(root);
        while (!q.empty())
        {
            r = q.front(); q.pop();
            if (!((r->data == root->data) && (r != root)))
                std::cout << r->data << ' ';
            if (r->left)
                q.push(r->left);
            if (r->right)
                q.push(r->right);
        }
    }
    
    void printHELP(node* cur)
    {
        if (cur->left != nullptr)
            printHELP(cur->left);
        std::cout << cur->data << " ";
        if ((cur->right != nullptr))
            printHELP(cur->right);
    }
    
    // Рекурсивная печать
    void print()
    {
        auto cur = root;
        printHELP(cur);
    }
    
    // Сравниение двух деревьев
    bool operator==(node & other)
    {
        auto it1 = begin();
        auto it2 = other.begin();
        for (; it1 != end(); )
        {
            if (it2 == other.end())
                return false;
            ++it1;
            ++it2;
            if (*it1 != *it2)
                return false;
        }
        return true;
    }
    
    static node* minnode(node* p)
    {
        if (!p)
            return p;
        while (p->left)
            p = p->left;
        return p;
    }
    
    static node* maxnode(node* p)
    {
        if (!p)
            return p;
        while (p->right)
            p = p->right;
        return p;
    }
    
    // Класс итератора
    class TreeIterator : public std::iterator<std::bidirectional_iterator_tag, T>
    {
    private:
        node* rootIter;
        
    public:
        TreeIterator() : rootIter(nullptr) {}
        
        TreeIterator(node* tree) : rootIter(tree) {}
        
        TreeIterator(const TreeIterator* tree)
        {
            rootIter = tree->root;
        }
        
        T operator *()
        {
            return rootIter->data;
        }
        
        TreeIterator(T data)
        {
            rootIter = new node(data);
        }
        
        TreeIterator(const TreeIterator& other) : rootIter(other.rootIter) {}
        
        friend bool operator==(const TreeIterator& other1, const TreeIterator& other2)
        {
            return (other1.rootIter == other2.rootIter);
            
        }
        
        friend bool operator!=(const TreeIterator& other1, const TreeIterator& other2)
        {
            return !(other1 == other2);
        }
        
        TreeIterator& operator=(const TreeIterator& other)
        {
            this->rootIter = other.rootIter;
            return *this;
        }
        
        TreeIterator& operator=(TreeIterator&& other)
        {
            this->rootIter = other.rootIter;
            other.rootIter = nullptr;
            return *this;
        }
        
        TreeIterator & operator++()
        {
            rootIter = rootIter->next();
            return *this;
        }
        
        TreeIterator operator++(T)
        {
            TreeIterator cur(*this);
            operator++(); //++(*this);
            return cur;
        }
        
        ~TreeIterator() = default;
    };
    
    using iterator = TreeIterator;
    
    BTS() : root(nullptr) {}
    BTS(T data = 0) { root = new node(data); }
    
    iterator end()
    {
        node* tmp = root;
        
        if (tmp == nullptr)
            return iterator(new node(0));
        
        while (tmp->right != nullptr)
            tmp = tmp->right;
        return iterator(tmp);
    }
    
    iterator begin()
    {
        node * tmp = root;
        while (tmp->left != nullptr)
            tmp = tmp->left;
        return iterator(tmp);
    }
    
    iterator min()
    {
        return iterator(minnode(root));
    }
    
    iterator max()
    {
        return iterator(maxnode(root));
    }
};

#endif /* BTS_h */
