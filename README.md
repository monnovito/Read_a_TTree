# Read_a_TTree
Some instructions to read a not trivial TTree from a .root file using TTree::MakeClass()

1. let's assume you got a .root with a TTree and ROOT working on your machine. 
   
2. use the C script 'root_to_Class.C' to make your Class.
   Execute it with the terminal command knowing file name and the tree name:
   
   ```
   root -l -b -q 'root_to_Class.C("filename.root", "treename")'
   ```
   
   this will produce Class_treename.C and Class_treename.h

   Class_treename.h manages all classes you need and some member functions. 
    just notice that your TTree is pointed to 'fChain'.

   Class_treename.C manages the Loop() function which is the main data analysis function.
   how access branches is write on the file itself. just notice that jentry and ientry are on tree indexes,
   so you gonna need an additional loop to read leaves. e.g. :
   
   ```
   //in the main for Loop
       for (unsigned int i = 0; i < leaf->size(); i++) {
         h->Fill(leaf->at(i));
      }
   ```
3. Now assuming Loop() is written, in order to execute it open root terminal and execute it as following.

   * add your .C file in library:
      ```
      .L Class_treename.C
      ```
   * create object of your new class, e.g. called 't'
     ```
      Class_treename t
      ```
   * now execute the Loop()
     ```
      t.Loop()
      ```
   * notice that t now contain all, so you can do some fast data check:
     ```
      t.fChain->Loop()
      t.fChain->Print()
      ```
