//  mySet.h
//  Binary Tree Search

#ifndef mySet_h
#define mySet_h

// Множество на основе двоичного дерева поиска
template <typename T>
class mySet
{
    BTS<T>* tree;
public:
    mySet() = default;
    
    void insert(T data)
    {
        if (tree)
            tree = new BTS<T>(data);
        else
            tree->insert(data);
    }
    
    void erase(T data)
    {
        tree->remove(data);
    }
    
    bool find(T data)
    {
        return (tree->find(data) != tree->end());
    }
    
    void print()
    {
        tree->print();
    }
};

#endif /* mySet_h */
