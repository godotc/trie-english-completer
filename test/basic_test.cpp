
#include "gtest/gtest.h"
#include <TrieTree.h>
#include <algorithm>
#include <iostream>
#include <set>
#include <vector>


TEST(TrieTree, InsertAndGet)
{
    trie::TrieTree trie;
    std::cerr << "start...\n";

    for (auto &x : {"abc", "abcd", "abdc"}) {
        trie.Insert(x);
    }

    auto ret = trie.GetSuccessors("abc");
    for (auto &x : ret) {
        std::cerr << x << "\n";
    }


    EXPECT_NE(ret.size(), 0);


    auto right = {"abc", "abcd"};

    for (auto x : right) {
        EXPECT_TRUE(std::find(ret.begin(), ret.end(), x) != ret.end());
    }
}
