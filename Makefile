bin/testTableEntry: testTableEntry.cpp TableEntry.h
	mkdir -p bin
	g++ -o bin/testTableEntry testTableEntry.cpp -std=c++11

bin/testHashTable: testHashTable.cpp Dict.h HashTable.h TableEntry.h
	mkdir -p bin
	g++ -o bin/testHashTable testHashTable.cpp -std=c++11

bin/testBSTree: testBSTree.cpp BSTree.h BSNode.h 
	mkdir -p bin
	g++ -o bin/testBSTree testBSTree.cpp -std=c++11

bin/testBSTreeDict: Dict.h BSTreeDict.h BSNode.h TableEntry.h testBSTreeDict.cpp
	mkdir -p bin
	g++ -o bin/testBSTreeDict testBSTreeDict.cpp -std=c++11

clean:
	rm -rf *.o *.gch bin
