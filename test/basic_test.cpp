
#include "gtest/gtest.h"
#include <TrieTree.h>
#include <algorithm>
#include <bits/chrono.h>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <ratio>
#include <set>
#include <string>
#include <vector>


TEST(TrieTree, insert_and_get)
{
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
    {
        trie::TrieTree trie;
        for (auto &x : {"app", "apple", "alaph", "anoce", "arange"})
            trie.Insert(x);

        for (auto &x : trie.GetSuccessors("ap"))
            std::cerr << x << "\n";
    }
}


TEST(TrieTree, load_from_file)
{
    {
        trie::TrieTree trie;
        std::string    s = "/tmp/english-words.txt";
        trie.SourceFromFile(s, 5);

        for (auto x : trie.GetSuccessors("A")) {
            std::cerr << x << " ";
        }
        std::cerr << "\n";
        for (auto x : trie.GetSuccessors("app")) {
            std::cerr << x << " ";
        }
        std::cerr << "\n";
    }

    {
        trie::TrieTree trie(5);
        std::string    s = "/tmp/english-words.txt";

        auto now = std::chrono::steady_clock::now();

        trie.SourceFromFile(s, 0);

        auto end      = std::chrono::steady_clock::now();
        auto duration = end - now;

        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
        std::cerr << "==============Total time:" << ms << " ms" << std::endl;


        auto ret = trie.GetSuccessors("app");
        for (auto x : ret) {
            std::cerr << x << " ";
        }

        EXPECT_NE(ret.size(), 0);

        std::cerr << "\n";
    }
}
