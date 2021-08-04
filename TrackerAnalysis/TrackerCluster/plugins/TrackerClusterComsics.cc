// -*- C++ -*-
//
// Package:    TrackerAnalysis/TrackerCluster
// Class:      TrackerCluster
// 
/**\class TrackerCluster TrackerCluster.cc TrackerAnalysis/TrackerCluster/plugins/TrackerCluster.cc
   
   Description: [one line class summary]
   
   Implementation:
   [Notes on implementation]
*/
//
// Original Author:  Jeremy Andrea
//         Created:  Mon, 30 Oct 2017 10:50:05 GMT
//
//


// system include files
#include <memory>

// user include files
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "DataFormats/Common/interface/View.h"
#include "DataFormats/TrackCandidate/interface/TrackCandidateCollection.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/TrackerCommon/interface/TrackerTopology.h"
#include "DataFormats/TrackerRecHit2D/interface/SiStripRecHit1D.h"
#include "DataFormats/TrackerRecHit2D/interface/SiStripRecHit2D.h"
#include "DataFormats/TrackingRecHit/interface/InvalidTrackingRecHit.h"
#include "DataFormats/SiStripDetId/interface/SiStripDetId.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h" 
#include "Geometry/Records/interface/TrackerDigiGeometryRecord.h"
#include "Geometry/CommonTopologies/interface/PixelGeomDetUnit.h"
#include "Geometry/TrackerGeometryBuilder/interface/TrackerGeometry.h"
#include "MagneticField/Engine/interface/MagneticField.h"
#include "MagneticField/Records/interface/IdealMagneticFieldRecord.h"
#include "RecoLocalTracker/ClusterParameterEstimator/interface/StripClusterParameterEstimator.h"
#include "RecoLocalTracker/SiStripClusterizer/interface/SiStripClusterInfo.h"
#include "RecoTracker/TransientTrackingRecHit/interface/TkTransientTrackingRecHitBuilder.h"
#include "TrackingTools/PatternTools/interface/TrajTrackAssociation.h"
#include "TrackingTools/PatternTools/interface/Trajectory.h"
#include "TrackingTools/Records/interface/TrackingComponentsRecord.h"
#include "TrackingTools/Records/interface/TransientRecHitRecord.h"
#include "TrackingTools/Records/interface/TransientTrackRecord.h"
#include "TrackingTools/TrajectoryState/interface/TrajectoryStateOnSurface.h"
#include "TrackingTools/TrajectoryState/interface/TrajectoryStateTransform.h"
#include "TrackingTools/TransientTrack/interface/TransientTrackBuilder.h"
#include "TrackingTools/TransientTrackingRecHit/interface/TransientTrackingRecHit.h"
#include "TrackingTools/TransientTrackingRecHit/interface/TransientTrackingRecHitBuilder.h"
#include <TTree.h>

//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<> and also remove the line from
// constructor "usesResource("TFileService");"
// This will improve performance in multithreaded jobs.

class TrackerCluster : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
public:
  explicit TrackerCluster(const edm::ParameterSet&);
  ~TrackerCluster();
  
  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
  
private:
  virtual void beginJob() override;
  virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
  virtual void endJob() override;
  double thickness(DetId id);
  
  // ----------member data ---------------------------
  
  edm::InputTag tkTraj_;

  const edm::EDGetTokenT<edm::View<reco::Track> > trackSrc_;
  const edm::EDGetTokenT<std::vector<Trajectory> > trajSrc_;
  const edm::EDGetTokenT<TrajTrackAssociationCollection> trajTrackAssociationSrc_;
  
  SiStripClusterInfo siStripClusterInfo_;

  TTree *smalltree;
  
  edm::Service<TFileService> fs;

  std::string ttrhbuilder_; 
  
  edm::ESHandle<MagneticField> bField;

  const TrackerGeometry* theTrackerGeometry;
  std::map<DetId,double> m_thicknessMap;
  
  //-----------------------
  //fill the tree per track
  int tree_track_nclusters;
  double tree_track_pt;
  double tree_track_eta;
  double tree_track_phi;
  int tree_track_nhits;
  double tree_track_NChi2;
  int runNumber,eventNumber,lumiBlock; 
  
  //then fill information of clusters
  //attached to the tracks
  
  int  tree_Cluster_subDet[10000]; 
  int tree_Cluster_PetalSide[10000];
  int tree_Cluster_LayerNbr[10000]; 
  int tree_Cluster_WheelSide[10000]; 
  double tree_Cluster_charge[10000];
  double tree_Cluster_path[10000];
  double tree_Cluster_tsosx[10000];
  double tree_Cluster_tsosy[10000];
  double tree_Cluster_SoverN[10000];
  double tree_Cluster_noise[10000];
  int    tree_Cluster_width[10000];
  double tree_Cluster_barycenter[10000];
  int    tree_Cluster_detID[10000];
  float tree_Cluster_LocalTracj_X[10000];
  float tree_Cluster_LocalTracj_Y[10000];
  float tree_Cluster_LocalTracj_Z[10000];
  
   // cluster position ----
  float tree_Cluster_locX[10000];
  float tree_Cluster_locY[10000];
  float tree_Cluster_globX[10000];
  float tree_Cluster_globY[10000];
  float tree_Cluster_globZ[10000];
  float tree_Cluster_tsosglobX[10000];
  float tree_Cluster_tsosglobY[10000];
  float tree_Cluster_tsosglobZ[10000];
  
  //-----------------------------
  //then fill information of clusters
  //attached to the tracks
  int tree_Strips_nstrip;
  int tree_Strips_idFirst[10000]; 
  int tree_Strips_idLast[10000]; 
  
  // strips infos ----
  int tree_Strips_stripCharges[10000];
  float	tree_Strips_stripGains[10000] ;
  float	tree_Strips_stripNoises[10000];
  bool 	tree_Strips_stripQualitiesBad[10000] ;
    
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
TrackerCluster::TrackerCluster(const edm::ParameterSet& iConfig):
  trackSrc_( consumes<edm::View<reco::Track> >( iConfig.getParameter<edm::InputTag>("trackLabel") )),
  trajSrc_( consumes<std::vector<Trajectory> >( iConfig.getParameter<edm::InputTag>("tkTraj") )),
  trajTrackAssociationSrc_( consumes<TrajTrackAssociationCollection>( iConfig.getParameter<edm::InputTag>("labelTrajToTrack") )),
  siStripClusterInfo_(consumesCollector(), std::string(""))
{
  //now do what ever initialization is needed
  usesResource("TFileService");
  
  //trackSrc_ = consumes<reco::TrackCollection>(src_);
  ttrhbuilder_ = iConfig.getParameter<std::string>("TTRHBuilder");
  
  smalltree = fs->make<TTree>("ttree", "ttree");
  
  //-----------------------
  //fill the tree per track
  smalltree->Branch("tree_track_nclusters", &tree_track_nclusters, "tree_track_nclusters/I" );
  smalltree->Branch("tree_track_pt",    &tree_track_pt,    "tree_track_pt/D" );
  smalltree->Branch("tree_track_eta",   &tree_track_eta,   "tree_track_eta/D" );
  smalltree->Branch("tree_track_phi",   &tree_track_phi,   "tree_track_phi/D" );
  smalltree->Branch("tree_track_nhits", &tree_track_nhits, "tree_track_nhits/I" );
  smalltree->Branch("tree_track_NChi2", &tree_track_NChi2, "tree_track_NChi2/D" );
  
  
  //then fill information of clusters
  //attached to the tracks
  
  smalltree->Branch("tree_Cluster_subDet",        tree_Cluster_subDet,       "tree_Cluster_subDet[tree_track_nclusters]/I"     );
  smalltree->Branch("tree_Cluster_PetalSide",     tree_Cluster_PetalSide,    "tree_Cluster_PetalSide[tree_track_nclusters]/I"  );
  smalltree->Branch("tree_Cluster_LayerNbr",      tree_Cluster_LayerNbr ,    "tree_Cluster_LayerNbr[tree_track_nclusters]/I"   );
  smalltree->Branch("tree_Cluster_WheelSide",     tree_Cluster_WheelSide,    "tree_Cluster_WheelSide[tree_track_nclusters]/I"  );
 
  
  smalltree->Branch("tree_Cluster_charge",     tree_Cluster_charge,    "tree_Cluster_charge[tree_track_nclusters]/D"     );
  smalltree->Branch("tree_Cluster_path",       tree_Cluster_path,      "tree_Cluster_path[tree_track_nclusters]/D"       );
  smalltree->Branch("tree_Cluster_tsosx",      tree_Cluster_tsosx,     "tree_Cluster_tsosx[tree_track_nclusters]/D"      );
  smalltree->Branch("tree_Cluster_tsosy",      tree_Cluster_tsosy,     "tree_Cluster_tsosy[tree_track_nclusters]/D"      );
  smalltree->Branch("tree_Cluster_SoverN",     tree_Cluster_SoverN,    "tree_Cluster_SoverN[tree_track_nclusters]/D"     );
  smalltree->Branch("tree_Cluster_noise",      tree_Cluster_noise,     "tree_Cluster_noise[tree_track_nclusters]/D"      );
  smalltree->Branch("tree_Cluster_width",      tree_Cluster_width,      "tree_Cluster_width[tree_track_nclusters]/I"      );
  smalltree->Branch("tree_Cluster_barycenter", tree_Cluster_barycenter, "tree_Cluster_barycenter[tree_track_nclusters]/D" );
  smalltree->Branch("tree_Cluster_detID",      tree_Cluster_detID,      "tree_Cluster_detID[tree_track_nclusters]/I"      );
  
   // cluster position ----
  smalltree->Branch("tree_Cluster_locX",  tree_Cluster_locX,  "tree_Cluster_locX[tree_track_nclusters]/F"  );
  smalltree->Branch("tree_Cluster_locY",  tree_Cluster_locY,  "tree_Cluster_locY[tree_track_nclusters]/F"  );
  smalltree->Branch("tree_Cluster_globX", tree_Cluster_globX, "tree_Cluster_globX[tree_track_nclusters]/F" );
  smalltree->Branch("tree_Cluster_globY", tree_Cluster_globY, "tree_Cluster_globY[tree_track_nclusters]/F" );
  smalltree->Branch("tree_Cluster_globZ", tree_Cluster_globZ, "tree_Cluster_globZ[tree_track_nclusters]/F" );
  smalltree->Branch("tree_Cluster_tsosglobX", tree_Cluster_tsosglobX, "tree_Cluster_tsosglobX[tree_track_nclusters]/F" );
  smalltree->Branch("tree_Cluster_tsosglobY", tree_Cluster_tsosglobY, "tree_Cluster_tsosglobY[tree_track_nclusters]/F" );
  smalltree->Branch("tree_Cluster_tsosglobZ", tree_Cluster_tsosglobZ, "tree_Cluster_tsosglobZ[tree_track_nclusters]/F" );
  smalltree->Branch("tree_Cluster_LocalTracj_X",tree_Cluster_LocalTracj_X, "tree_Cluster_LocalTracj_X[tree_track_nclusters]/F"  );
  smalltree->Branch("tree_Cluster_LocalTracj_Y",tree_Cluster_LocalTracj_Y, "tree_Cluster_LocalTracj_Y[tree_track_nclusters]/F"  );
  smalltree->Branch("tree_Cluster_LocalTracj_Z",tree_Cluster_LocalTracj_Z, "tree_Cluster_LocalTracj_Z[tree_track_nclusters]/F"  );
  
  //-----------------------------
  //then fill information of clusters
  //attached to the tracks
  smalltree->Branch("tree_Strips_nstrip", &tree_Strips_nstrip , "tree_Strips_nstrip/I"                      );
  smalltree->Branch("tree_Strips_idFirst", tree_Strips_idFirst, "tree_Strips_idFirst[tree_track_nclusters]/I" ); 
  smalltree->Branch("tree_Strips_idLast",  tree_Strips_idLast,  "tree_Strips_idLast[tree_track_nclusters]/I"  ); 
  
  // strips infos ----
  smalltree->Branch("tree_Strips_stripCharges",      tree_Strips_stripCharges,      "tree_Strips_stripCharges[tree_Strips_nstrip]/I"      );
  smalltree->Branch("tree_Strips_stripGains",        tree_Strips_stripGains,        "tree_Strips_stripGains[tree_Strips_nstrip]/F"        );
  smalltree->Branch("tree_Strips_stripNoises",       tree_Strips_stripNoises,       "tree_Strips_stripNoises[tree_Strips_nstrip]/F"       );
  smalltree->Branch("tree_Strips_stripQualitiesBad", tree_Strips_stripQualitiesBad, "tree_Strips_stripQualitiesBad[tree_Strips_nstrip]/O" );
  smalltree->Branch("runNumber",&runNumber,"runNumber/I");
  smalltree->Branch("eventNumber",&eventNumber,"eventNumber/I");
  smalltree->Branch("lumiBlock",&lumiBlock,"lumiBlock/I");
 
 //  int runNumber,eventNumber,lumiBlock;
 //
  runNumber = 0;
  eventNumber = 0;
  lumiBlock = 0;
  tree_track_nclusters = 0;
  tree_track_pt = -1;
  tree_track_eta = -1;
  tree_track_phi = -1;
  tree_track_nhits = -1;
  tree_track_NChi2 = -1;
  tree_Strips_nstrip =0;
}


TrackerCluster::~TrackerCluster()
{
  
  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)
  
}


//
// member functions
//

// ------------ method called for each event  ------------
void
TrackerCluster::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{

  using namespace edm;
  using namespace reco;
  using namespace std;


  runNumber = iEvent.id().run();
  edm::LogInfo("TrackCluster") << "runNumber = " << runNumber << std::endl;
  eventNumber = iEvent.id().event();
  lumiBlock = iEvent.luminosityBlock();
 
  //edm::Handle<std::vector<reco::Track> > TracksForRes;
  edm::Handle<  edm::View<reco::Track>  > TracksForRes;
  iEvent.getByToken(trackSrc_, TracksForRes);
  
  edm::ESHandle<TrackerGeometry> TG;
  iSetup.get<TrackerDigiGeometryRecord>().get(TG);
  theTrackerGeometry = TG.product();
   
  edm::ESHandle<TransientTrackBuilder> theB;
  iSetup.get<TransientTrackRecord>().get( "TransientTrackBuilder", theB );
 
  edm::ESHandle<TransientTrackingRecHitBuilder> theTrackerRecHitBuilder;
  iSetup.get<TransientRecHitRecord>().get(ttrhbuilder_,theTrackerRecHitBuilder);
  
  //get tracker geometry
  edm::ESHandle<TrackerGeometry> pDD;
  iSetup.get<TrackerDigiGeometryRecord>().get(pDD);
  
  
  edm::Handle<std::vector<Trajectory> > TrajectoryCollection;
  iEvent.getByToken(trajSrc_, TrajectoryCollection);
  edm::Handle<TrajTrackAssociationCollection> trajTrackAssociationHandle;
  iEvent.getByToken(trajTrackAssociationSrc_, trajTrackAssociationHandle);
 
  edm::ESHandle<StripClusterParameterEstimator> parameterestimator;
  iSetup.get<TkStripCPERecord>().get("StripCPEfromTrackAngle", parameterestimator); 
  const StripClusterParameterEstimator &stripcpe(*parameterestimator);
  
  iSetup.get<IdealMagneticFieldRecord>().get(bField); 

  edm::ESHandle<TrackerTopology> tTopoHandle;
  iSetup.get<TrackerTopologyRcd>().get(tTopoHandle);
  const TrackerTopology* const tTopo = tTopoHandle.product();

  siStripClusterInfo_.initEvent(iSetup);
  
  //  edm::LogInfo("TrackCluster") << "I'm doing some junk" << std::endl;
 
  // Loop on tracks
  for(TrajTrackAssociationCollection::const_iterator it = trajTrackAssociationHandle->begin(); it!=trajTrackAssociationHandle->end(); ++it) {
    reco::TrackRef itTrack  = it->val;
    edm::Ref<std::vector<Trajectory> > itraj  = it->key; // bug to find type of the key
    std::vector<TrajectoryMeasurement> TMeas=itraj->measurements();
    vector<TrajectoryMeasurement>::iterator itm;
    
    tree_track_nclusters = 0;
    tree_Strips_nstrip   = 0;
    tree_track_pt    = itTrack->pt();
    tree_track_eta   = itTrack->eta();
    tree_track_phi   = itTrack->phi();
    tree_track_nhits = itTrack->hitPattern().numberOfValidHits();
    tree_track_NChi2 = itTrack->normalizedChi2();
    //    edm::LogInfo("TrackCluster") << "Found a track" << std::endl;
    
    // Loop on trajectory measurements
    for (itm=TMeas.begin();itm!=TMeas.end();itm++){
      //      edm::LogInfo("TrackCluster") << "Found a traj" << std::endl;
      const TrackingRecHit* hit = &*(*itm).recHit();
      const DetId detid = hit->geographicalId();
      int subDet = detid.subdetId();
      
      const TransientTrackingRecHit::ConstRecHitPointer theTTrechit = (*itm).recHit();
      const SiStripRecHit2D* SiStriphit2D = dynamic_cast<const SiStripRecHit2D*>((*theTTrechit).hit());
      //const SiStripRecHit2D* SiStriphit2D = dynamic_cast<const SiStripRecHit2D*>( theTTrechit->hit());
      const SiStripRecHit1D* SiStriphit1D = dynamic_cast<const SiStripRecHit1D*>((*theTTrechit).hit());
      const SiStripCluster* cluster = 0;
      if (SiStriphit2D!=0){
        cluster = &*(SiStriphit2D->cluster());
      }
      if (SiStriphit1D!=0){
        cluster = &*(SiStriphit1D->cluster());
      }
      
//      SiStripClusterInfo clusterInfo = SiStripClusterInfo( *cluster, iSetup, detid); 
      siStripClusterInfo_.setCluster(*cluster, detid);
      //if(cluster == 0) cout << "no cluster found " << endl;
      if(cluster!=0){
        
        const TrajectoryStateOnSurface tsos = itm->updatedState();
	tree_Cluster_WheelSide[tree_track_nclusters] = 0;
	tree_Cluster_detID[tree_track_nclusters] = detid;
	tree_Cluster_PetalSide[tree_track_nclusters] = 0;
       
        tree_Cluster_LocalTracj_X[tree_track_nclusters] = tsos.localDirection().x();
        tree_Cluster_LocalTracj_Y[tree_track_nclusters] = tsos.localDirection().y();
        tree_Cluster_LocalTracj_Z[tree_track_nclusters] = tsos.localDirection().z();
	
	edm::LogInfo("TrackCluster") << "***************** " << " "
				     << tsos.localDirection().x() << " "
				     << tsos.localDirection().y() << " "
				     << tsos.localDirection().z() << " "
				     << tree_Cluster_LocalTracj_X[tree_track_nclusters] << " "
				     << tree_Cluster_LocalTracj_Y[tree_track_nclusters] << " "
				     << tree_Cluster_LocalTracj_Z[tree_track_nclusters] << " " << std::endl;
       
	double cosine = tsos.localDirection().z()/tsos.localDirection().mag();
	tree_Cluster_path[tree_track_nclusters]	= (10.0*thickness(detid))/fabs(cosine);

	//determine subdte id
	if(subDet == SiStripDetId::TIB){
	  tree_Cluster_subDet[tree_track_nclusters] = 0;
	  tree_Cluster_LayerNbr[tree_track_nclusters] = tTopo->tobLayer(detid.rawId());
	} 
	if(subDet == SiStripDetId::TOB){
	  tree_Cluster_subDet[tree_track_nclusters] = 1;
	  tree_Cluster_LayerNbr[tree_track_nclusters] =tTopo->tibLayer(detid.rawId());
	} 
	if(subDet == SiStripDetId::TID){
	  tree_Cluster_subDet[tree_track_nclusters] = 2;
	  tree_Cluster_WheelSide[tree_track_nclusters] =tTopo->tidSide(detid.rawId());
	  tree_Cluster_LayerNbr[tree_track_nclusters] =tTopo->tidWheel(detid.rawId());
	} 
	if(subDet == SiStripDetId::TEC){
	  tree_Cluster_subDet[tree_track_nclusters] = 3; 
	  tree_Cluster_WheelSide[tree_track_nclusters] = tTopo->tecSide(detid.rawId());
	  tree_Cluster_LayerNbr[tree_track_nclusters] =tTopo->tecWheel(detid.rawId());
	  if(tTopo->tecIsFrontPetal(detid.rawId()))  tree_Cluster_PetalSide[tree_track_nclusters] = 1;
	  else                                       tree_Cluster_PetalSide[tree_track_nclusters] = -1;
	}

	tree_Cluster_tsosx[tree_track_nclusters]        = tsos.localPosition().x();
        tree_Cluster_tsosy[tree_track_nclusters]        = tsos.localPosition().y();
        tree_Cluster_SoverN[tree_track_nclusters]       = siStripClusterInfo_.signalOverNoise();
	tree_Cluster_noise[tree_track_nclusters]        = siStripClusterInfo_.noiseRescaledByGain();
	tree_Cluster_charge[tree_track_nclusters]       = siStripClusterInfo_.charge();
	tree_Cluster_width[tree_track_nclusters]        = cluster->amplitudes().size();
	tree_Cluster_barycenter[tree_track_nclusters]   = cluster->barycenter();
	
	tree_Cluster_tsosglobX[tree_track_nclusters] = tsos.globalPosition().x();
        tree_Cluster_tsosglobY[tree_track_nclusters] = tsos.globalPosition().y();
        tree_Cluster_tsosglobZ[tree_track_nclusters] = tsos.globalPosition().z();
	
	 // cluster position ----
	DetId clusterDetId(detid);
    	const StripGeomDetUnit * stripdet = (const StripGeomDetUnit*) theTrackerGeometry->idToDetUnit(clusterDetId);
    	StripClusterParameterEstimator::LocalValues parameters=stripcpe.localParameters(*cluster, *stripdet);
    	
	LocalPoint lp = parameters.first;
	LocalVector lbfield=(stripdet->surface()).toLocal(bField->inTesla(stripdet->surface().position()));
	
	tree_Cluster_locX[tree_track_nclusters]  = lp.x();
        tree_Cluster_locY[tree_track_nclusters]  = lbfield.y();
	tree_Cluster_globX[tree_track_nclusters] = theTTrechit->globalPosition().x();
        tree_Cluster_globY[tree_track_nclusters] = theTTrechit->globalPosition().y();
        tree_Cluster_globZ[tree_track_nclusters] = theTTrechit->globalPosition().z();
  
        
	// strips infos ----
	auto                       stripCharges = siStripClusterInfo_.stripCharges();
	std::vector<float>         stripGains = siStripClusterInfo_.stripGains();
	std::vector<float>         stripNoises = siStripClusterInfo_.stripNoises();
	std::vector<bool>          stripQualitiesBad = siStripClusterInfo_.stripQualitiesBad();
	
	tree_Strips_idFirst[tree_track_nclusters] = tree_Strips_nstrip;
	
	for(unsigned int istrip=0; istrip < stripGains.size(); istrip++){
          tree_Strips_stripCharges[tree_Strips_nstrip]      = stripCharges[istrip];
	  tree_Strips_stripGains[tree_Strips_nstrip]        = stripGains[istrip];
          tree_Strips_stripNoises[tree_Strips_nstrip]       = stripNoises[istrip];
          tree_Strips_stripQualitiesBad[tree_Strips_nstrip] = stripQualitiesBad[istrip];
	  tree_Strips_nstrip++;
	}
        tree_Strips_idLast[tree_track_nclusters] = tree_Strips_nstrip;
		
        tree_track_nclusters++;
      }//end if cluster
     
    }//loop on clusters
     smalltree->Fill();
  }//end loop on tracks

}

// ------------ method to get the detector thickness ------------
//****************************************************************/
double 
TrackerCluster::thickness(DetId id)
//****************************************************************/
{
  std::map<DetId,double>::iterator th=m_thicknessMap.find(id);
  if(th!=m_thicknessMap.end())
    return (*th).second;
  else {
    double detThickness=1.;
    //compute thickness normalization
    const GeomDetUnit* it = theTrackerGeometry->idToDetUnit(DetId(id));
    bool isPixel = dynamic_cast<const PixelGeomDetUnit*>(it)!=0;
    bool isStrip = dynamic_cast<const StripGeomDetUnit*>(it)!=0;
    if (!isPixel && ! isStrip) {
      //FIXME throw exception
      edm::LogWarning("DeDxHitsProducer") << "\t\t this detID doesn't seem to belong to the Tracker";
      detThickness = 1.;
    }else{
      detThickness = it->surface().bounds().thickness();
    }
    
    m_thicknessMap[id]=detThickness;//computed value
    return detThickness;
  }
}


// ------------ method called once each job just before starting event loop  ------------
void 
TrackerCluster::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
TrackerCluster::endJob() 
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
TrackerCluster::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(TrackerCluster);
