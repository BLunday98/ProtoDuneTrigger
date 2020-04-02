//some standard C++ includes
#include <iostream>
#include <string>
#include <vector>

//some ROOT includes
#include "TFile.h"
#include "TSystemDirectory.h"
#include "TString.h"

//"art" includes (canvas, and gallery)
#include "canvas/Utilities/InputTag.h"
#include "gallery/Event.h"
#include "gallery/ValidHandle.h"

//"larsoft" object includes
#include "lardataobj/RecoBase/Hit.h" // -- recob::Hit

//convenient for us! let's not bother with art and std namespaces!
using namespace art;
using namespace std;

int main(int argc, char* argv[]){
  TString dirname1    = "/pnfs/dune/persistent/users/drivera/protoDUNE_cosmic_and_bkg_prim_studies";
  TString output_name = "skimmed_PDSP_output.root";
  TString contains    = "trigprim_test.root";
  TString extension   = ".root";
  TString usage       = "./Skim_PDSP <input_directory> <output_file_name> <contains>";
  TString example     = "./Skim_PDSP /pnfs/dune/persistent/users/drivera/protoDUNE_cosmic_and_bkg_prim_studies skimmed_PDSP_output.root trigprim_test.root";

  if (argc < 3){
    cout << "Need directory and output name to run" << endl;
    cout << "Usage: \n" << usage.Data() << endl;
    cout << "Example: \n" << example.Data() << endl;
    return 1;
  }
  else if (argc==3){
    dirname1    = argv[1];
    output_name = argv[2];
  }
  else if (argc==4){
    dirname1    = argv[1];
    output_name = argv[2];
    contains    = argv[3];
  }
  else{
    cout << "Too many arguments" << endl;
    cout << usage.Data() << endl;
    cout << example.Data() << endl;
    return 1;
  }

  vector<string> filenames;
  int run;
  int event;

  // -- will get used to retrieve multiple "fasthit" objects
  // -- Note: must match the module label for the recob::Hit objects
  vector<TString> tags = {"15","18"};

  vector<vector<unsigned int>> hit_channel(tags.size());
  vector<vector<unsigned int>> hit_peak_time(tags.size());
  vector<vector<unsigned int>> hit_tot(tags.size());
  vector<vector<unsigned int>> hit_sum_adc(tags.size());

  TFile* output_file = new TFile(output_name, "RECREATE");
  TString tag;

  // -- tree name "tree" must match what we access in the Adjacency Algorithms
  TTree tree("tree","Skimmed PDSP");

  // -- required branches:
  tree.Branch("Run",&run);
  tree.Branch("Event_Num",&event);

  // -- branch names must match what we read in the Adjacency Algorithms
  for (unsigned int i=0; i < tags.size(); ++i){
    tree.Branch("Hit_"+tags.at(i)+"_Channels",&hit_channel.at(i));
    tree.Branch("Hit_"+tags.at(i)+"_Peak_Time",&hit_peak_time.at(i));
    tree.Branch("Hit_"+tags.at(i)+"_TOT",&hit_tot.at(i));
    tree.Branch("Hit_"+tags.at(i)+"_Sum_ADC",&hit_sum_adc.at(i));
  }
  // -- end of required branches

  output_file->cd();

  TSystemDirectory dir(dirname1,dirname1);
  TList *files = dir.GetListOfFiles();
  if (files){
    TSystemFile *file;
    TString fname, tmpname;

    TIter next(files);
    while ((file=(TSystemFile*)next())){
      fname = file->GetName();
      if (!file->IsDirectory() && fname.Contains(contains) && fname.EndsWith(extension)){
	      tmpname = dirname1 + "/" + fname;
	      filenames.push_back((string)tmpname.Data());
      }
    }
  }
  
  for (unsigned int i=0; i < filenames.size(); ++i){
    cout << filenames.at(i) << endl;
  }
  
  // -- We need to specify the "input tag" for our collection of hits.
  // -- This is like the module label, except it can also include process name
  // -- and an instance label. Format is like this:
  // -- InputTag mytag{ "module_label","instance_label","process_name"};
  // -- You can ignore instance label if there isn't one. If multiple processes
  // -- used the same module label, the most recent one should be used by default.

  // -- Check the contents of your file by setting up a version of larsoft, and
  // -- running an event dump:
  //    lar -c eventdump.fcl -s MyInputFile_1.root -n 1 | grep "std::vector<recob::Hit>"
  InputTag fast_hit_tag;

  for (gallery::Event ev(filenames) ; !ev.atEnd(); ev.next()) {

    // -- to get run and event info, you use this "eventAuxillary()" object.
    run = ev.eventAuxiliary().run();
    event = ev.eventAuxiliary().event();
    cout << "\nProcessing "
	    << "Run "   << run   << ", "
	    << "Event " << event << endl;
   
    // -- loop over the "fasthit" tag(s) 
    for (unsigned int j=0; j < tags.size(); ++j){
      tag = "fasthit"+tags.at(j);
      fast_hit_tag = {(string)tag.Data()};
      auto const& fast_hit_handle = ev.getValidHandle<vector<recob::Hit>>(fast_hit_tag);
      auto const& fast_hit_vec(*fast_hit_handle);

      // -- extract hit info
      for (unsigned int i=0; i < fast_hit_vec.size(); ++i){
	      hit_channel.at(j).push_back(fast_hit_vec.at(i).Channel());
	      hit_peak_time.at(j).push_back(fast_hit_vec.at(i).PeakTime());
	      hit_tot.at(j).push_back((unsigned int)(fast_hit_vec.at(i).EndTick()-fast_hit_vec.at(i).StartTick()));
	      hit_sum_adc.at(j).push_back(fast_hit_vec.at(i).SummedADC());
      }
    }

    // -- fill output tree
    tree.Fill();

    // -- clear vectors
    for (unsigned int i=0; i < tags.size(); ++i) {
      hit_channel.at(i).clear();
      hit_peak_time.at(i).clear();
      hit_tot.at(i).clear();
      hit_sum_adc.at(i).clear();
    }
  }
  cout << "Writing" << endl; 
  output_file->Write();
  cout << "Closing" << endl;
  output_file->Close();
  filenames.clear();  
  return 0;
}
