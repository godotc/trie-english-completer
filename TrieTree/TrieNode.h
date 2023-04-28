#pragma once

#include <algorithm>
#include <memory>
#include <unordered_map>
namespace trie {

class TrieNode
{
  public:

    explicit TrieNode(char key_char)
    {
        _key_char = key_char;
        _is_end   = false;
    }

    TrieNode(TrieNode &&other_trie_node) noexcept
    {
        _key_char                 = other_trie_node._key_char;
        _is_end                   = other_trie_node._key_char;
        other_trie_node._key_char = '\0';
        other_trie_node._is_end   = false;
        _chilren                  = std::move(other_trie_node._chilren);
    }

    virtual ~TrieNode() = default;

  public:
    bool HasChild(char c) const { return _chilren.find(c) != _chilren.end(); }
    bool HasChildren() const { return !_chilren.empty(); }
    bool IsEndNode() const { return _is_end; }

    char GetKeyChar() const { return _key_char; }


  public:

    auto InsertChildNode(char key_char, std::unique_ptr<TrieNode> &&child) -> std::unique_ptr<TrieNode> *
    {
        if (key_char != child->GetKeyChar())
            return nullptr;

        if (_chilren.find(key_char) != _chilren.end())
            return nullptr;

        _chilren.emplace(key_char, std::move(child));
        return &_chilren[key_char];
    }

    auto GetChildNode(char key_char) -> std::unique_ptr<TrieNode> *
    {
        auto it = _chilren.find(key_char);
        if (it != _chilren.end()) {
            return &(it->second);
        }
        return nullptr;
    }

    void RemoveChildNode(char key_char) { _chilren.erase(key_char); };

    void SetEndNode(bool is_end) { _is_end = is_end; };

    const auto GetChilren()
    {
        return &_chilren;
    }

  private:
    char _key_char;
    bool _is_end;

    std::unordered_map<char, std::unique_ptr<TrieNode>> _chilren;
};

} // namespace trie
