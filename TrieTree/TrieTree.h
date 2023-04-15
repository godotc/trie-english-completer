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


        return ret;
    }



  private:
    std::unique_ptr<TrieNode> _root;

    std::mutex mtx;
};
} // namespace trie
