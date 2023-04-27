#pragma once

#include "TrieNode.h"
#include <memory>
#include <mutex>
#include <string>
#include <string_view>
#include <tuple>
#include <vector>

namespace trie {

class TrieTree
{
  public:
    TrieTree()
    {
        _root = std::make_unique<TrieNode>('\0');
    }

  public:
    bool Insert(const std::string &key)
    {
        auto node = &_root;
        auto ptr  = node;

        std::lock_guard<std::mutex> lock(mtx);

        for (auto c : key)
        {
            if (node->get()->HasChild(c)) {
                node = node->get()->GetChildNode(c);
            }
            else {
                ptr = node->get()->InsertChildNode(c, std::make_unique<TrieNode>(c));
                if (!ptr)
                    return false;
                node = ptr;
            }
        }

        node->get()->SetEndNode(true);

        return true;
    }

    std::vector<std::string> GetSuccessors(const std::string &prefix)
    {
        std::vector<std::string> ret;

        auto node = &_root;

        int n = prefix.size();
        int i = 0;
        for (; i < n; ++i) {
            char ch = prefix[i];

            if (node->get()->HasChild(ch)) {
                node = node->get()->GetChildNode(ch);
            }
            else break;
        }
        if (i != n) return ret;

        getSuccessorsFromNode(prefix, node, ret);


        return ret;
    }


  private:
    void getSuccessorsFromNode(const std::string &prefix, const std::unique_ptr<TrieNode> *node, std::vector<std::string> &ret)
    {
        if (!node->get()->HasChildren()) return;
        const auto Chilren = node->get()->GetChilren();


        // TODO: compile error
        for (const auto &child : Chilren)
        {
            char        key        = child.first;
            std::string t          = prefix + key;
            const auto  child_node = node->get()->GetChildNode(key);

            ret.emplace_back(t);
            getSuccessorsFromNode(t, child_node, ret);
        }
    }


  private:
    std::unique_ptr<TrieNode> _root;

    std::mutex mtx;
};
} // namespace trie
