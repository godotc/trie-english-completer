#include "pack.h"
#include <gtest/gtest.h>



TEST(TrieTree, test_pack_c_style)
{
    trie::PackTrie trie(6);

    trie.SourceFromFileP("/tmp/english-words.txt");

    trie.GetSuccersorsP("Hello");
}
