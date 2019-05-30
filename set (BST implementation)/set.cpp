#include "set.h"

void print(std::ostream& out, const treenode* n, size_t indent)
{

    for (size_t i = 0; i != indent; ++i)
        out << "|  ";
    if (n) {
        out << (n->val) << "\n";
        print(out, n->left, indent + 1);
        print(out, n->right, indent + 1);
    }
    else
        out << "#\n";
}

void checksorted(
    treenode* n,
    const std::string* lowerbound,
    const std::string* upperbound)
{
    while (n) {
        if (lowerbound && !before(*lowerbound, n->val)) {
            std::cout << "value " << (n->val);
            std::cout << " is not above lower bound " << *lowerbound << "\n";
            std::abort();
        }

        if (upperbound && !before(n->val, *upperbound)) {
            std::cout << "value " << (n->val);
            std::cout << "is not below upperbound " << *upperbound << "\n";
            std::abort();
        }

        checksorted(n->left, lowerbound, &(n->val));
        lowerbound = &(n->val);
        n = n->right;
    }
}

void writecopy(treenode** to, treenode* from)
{
    while (from) {
        *to = new treenode{ from->val };

        writecopy(&(*to)->left, from->left);
        to = &(*to)->right;
        from = from->right;
    }
}

void deallocate(treenode* n)
{
    while (n) {
        deallocate(n->left);
        treenode* bye = n;
        n = n->right;
        delete bye;
    }
}

size_t log_base2(size_t s) { return (s > 1) ? 1 + log_base2(s / 2) : 0; }

// From previous task:

bool equal(const std::string& s1, const std::string& s2)
{
    if (s1.length() == s2.length()) {
        for (size_t i = 0; i < s1.length(); i++) {
            if (tolower(s1[i]) != tolower(s2[i]))
                return false;
        }
        return true;
    }
    return false;
}

// Must be written for task 5(part 2) :

bool before(const std::string& s1, const std::string& s2)
{
    for (size_t i = 0; i < s1.length() && i < s2.length(); i++) {
        if (tolower(s1[i]) < tolower(s2[i]))
            return true;
        else if (tolower(s1[i]) > tolower(s2[i]))
            return false;
    }
    return false;
}

const treenode* find(const treenode* n, const std::string& el)
{

    if (n == nullptr)
        return n;

    else if (equal(n->val, el))
        return n;

    else if (before(n->val, el))
        return find(n->right, el);

    else
        return find(n->left, el);
}
// Write this one first.

treenode** find(treenode** n, const std::string& el)
{
    if (*n == nullptr)
        return n;

    if (equal((*n)->val, el))
        return n;

    else if (before((*n)->val, el))
        return find(&((*n)->right), el);

    else
        return find(&(*n)->left, el);
}
// Modify the other find into this one, also have a look at
// stackscan4.pdf

// Insert n at the right most position in into:

void rightinsert(treenode** into, treenode* n)
{
    for (; (*into)->right != nullptr; into = &(*into)->right)
        ;
    (*into)->right = n;
}

size_t size(const treenode* n)
{
    if (n == nullptr)
        return 0;
    else
        return (size(n->left) + 1 + size(n->right));
}

size_t height(const treenode* n)
{
    if (n == nullptr)
        return 0;

    size_t lDepth = height(n->left);
    size_t rDepth = height(n->right);

    if (lDepth > rDepth)
        return (lDepth + 1);
    else
        return (rDepth + 1);
}

bool set::insert(const std::string& el)
{

    treenode** ptr = find(&tr, el);
    if (*ptr != nullptr)
        return false;
    else {
        *ptr = new treenode{ el };
        return true;
    }
}

bool set::contains(const std::string& el) const
{
    return find(tr, el) != nullptr;
}

bool set::remove(const std::string& el)
{
    treenode** ptr = find(&tr, el);
    if (*ptr == nullptr)
        return false;
    if (((*ptr)->left == nullptr) && ((*ptr)->right == nullptr)) {
        treenode* bye = (*ptr);
        (*ptr) = nullptr;
        delete bye;
    }
    else if (((*ptr)->left != nullptr) && ((*ptr)->right == nullptr)) {
        treenode* bye = (*ptr);
        (*ptr) = (*ptr)->left;
        delete bye;
    }

    else if (((*ptr)->left == nullptr) && ((*ptr)->right != nullptr)) {
        treenode* bye = (*ptr);
        (*ptr) = (*ptr)->right;
        delete bye;
    }
    else {
        treenode* bye = (*ptr);
        rightinsert(&(*ptr)->left, bye->right);
        (*ptr) = (*ptr)->left;
        delete bye;
    }
    return true;
}

void set::checksorted() const
{
    ::checksorted(tr, nullptr, nullptr);
    // :: are needed because the other checksorted is not in the class.
}

std::ostream& set::print(size_t indent, std::ostream& out) const
{
    ::print(out, tr, indent);
    return out;
}

