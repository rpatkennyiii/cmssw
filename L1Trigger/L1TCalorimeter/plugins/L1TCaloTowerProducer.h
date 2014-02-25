#ifndef L1TCaloTowerProducer_h
#define L1TCaloTowerProducer_h

// -*- C++ -*-
//
// Package:    L1Trigger/skeleton
// Class:      skeleton
// 
/**\class skeleton skeleton.cc L1Trigger/skeleton/plugins/skeleton.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  James Brooke
//         Created:  Thu, 05 Dec 2013 17:39:27 GMT
//
//


// system include files
#include <boost/shared_ptr.hpp>

// user include files

#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/EDGetToken.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"



//
// class declaration
//

namespace l1t {
    
  class L1TCaloTowerProducer : public edm::EDProducer { 
  public:
    explicit L1TCaloTowerProducer(const edm::ParameterSet& ps);
    ~L1TCaloTowerProducer();

    static void fillDescriptions(edm::ConfigurationDescriptions& descriptions)
;

  private:
      virtual void beginJob() override;
      virtual void produce(edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;
      
      //virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
      //virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;

      // ----------member data ---------------------------

      int bxFirst_, bxLast_; // bx range to process

      std::vector<edm::EDGetToken> ecalToken_;  // this is a crazy way to store multi-BX info
      std::vector<edm::EDGetToken> hcalToken_;  // should be replaced with a BXVector< > or similar

      int ietaMin_, ietaMax_, iphiMin_, iphiMax_;

  }; 
  
} 

#endif
