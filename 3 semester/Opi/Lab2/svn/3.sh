#!/bin/bash
svnadmin create repos1
svn checkout file:///home/s192443/repos1 project1
cd project1
mkdir trunk
mkdir branches
mkdir tags
svn add * 
svn commit -m "add files"  
cd trunk
cp ../../commit0/* .
svn add *
svn commit -m "commited r0 in trunk" --username "Yura"
cd ..
svn cp trunk branches/br2
cd branches
cd br2
cp ../../../commit1/* .
svn add *
svn commit -m "commited r1 in second branch" --username "Sasha"
cd ..
cd ..
svn cp branches/br2 branches/br3
cd branches
cd br3
cp ../../../commit2/* .
svn commit -m "commited r2 in third branch" --username "Sasha"
cd ..
cd ..
cd trunk
cp ../../commit3/* .
svn add *
svn commit -m "commited r3 in trunk" --username "Yura"
cd ..
cd branches
cd br3
cp ../../../commit4/* .
svn commit -m "commited r4 in branch 3" --username "Sasha"
cp ../../../commit5/* .
svn commit -m "commited r5 in branch 3" --username "Sasha"
cd ..
cd ..
cd ..
svn checkout file:///home/s192443/repos/trunk
