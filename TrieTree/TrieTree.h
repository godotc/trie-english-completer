#pragma once

#include "TrieNode.h"
#include <atomic>
#include <cctype>
#include <cstddef>
#include <cstdio>
#include <exception>
#include <fstream>
#include <functional>
#include <iostream>
#include <memory>
#include <mutex>
#include <stdexcept>
#include <string>
#include <string_view>
#include <sys/types.h>
#include <tuple>
#include <unordered_map>
#include <vector>

namespace trie {

class TrieTree
{
  public:
    explicit TrieTree(int outSize = 5)
    {
        _root           = std::make_unique<TrieNode>('\0');
        this->m_Outsize = outSize;
    }

  public:

    void SourceFromFile(const std::string &FileName, int n = 0)
    {

        std::ifstream ifs(FileName);
        if (ifs.fail() || !ifs.is_open()) {
            std::cerr << "Open file " << FileName << "Failed!" << std::endl;
        }

        uint size = 32;
        char word[32];
        int  count = 0;

        while (ifs.getline(word, size)) {
            int len = sizeof(word);
            if (len > 1 && std::islower(word[1])) {
                for (int i = 0; i < len; ++i) {
                    word[i] = tolower(word[i]);
                }
            }

            this->Insert(word);
            ++count;
            if (n != 0 && count == n) break;
        }

        printf("Load %d word of dataset\n", count);
    }

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

        // BUG:  may multiple recursion make it be negative, and make it as UINT_32_MAX
        // So it cannot be uint or size_t, int will be useful here
        // size_t count = m_Outsize;
        // BUG: assign a uint to int will also make overflow
        // int count = m_Outsize;
        std::atomic<int> count(m_Outsize);
        std::cout << "Init count: " << count << std::endl;

        getSuccessorsFromNode(prefix, node, ret, count);


        return ret;
    }



  private:
    void getSuccessorsFromNode(const std::string &prefix, const std::unique_ptr<TrieNode> *node, std::vector<std::string> &ret, std::atomic<int> &count)
    {
        if (count <= 0) return; // BUG: ==0 overflow
        if (node->get()->IsEndNode()) {
            ret.push_back(prefix);
            --count;
            if (count <= 0) return; // BUG: ==0 overflow
            std::cout << "Prefix:" << prefix << " Left " << count << std::endl;
        }


        if (!node->get()->HasChildren()) return;

        const auto Children = node->get()->GetChilren();

        for (const auto &child : *Children)
        {
            char        key        = child.first;
            std::string t          = prefix + key;
            const auto  child_node = node->get()->GetChildNode(key);

            getSuccessorsFromNode(t, child_node, ret, count);
        }
    }


  private:
    std::unique_ptr<TrieNode> _root;

    std::mutex mtx;

    int m_Outsize = 5;
};
} // namespace trie
