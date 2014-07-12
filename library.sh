#/#!/bin/bash

cat Geometry/Geometry.cpp   >> Geometry.cpp
cat Geometry/Intersect.cpp  >> Geometry.cpp
cat Geometry/Convex.cpp     >> Geometry.cpp

cat Graph/ShortestPath.cpp                >> Graph.cpp
cat Graph/MinimumSpanningTree.cpp         >> Graph.cpp
cat Graph/FordFulkerson.cpp               >> Graph.cpp
cat Graph/Dinic.cpp                       >> Graph.cpp
cat Graph/MinCostFlow.cpp                 >> Graph.cpp
cat Graph/BipartiteMatching.cpp           >> Graph.cpp
cat Graph/StronglyConnectedComponents.cpp >> Graph.cpp
cat Graph/2SAT.cpp                        >> Graph.cpp
cat Graph/LCA\(BinarySearch\).cpp         >> Graph.cpp
cat Graph/LCA\(RMQ\).cpp                  >> Graph.cpp
cat Graph/ShortestHamiltonPath.cpp        >> Graph.cpp
cat Graph/ArticulationPoints.cpp          >> Graph.cpp
cat Graph/Bridge.cpp                      >> Graph.cpp

cat Math/Math.cpp         >> Math.cpp
cat Math/Matrix.cpp       >> Math.cpp
cat Math/SquareMatrix.cpp >> Math.cpp

cat Others/Compressor.cpp        >> Others.cpp
cat Others/LIS.cpp               >> Others.cpp
cat Others/Dice.cpp              >> Others.cpp
cat Others/RegularOctahedron.cpp >> Others.cpp

cat Structure/UnionFind.cpp         >> Structure.cpp
cat Structure/SegmentTree.cpp       >> Structure.cpp
cat Structure/FenwickTree.cpp       >> Structure.cpp
cat Structure/SqrtDecomposition.cpp >> Structure.cpp
cat Structure/Treap.cpp             >> Structure.cpp

OPT="--highlight=cpp --color --landscape --columns=2"
enscript $OPT -o Geometry.ps Geometry.cpp
enscript $OPT -o Graph.ps Graph.cpp
enscript $OPT -o Math.ps Math.cpp
enscript $OPT -o Others.ps Others.cpp
enscript $OPT -o Structure.ps Structure.cpp
enscript $OPT -o Template.ps Template.cpp
enscript --highlight=elisp --color --landscape --columns=2 -o Emacs.ps .emacs

rm -f Geometry.cpp
rm -f Graph.cpp
rm -f Math.cpp
rm -f Others.cpp
rm -f Structure.cpp
