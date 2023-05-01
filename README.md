
# English Completer

A toy of a text editor. Which will complete english words based on trietree.

GUI framework  I choose Qt. So most feature's implementaion just from packge, and this not a project start from lower level.

1. Trie tree to orgnaize englsh words dataset.
2. Qt as GUI framework.
3. Trigger complete prompt pannel when typing words.

## Run it

###  Required:
1. Qt SDK >= 5.15 
2. [xmake](!https://xmake.io/#/guide/installation)

### Commands 

```sh
make cfg # generate debug config files and compile_commands for `clangd`

xmake requre # install dependencies pacakge 
xmake build
xmake run
```

## Plan

### Complete

- [x] A simple widget frame that can hardly input characters and popup wordlist. 🥲
- [x] Implement the trie tree for load words from file. And get suggestions from prefix which inputted in textedit from datastruct.
- [x] Adjust the suggestion list size.
- [x] Migration from native cpp trie to qt.

### TODO

- [ ] Optimize when the word_list to popup.
- [ ] Detect the word which was inputtin is the first word of sentence or not. If true, will insert suggestion which first char is uppercase.
- [ ] Optimize the suggestion's letter priority, make its recommandation more intelligent.

### TBD

- [ ] Add open file button and save feature.
- [ ] Add more hook point for shortcut.
- [ ] Config the font, size, editor scheme.

