#ifndef RB_TREE_HPP
#define RB_TREE_HPP

#include <algorithm> // max, min
#include <memory>


#define MAYTHROW noexcept(false)



enum class Color : bool
{
    Black = true,
    Red = false
};



template<class Key, class Value, class Comparator=std::less<Key>>
class RedBlackTree
{
public:

    class Node
    {
        friend class RedBlackTree;

    public:
        Node(const Node &) = delete;
        Node(Node &&) = delete;
        Node &operator = (const Node &) = delete;
        Node &operator = (Node &&) = delete;

        inline ~Node()
        {
            delete left;
            delete right;
        }

        inline const Value &get_value() const noexcept
        {
            return value;
        }

        inline const Key &get_key() const noexcept
        {
            return key;
        }

    private:
        inline Node(const Key &key, Node *parent) :
            key(key), parent(parent) { }

        inline Node *minimum() noexcept
        {
            auto node = this;
            while (node->left != nullptr) {
                node = node->left;
            }
            return node;
        }

        inline Node *maximun() noexcept
        {
            auto node = this;
            while (node->right != nullptr) {
                node = node->right;
            }
            return node;
        }

        inline Node *sibling() noexcept
        {
            if (parent == nullptr) {
                return nullptr;
            }
            return is_right_child() ? parent->left : parent->right;
        }

        inline bool is_right_child() const noexcept
        {
            assert(parent != nullptr);
            return parent->right == this;
        }

        void check(int &maxh, int &minh) const noexcept
        {
            int l_maxh = 0;
            int l_minh = 0;
            if (left != nullptr) {
                assert(color == Color::Black or left->color == Color::Black);
                assert(left->parent == this);
                left->check(l_maxh, l_minh);
            }
            int r_maxh = 0;
            int r_minh = 0;
            if (right != nullptr) {
                assert(color == Color::Black or right->color == Color::Black);
                assert(right->parent == this);
                right->check(r_maxh, r_minh);
            }
            maxh = std::max(l_maxh, r_maxh) + 1;
            minh = std::min(l_minh, r_minh) + 1;
            assert(maxh <= minh * 2);
        }

        Key key;
        Value value;
        Node *parent;
        Color color = Color::Red;
        Node *left = nullptr;
        Node *right = nullptr;
    };

    RedBlackTree() = default;
    RedBlackTree(const RedBlackTree &) = delete;
    RedBlackTree(RedBlackTree &&) = delete;
    RedBlackTree &operator = (const RedBlackTree &) = delete;
    RedBlackTree &operator = (RedBlackTree &&) = delete;

    inline ~RedBlackTree()
    {
        delete root;
    }


    // element access
    inline Value &at(const Key &key) const MAYTHROW
    {
        auto node = find(key);
        if (node == nullptr) {
            throw std::out_of_range("key not found");
        }
        return node->value;
    }

    inline Value &operator[](const Key &key) MAYTHROW
    {
        return find_or_insert(key).first->value;
    }


    // capacity
    inline bool empty() const noexcept
    {
        assert(root == nullptr or tree_size > 0);
        return root == nullptr;
    }

    inline size_t size() const noexcept
    {
        return tree_size;
    }


    // modifiers
    inline void clear() MAYTHROW
    {
        delete root;
    }

    inline std::pair<Node *, bool> insert(const Key &key, const Value &value) MAYTHROW // TODO: iterators
    {
        auto result = find_or_insert(key);
        if (result.second) {
            result.first->value = value;
        }
        return result;
    }

    inline std::pair<Node *, bool> insert_or_assign(const Key &key, const Value &value) MAYTHROW // TODO: iterators
    {
        auto result = find_or_insert(key);
        result.first->value = value;
        return result;
    }

    void erase(Node *node) MAYTHROW // TODO: iterators
    {
        assert(node != nullptr);
        Node *successor;
        if (node->left == nullptr or node->right == nullptr) {
            successor = node;
        }
        else if (node->right != nullptr) {
            successor = node->right->minimum();
        }
        else {
            successor = node;
            while (successor->is_right_child()) {
                successor = successor->parent;
            }
            successor = successor->parent;
        }
        auto balancing = successor->left != nullptr ? successor->left : successor->right;
        auto sibling = successor->sibling();
        transplant(successor, balancing);
        bool removed_black = successor->color == Color::Black;
        if (successor != node) {
            transplant(node, successor);
            successor->left = node->left;
            successor->left->parent = successor;
            successor->right = node->right;
            if (successor->right != nullptr) {
                successor->right->parent = successor;
            }
            successor->color = node->color;
        }
        node->left = nullptr;
        node->right = nullptr;
        delete node;
        if (removed_black and root != nullptr) {
            // reballance tree after deletion
            if (balancing != nullptr) {
                balancing->color = Color::Black;
            }
            else {
                while (true) {
                    if (sibling->is_right_child()) {
                        if (sibling->color == Color::Red) {
                            sibling->color = Color::Black;
                            sibling->parent->color = Color::Red;
                            rotate_left(sibling->parent);
                            sibling = sibling->left->right;
                        }
                        if (is_black_node(sibling->left) and is_black_node(sibling->right)) {
                            sibling->color = Color::Red;
                            balancing = sibling->parent;
                            if (balancing == root or balancing->color == Color::Red) {
                                balancing->color = Color::Black;
                                break;
                            }
                            sibling = balancing->sibling();
                            // continue;
                        }
                        else {
                            if (is_black_node(sibling->right)) {
                                sibling->left->color = Color::Black;
                                sibling->color = Color::Red;
                                rotate_right(sibling);
                                sibling = sibling->parent;
                            }
                            sibling->color = sibling->parent->color;
                            sibling->parent->color = Color::Black;
                            sibling->right->color = Color::Black;
                            rotate_left(sibling->parent);
                            break;
                        }
                    }
                    else {
                        if (sibling->color == Color::Red){
                            sibling->color = Color::Black;
                            sibling->parent->color = Color::Red;
                            rotate_right(sibling->parent);
                            sibling = sibling->right->left;
                        }
                        if (is_black_node(sibling->left) and is_black_node(sibling->right)) {
                            sibling->color = Color::Red;
                            balancing = sibling->parent;
                            if (balancing->color == Color::Red or balancing == root) {
                                balancing->color = Color::Black;
                                break;
                            }
                            sibling = balancing->sibling();
                            // continue;
                        }
                        else {
                            if (is_black_node(sibling->left)) {
                                sibling->right->color = Color::Black;
                                sibling->color = Color::Red;
                                rotate_left(sibling);
                                sibling = sibling->parent;
                            }
                            sibling->color = sibling->parent->color;
                            sibling->parent->color = Color::Black;
                            sibling->left->color = Color::Black;
                            rotate_right(sibling->parent);
                            break;
                        }
                    }
                } // while
            }
        }
        --tree_size;
    }


    // lookup
    inline size_t count(const Key &key) const noexcept
    {
        return find(key) != nullptr;
    }

    inline Node *find(const Key &key) const noexcept // TODO: iterators
    {
        auto node = root;
        while (node != nullptr) {
            if (cmp(node->key, key)) {
                node = node->right;
            }
            else if (cmp(key, node->key)) {
                node = node->left;
            }
            else { // ==
                return node;
            }
        }
        return nullptr;
    }

    inline bool contains(const Key &key) const noexcept
    {
        return find(key) != nullptr;
    }


    // testcase
    void check() const noexcept
    {
        if (root != nullptr) {
            assert(root->color == Color::Black);
            assert(root->parent == nullptr);
            int maxh = 0;
            int minh = 0;
            root->check(maxh, minh);
        }
    }

private:
    inline bool is_red_node(Node *node) const noexcept
    {
        return node != nullptr
           and node->color == Color::Red;
    }

    inline bool is_black_node(Node *node) const noexcept
    {
        return node == nullptr
            or node->color == Color::Black;
    }

    inline void transplant(Node *branch, Node *node) noexcept
    {
        if (branch->parent == nullptr) {
            root = node;
        }
        else if (branch->is_right_child()) {
            branch->parent->right = node;
        }
        else {
            branch->parent->left = node;
        }
        if (node != nullptr) {
            node->parent = branch->parent;
        }
    }

    void rotate_left(Node *node) noexcept
    {
        assert(node->right != nullptr);
        auto y = node->right;
        node->right = y->left;
        y->left = node;
        transplant(node, y);
        node->parent = y;
        if (node->right != nullptr) {
            node->right->parent = node;
        }
    }

    void rotate_right(Node *node) noexcept
    {
        assert(node->left != nullptr);
        auto y = node->left;
        node->left = y->right;
        y->right = node;
        transplant(node, y);
        node->parent = y;
        if (node->left != nullptr) {
            node->left->parent = node;
        }
    }

    std::pair<Node *, bool> find_or_insert(const Key &key) MAYTHROW
    {
        Node *node = nullptr;
        Node **ptr = &root;
        while (*ptr != nullptr) {
            node = *ptr;
            if (cmp(node->key, key)) {
                ptr = &node->right;
            }
            else if (cmp(key, node->key)) {
                ptr = &node->left;
            }
            else { // ==
                return std::make_pair(node, false);
            }
        }
        *ptr = new Node(key, node);
        node = *ptr;
        auto result = std::make_pair(node, true);
        ++tree_size;
        // reballance tree after insertion
        while (is_red_node(node->parent)) {
            // if we have a red parent, we must have a grandparent
            auto grandparent = node->parent->parent;
            if (node->parent->is_right_child()) {
                if (is_red_node(grandparent->left)) {
                    node->parent->color = Color::Black;
                    grandparent->left->color = Color::Black;
                    node = grandparent;
                    node->color = Color::Red;
                }
                else {
                    if (not node->is_right_child()) {
                        node = node->parent;
                        rotate_right(node);
                    }
                    node->parent->color = Color::Black;
                    grandparent->color = Color::Red;
                    rotate_left(grandparent);
                }
            }
            else {
                if (is_red_node(grandparent->right)) {
                    node->parent->color = Color::Black;
                    grandparent->right->color = Color::Black;
                    node = grandparent;
                    node->color = Color::Red;
                }
                else {
                    if (node->is_right_child()) {
                        node = node->parent;
                        rotate_left(node);
                    }
                    node->parent->color = Color::Black;
                    grandparent->color = Color::Red;
                    rotate_right(grandparent);
                }
            }
        }
        root->color = Color::Black;
        return result;
    }

private:
    Node *root = nullptr;
    size_t tree_size = 0;
    Comparator cmp;
};


#endif // RB_TREE_HPP
