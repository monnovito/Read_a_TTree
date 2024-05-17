#include <iostream>
#include <string>
#include <algorithm> // For std::replace

void root_to_Class(const char* filename, const char* treename) {
  // Open the ROOT file
  TFile *input = TFile::Open(filename, "READ");
  if (!input || input->IsZombie()) {
    std::cerr << "Error: Unable to open file or file is corrupted.\n";
    delete input;
    return;
  }

  // Get the TTree from the file
  TTree *tree = (TTree*) input->Get(treename);
  if (!tree) {
    std::cerr << "Error: Unable to retrieve TTree from the file.\n";
    input->Close();
    delete input;
    return;
  }

  // Replace semicolons in the tree name with underscores
  std::string modified_treename(treename);
  std::replace(modified_treename.begin(), modified_treename.end(), ';', '_');

  // Create the class name
  std::string classname = "Class_" + modified_treename;

  // Generate the class
  tree->MakeClass(classname.c_str());

  // Clean up
  input->Close();
  delete input;
}
