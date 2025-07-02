#ifndef TrigEffNSFs_BranchInterface_hpp
#define TrigEffNSFs_BranchInterface_hpp

#include <TTree.h>
#include <Rtypes.h> // Bool_t, Int_t, Float_t
#include <string>

class TrigEffNSFs_BranchInterface {

  public:
  
    // Trigger bits
    Bool_t passTrigger_HLT_IsoMu27{false};
    Bool_t passTrigger_HLT_PFHT1050{false};
    Bool_t passTrigger_6J1T_B{false}, passTrigger_6J1T_CDEF{false};
    Bool_t passTrigger_6J2T_B{false}, passTrigger_6J2T_CDEF{false};
    Bool_t passTrigger_4J3T_B{false}, passTrigger_4J3T_CDEF{false};

    // Object counts
    Int_t  nMuons{-5}, nElecs{-5}, nJets{-5}, nbJets{-5};
    
    // Kinematics
    Float_t HT{-100.0};
    static const int MAX_JETS = 30;
    Float_t jetPt[MAX_JETS]{-100.0};
    Float_t jetEta[MAX_JETS]{-100.0};
    Float_t bTagScore[MAX_JETS]{-20.0};
    Int_t   hadFlavs[MAX_JETS]{-5};
////    Int_t   partonFlavs[MAX_JETS]{-5};

    // Event meta-data
    UInt_t  eventNumber{1};
    UInt_t  runNumber{1};

    // Weights & filters
    Float_t PUWeight{-50000.0}, L1PrefiringWeight{-50000.0};
    Bool_t failGoldenJson{true}, passMETFilters{false};

    // Bind all branches of the tree to this interface
    void SetBranchAddresses(TTree* tree);

    // Disable/Enable a branch by name (turn off/on reading for that branch)
    void DisableBranch(const std::string& branchName);
    void EnableBranch(const std::string& branchName);
 
    // Enable internal debug prints
    void SetDebug(bool dbg);

  private:

    TTree* treePtr_{nullptr};
    bool   debug_{false};

};

#endif // #ifdef TrigEffNSFs_BranchInterface_cxx
