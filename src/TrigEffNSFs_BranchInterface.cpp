#define TrigEffNSFs_BranchInterface_cxx

#include "TrigEffNSFs_BranchInterface.hpp"
#include <iostream>

void TrigEffNSFs_BranchInterface::SetBranchAddresses(TTree* tree) {

    if (!tree) {
        std::cerr << "[TrigEffNSFs_BranchInterface] Null TTree pointer!" << std::endl;
        return;
    }

    treePtr_ = tree;

    tree->SetBranchAddress("passTrigger_HLT_IsoMu27",  &passTrigger_HLT_IsoMu27);
    tree->SetBranchAddress("passTrigger_HLT_PFHT1050", &passTrigger_HLT_PFHT1050);
    tree->SetBranchAddress("passTrigger_6J1T_B",       &passTrigger_6J1T_B);
    tree->SetBranchAddress("passTrigger_6J1T_CDEF",    &passTrigger_6J1T_CDEF);
    tree->SetBranchAddress("passTrigger_6J2T_B",       &passTrigger_6J2T_B);
    tree->SetBranchAddress("passTrigger_6J2T_CDEF",    &passTrigger_6J2T_CDEF);
    tree->SetBranchAddress("passTrigger_4J3T_B",       &passTrigger_4J3T_B);
    tree->SetBranchAddress("passTrigger_4J3T_CDEF",    &passTrigger_4J3T_CDEF);
    tree->SetBranchAddress("nMuons",                   &nMuons);
    tree->SetBranchAddress("nElecs",                   &nElecs);
    tree->SetBranchAddress("nJets",                    &nJets);
    tree->SetBranchAddress("HT",                       &HT);
    tree->SetBranchAddress("jetPt",                    &jetPt);
    tree->SetBranchAddress("jetEta",                   &jetEta);
    tree->SetBranchAddress("bTagScore",                &bTagScore);
    tree->SetBranchAddress("hadFlavs",                 &hadFlavs);
////    tree->SetBranchAddress("partonFlavs",              &partonFlavs);
    tree->SetBranchAddress("eventNumber",              &eventNumber);
    tree->SetBranchAddress("runNumber",                &runNumber);
    tree->SetBranchAddress("PUWeight",                 &PUWeight);
    tree->SetBranchAddress("L1PrefiringWeight",        &L1PrefiringWeight);
    tree->SetBranchAddress("failGoldenJson",           &failGoldenJson);
    tree->SetBranchAddress("passMETFilters",           &passMETFilters);

}

void TrigEffNSFs_BranchInterface::DisableBranch(const std::string& branchName) {

    if (!treePtr_) {
        std::cerr << "[TrigEffNSFs_BranchInterface] Cannot disable branch '"
                  << branchName << "': tree pointer is null\n";
        return;
    }
    treePtr_->SetBranchStatus(branchName.c_str(), 0);
    if (debug_) {
        std::cout << "[TrigEffNSFs_BranchInterface] Disabled branch '"
                  << branchName << "'\n";
    }
}

void TrigEffNSFs_BranchInterface::EnableBranch(const std::string& branchName) {

    if (!treePtr_) {
        std::cerr << "[TrigEffNSFs_BranchInterface] Cannot enable branch '"
                  << branchName << "': tree pointer is null\n";
        return;
    }
    treePtr_->SetBranchStatus(branchName.c_str(), 1);
    if (debug_) {
        std::cout << "[TrigEffNSFs_BranchInterface] Enabled branch '"
                  << branchName << "'\n";
    }
}

void TrigEffNSFs_BranchInterface::SetDebug(bool dbg) {
    debug_ = dbg;
}

