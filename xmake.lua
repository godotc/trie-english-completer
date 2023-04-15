add_rules("mode.debug", "mode.release")

set_languages("c++14")

add_requires("gtest")

add_includedirs("TrieTree/");


target("trie_tree")
	set_kind("shared")
	add_headerfiles("TrieTree/**.h")
	add_files("TrieTree/**.cpp")
		
		

target("english_complete")
    add_rules("qt.widgetapp")
    add_headerfiles("src/**.h")
    add_files("src/**.cpp")
	add_files("res.qrc")
    --add_files("src/mainwindow.ui")
    -- add files with Q_OBJECT meta (only for qt.moc)
	add_deps("trie_tree")


target("test")
	add_packages("gtest")
	add_files("test/**.cpp")
	add_headerfiles("src/**.h");
	add_deps("trie_tree")
