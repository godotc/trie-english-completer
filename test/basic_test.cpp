
#include "gtest/gtest.h"
#include <TrieTree.h>
#include <iostream>
#include <vector>


TEST(TrieTree, InsertAndGet)
{
    trie::TrieTree trie;
    std::cerr << "start...\n";

    for (auto &x : {"abc", "abcd", "abdc"}) {
        trie.Insert(x);
    }

    auto ret = trie.GetSuccessors("ab");
    for (auto &x : ret) {
        std::cerr << x << "\n";
    }


    EXPECT_NE(ret.size(), 0);


    std::vector<std::string> right = {"abc", "abcd"};
    for (int i = 0; i < ret.size(); ++i) {
        EXPECT_EQ(ret[i], right[i]);
    }
}
