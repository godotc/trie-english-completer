#pragma once
#include "TrieTree.h"
#include <cstddef>

namespace trie {

class PackTrie : public TrieTree
{

  public:
    explicit PackTrie(int outsize = 5) : TrieTree(outsize) {}


  public:
    void SourceFromFileP(const char *FileName, int n = 0)
    {
        SourceFromFile(FileName, n);
    }

    void InsertP(const char *word)
    {
        Insert(word);
    }

    auto GetSuccersorsP(const char *prefix)
    {
        return GetSuccessors(prefix);
    }
};

} // namespace trie
