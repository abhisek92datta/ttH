#include "MiniAOD/MiniAODHelper/interface/LeptonSFHelper.h"

//PUBLIC
LeptonSFHelper::LeptonSFHelper( ){

  //std::cout << "Initializing Lepton scale factors" << std::endl;

  SetElectronHistos( );
  SetMuonHistos( );
  SetElectronElectronHistos( );
  SetMuonMuonHistos( );
  SetElectronMuonHistos( );

  electronMaxPt = 149.99;
  muonMaxPt = 119.99;
  electronMaxPt_High = 200.01;
  muonMaxPt_High = 499.99;

}

LeptonSFHelper::~LeptonSFHelper( ){

}

std::map< std::string, float >  LeptonSFHelper::GetLeptonSF( const std::vector< pat::Electron >& Electrons,
							     const std::vector< pat::Muon >& Muons  ) {


  std::map< std::string , float > ScaleFactorMap;

  float ElectronIDSF = 1.0;
  float ElectronIDSF_Up = 1.0;
  float ElectronIDSF_Down = 1.0;
  float ElectronIsoSF = 1.0;
  float ElectronIsoSF_Up = 1.0;
  float ElectronIsoSF_Down = 1.0;
  float ElectronTriggerSF = 1.0;
  float ElectronTriggerSF_Up = 1.0;
  float ElectronTriggerSF_Down = 1.0;
  float MuonIDSF = 1.0;
  float MuonIDSF_Up = 1.0;
  float MuonIDSF_Down = 1.0;
  float MuonIsoSF = 1.0;
  float MuonIsoSF_Up = 1.0;
  float MuonIsoSF_Down = 1.0;
  float MuonTriggerSF = 1.0;
  float MuonTriggerSF_Up = 1.0;
  float MuonTriggerSF_Down = 1.0;
  float ElectronElectronTriggerSF = 1.0;
  float MuonMuonTriggerSF = 1.0;
  float ElectronMuonTriggerSF = 1.0;


  for (auto Electron: Electrons){ //Electron is of type pat::Electron

    ElectronIDSF = ElectronIDSF * GetElectronSF(Electron.pt(), Electron.superCluster()->eta(), 0, "ID");
    ElectronIDSF_Up = ElectronIDSF_Up *GetElectronSF(Electron.pt(), Electron.superCluster()->eta(), 1, "ID");
    ElectronIDSF_Down = ElectronIDSF_Down * GetElectronSF(Electron.pt(), Electron.superCluster()->eta(), -1, "ID");

    ElectronIsoSF = ElectronIsoSF * GetElectronSF(Electron.pt(), Electron.superCluster()->eta(), 0, "Iso");
    ElectronIsoSF_Up = ElectronIsoSF_Up  * GetElectronSF(Electron.pt(), Electron.superCluster()->eta(), 1, "Iso");
    ElectronIsoSF_Down = ElectronIsoSF_Down * GetElectronSF(Electron.pt(), Electron.superCluster()->eta(), -1, "Iso");

    ElectronTriggerSF = ElectronTriggerSF * GetElectronSF(Electron.pt(), Electron.superCluster()->eta(), 0, "Trigger");
    ElectronTriggerSF_Up = ElectronTriggerSF_Up  * GetElectronSF(Electron.pt(), Electron.superCluster()->eta(), 1, "Trigger");
    ElectronTriggerSF_Down = ElectronTriggerSF_Down * GetElectronSF(Electron.pt(), Electron.superCluster()->eta(), -1, "Trigger");

  } for (auto Muon: Muons){ //Muon is of type pat::Muon

    MuonIDSF = MuonIDSF * GetMuonSF(Muon.pt(), Muon.eta(), 0, "ID");
    MuonIDSF_Up = MuonIDSF_Up * GetMuonSF(Muon.pt(), Muon.eta(), 1, "ID");
    MuonIDSF_Down = MuonIDSF_Down * GetMuonSF(Muon.pt(), Muon.eta(), -1, "ID");

    MuonIsoSF = MuonIsoSF * GetMuonSF(Muon.pt(), Muon.eta(), 0, "Iso");
    MuonIsoSF_Up = MuonIsoSF_Up  * GetMuonSF(Muon.pt(), Muon.eta(), 1, "Iso");
    MuonIsoSF_Down = MuonIsoSF_Down * GetMuonSF(Muon.pt(), Muon.eta(), -1, "Iso");

    MuonTriggerSF = MuonTriggerSF * GetMuonSF(Muon.pt(), Muon.eta(), 0, "Trigger");
    MuonTriggerSF_Up = MuonTriggerSF_Up  * GetMuonSF(Muon.pt(), Muon.eta(), 1, "Trigger");
    MuonTriggerSF_Down = MuonTriggerSF_Down * GetMuonSF(Muon.pt(), Muon.eta(), -1, "Trigger");

  }

  //std::cout << "Anzahl El plus Mu " << Electrons.size()+Muons.size() << std::endl;

  if(Electrons.size()+Muons.size()==2) {
    if(Electrons.size()==2) {

	//std::cout << "zwei Elektronen ! " << std::endl;
	ElectronElectronTriggerSF = ElectronElectronTriggerSF * GetElectronElectronSF(Electrons.at(0).eta(), Electrons.at(1).eta(), 0, "Trigger");


    }
    else if(Muons.size()==2) {

	//std::cout << "zwei Muonen ! " << std::endl;
	MuonMuonTriggerSF = MuonMuonTriggerSF * GetMuonMuonSF(Muons.at(0).eta(), Muons.at(1).eta(), 0, "Trigger");


    }
    else {

	//std::cout << "ein Ele und ein Mu ! " << std::endl;
	ElectronMuonTriggerSF = ElectronMuonTriggerSF * GetElectronMuonSF(Electrons.at(0).eta(), Muons.at(0).eta(), 0, "Trigger");


    }
  }

  //std::cout << ElectronElectronTriggerSF << "  " << MuonMuonTriggerSF << "  " << ElectronMuonTriggerSF << std::endl;

  ScaleFactorMap["ElectronSFID"] = ElectronIDSF;
  ScaleFactorMap["ElectronSFID_Up"] = ElectronIDSF_Up;
  ScaleFactorMap["ElectronSFID_Down"] = ElectronIDSF_Down;
  ScaleFactorMap["ElectronSFIso"] = ElectronIsoSF;
  ScaleFactorMap["ElectronSFIso_Up"] = ElectronIsoSF_Up;
  ScaleFactorMap["ElectronSFIso_Down"] = ElectronIsoSF_Down;
  ScaleFactorMap["ElectronSFTrigger"] = ElectronTriggerSF;
  ScaleFactorMap["ElectronSFTrigger_Up"] = ElectronTriggerSF_Up;
  ScaleFactorMap["ElectronSFTrigger_Down"] = ElectronTriggerSF_Down;
  ScaleFactorMap["ElectronElectronTriggerSF"] =ElectronElectronTriggerSF;

  ScaleFactorMap["MuonSFID"] = MuonIDSF;
  ScaleFactorMap["MuonSFID_Up"] = MuonIDSF_Up;
  ScaleFactorMap["MuonSFID_Down"] = MuonIDSF_Down;
  ScaleFactorMap["MuonSFIso"] = MuonIsoSF;
  ScaleFactorMap["MuonSFIso_Up"] = MuonIsoSF_Up;
  ScaleFactorMap["MuonSFIso_Down"] = MuonIsoSF_Down;
  ScaleFactorMap["MuonSFTrigger"] = MuonTriggerSF;
  ScaleFactorMap["MuonSFTrigger_Up"] = MuonTriggerSF_Up;
  ScaleFactorMap["MuonSFTrigger_Down"] = MuonTriggerSF_Down;
  ScaleFactorMap["MuonMuonTriggerSF"] = MuonMuonTriggerSF;

  ScaleFactorMap["ElectronMuonTriggerSF"] = ElectronMuonTriggerSF;

  ScaleFactorMap["ElectronSF"]= ElectronIDSF * ElectronIsoSF * ElectronTriggerSF;
  ScaleFactorMap["ElectronSF_Up"]= ElectronIDSF_Up * ElectronIsoSF_Up * ElectronTriggerSF_Up;
  ScaleFactorMap["ElectronSF_Down"]= ElectronIDSF_Down * ElectronIsoSF_Down * ElectronTriggerSF_Down;

  ScaleFactorMap["MuonSF"]= MuonIDSF * MuonIsoSF * MuonTriggerSF;
  ScaleFactorMap["MuonSF_Up"]= MuonIDSF_Up * MuonIsoSF_Up * MuonTriggerSF_Up;
  ScaleFactorMap["MuonSF_Down"]= MuonIDSF_Down * MuonIsoSF_Down * MuonTriggerSF_Down;

  ScaleFactorMap["LeptonSF"]= ScaleFactorMap["ElectronSF"] * ScaleFactorMap["MuonSF"];
  ScaleFactorMap["LeptonSF_Up"]= ScaleFactorMap["ElectronSF_Up"] * ScaleFactorMap["MuonSF_Up"];
  ScaleFactorMap["LeptonSF_Down"]= ScaleFactorMap["ElectronSF_Down"] * ScaleFactorMap["MuonSF_Down"];

  return ScaleFactorMap;
}
float LeptonSFHelper::GetElectronSF(  float electronPt , float electronEta , int syst , std::string type  ) {
  if ( electronPt == 0.0 ){ return 1.0; }

  int thisBin=0;

  float searchEta=electronEta;
  float searchPt=TMath::Min( electronPt , electronMaxPt );

  float nomval = 0;
  float error = 0;
  float upval = 0;
  float downval= 0;

	if ( type == "ID_BCDEF" ){

		thisBin = h_ele_ID_BCDEF_abseta_pt_ratio->FindBin( searchEta , searchPt );
		nomval=h_ele_ID_BCDEF_abseta_pt_ratio->GetBinContent( thisBin );
		error=h_ele_ID_BCDEF_abseta_pt_ratio->GetBinError( thisBin );
		if(nomval==0) {
			thisBin = h_ele_ID_BCDEF_abseta_pt_ratio->FindBin( searchEta , 10.001 );
			nomval=h_ele_ID_BCDEF_abseta_pt_ratio->GetBinContent( thisBin );
			error=h_ele_ID_BCDEF_abseta_pt_ratio->GetBinError( thisBin );
		}
		upval=nomval+error;
		downval=nomval-error;
	}

	else if ( type == "ID_B" ){

		thisBin = h_ele_ID_B_abseta_pt_ratio->FindBin( searchEta , searchPt );
		nomval=h_ele_ID_B_abseta_pt_ratio->GetBinContent( thisBin );
		error=h_ele_ID_B_abseta_pt_ratio->GetBinError( thisBin );
		if(nomval==0) {
			thisBin = h_ele_ID_B_abseta_pt_ratio->FindBin( searchEta , 10.001 );
			nomval=h_ele_ID_B_abseta_pt_ratio->GetBinContent( thisBin );
			error=h_ele_ID_B_abseta_pt_ratio->GetBinError( thisBin );
		}
		upval=nomval+error;
		downval=nomval-error;
	}

	else if ( type == "ID_C" ){

		thisBin = h_ele_ID_C_abseta_pt_ratio->FindBin( searchEta , searchPt );
		nomval=h_ele_ID_C_abseta_pt_ratio->GetBinContent( thisBin );
		error=h_ele_ID_C_abseta_pt_ratio->GetBinError( thisBin );
		upval=nomval+error;
		downval=nomval-error;
		if(nomval==0) {
			thisBin = h_ele_ID_C_abseta_pt_ratio->FindBin( searchEta , 10.001 );
			nomval=h_ele_ID_C_abseta_pt_ratio->GetBinContent( thisBin );
			error=h_ele_ID_C_abseta_pt_ratio->GetBinError( thisBin );
		}
		upval=nomval+error;
		downval=nomval-error;
	}

	else if ( type == "ID_D" ){

		thisBin = h_ele_ID_D_abseta_pt_ratio->FindBin( searchEta , searchPt );
		nomval=h_ele_ID_D_abseta_pt_ratio->GetBinContent( thisBin );
		error=h_ele_ID_D_abseta_pt_ratio->GetBinError( thisBin );
		if(nomval==0) {
			thisBin = h_ele_ID_D_abseta_pt_ratio->FindBin( searchEta , 10.001 );
			nomval=h_ele_ID_D_abseta_pt_ratio->GetBinContent( thisBin );
			error=h_ele_ID_D_abseta_pt_ratio->GetBinError( thisBin );
		}
		upval=nomval+error;
		downval=nomval-error;
	}

	else if ( type == "ID_E" ){

		thisBin = h_ele_ID_E_abseta_pt_ratio->FindBin( searchEta , searchPt );
		nomval=h_ele_ID_E_abseta_pt_ratio->GetBinContent( thisBin );
		error=h_ele_ID_E_abseta_pt_ratio->GetBinError( thisBin );
		if(nomval==0) {
			thisBin = h_ele_ID_E_abseta_pt_ratio->FindBin( searchEta , 10.001 );
			nomval=h_ele_ID_E_abseta_pt_ratio->GetBinContent( thisBin );
			error=h_ele_ID_E_abseta_pt_ratio->GetBinError( thisBin );
		}
		upval=nomval+error;
		downval=nomval-error;
	}

	else if ( type == "ID_F" ){

		thisBin = h_ele_ID_F_abseta_pt_ratio->FindBin( searchEta , searchPt );
		nomval=h_ele_ID_F_abseta_pt_ratio->GetBinContent( thisBin );
		error=h_ele_ID_F_abseta_pt_ratio->GetBinError( thisBin );
		if(nomval==0) {
			thisBin = h_ele_ID_F_abseta_pt_ratio->FindBin( searchEta , 10.001 );
			nomval=h_ele_ID_F_abseta_pt_ratio->GetBinContent( thisBin );
			error=h_ele_ID_F_abseta_pt_ratio->GetBinError( thisBin );
		}
		upval=nomval+error;
		downval=nomval-error;
	}

  /*
  else if ( type == "Trigger" ){

	searchPt=TMath::Min( electronPt , electronMaxPt_High );

    thisBin = h_ele_TRIGGER_abseta_pt_ratio->FindBin( searchPt, searchEta );
    nomval=h_ele_TRIGGER_abseta_pt_ratio->GetBinContent( thisBin );
    error=h_ele_TRIGGER_abseta_pt_ratio->GetBinError( thisBin );
    upval=nomval+error;
    downval=nomval-error;
    
    if(nomval==0) {
    	thisBin = h_ele_TRIGGER_abseta_pt_ratio->FindBin( 25.001, searchEta );
    	nomval=h_ele_TRIGGER_abseta_pt_ratio->GetBinContent( thisBin );
    }

  }
  */
	else if ( type == "Iso_BCDEF" ){

		if(searchPt>20){
			thisBin = h_ele_ISO_BCDEF_abseta_pt_ratio->FindBin( searchEta , searchPt );
			nomval=h_ele_ISO_BCDEF_abseta_pt_ratio->GetBinContent( thisBin );
			error=h_ele_ISO_BCDEF_abseta_pt_ratio->GetBinError( thisBin );
			if(nomval==0) {
				thisBin = h_ele_ISO_BCDEF_abseta_pt_ratio->FindBin( searchEta , 20.001 );
				nomval=h_ele_ISO_BCDEF_abseta_pt_ratio->GetBinContent( thisBin );
				error=h_ele_ISO_BCDEF_abseta_pt_ratio->GetBinError( thisBin );
			}
			upval=nomval+error;
			downval=nomval-error;
		}
		else{
			thisBin = h_ele_ISO_BCDEF_lowEt_abseta_pt_ratio->FindBin( searchEta , searchPt );
			nomval=h_ele_ISO_BCDEF_lowEt_abseta_pt_ratio->GetBinContent( thisBin );
			error=h_ele_ISO_BCDEF_lowEt_abseta_pt_ratio->GetBinError( thisBin );
			if(nomval==0) {
				thisBin = h_ele_ISO_BCDEF_lowEt_abseta_pt_ratio->FindBin( searchEta , 10.001 );
				nomval=h_ele_ISO_BCDEF_lowEt_abseta_pt_ratio->GetBinContent( thisBin );
				error=h_ele_ISO_BCDEF_lowEt_abseta_pt_ratio->GetBinError( thisBin );
			}
			upval=nomval+error;
			downval=nomval-error;
		}
	}

	else if ( type == "Iso_B" ){

		if(searchPt>20){
			thisBin = h_ele_ISO_B_abseta_pt_ratio->FindBin( searchEta , searchPt );
			nomval=h_ele_ISO_B_abseta_pt_ratio->GetBinContent( thisBin );
			error=h_ele_ISO_B_abseta_pt_ratio->GetBinError( thisBin );
			if(nomval==0) {
				thisBin = h_ele_ISO_B_abseta_pt_ratio->FindBin( searchEta , 20.001 );
				nomval=h_ele_ISO_B_abseta_pt_ratio->GetBinContent( thisBin );
				error=h_ele_ISO_B_abseta_pt_ratio->GetBinError( thisBin );
			}
			upval=nomval+error;
			downval=nomval-error;
		}
		else{
			nomval=1;
			error=0;
			upval=nomval+error;
			downval=nomval-error;
		}
	}

	else if ( type == "Iso_C" ){

		if(searchPt>20){
			thisBin = h_ele_ISO_C_abseta_pt_ratio->FindBin( searchEta , searchPt );
			nomval=h_ele_ISO_C_abseta_pt_ratio->GetBinContent( thisBin );
			error=h_ele_ISO_C_abseta_pt_ratio->GetBinError( thisBin );
			if(nomval==0) {
				thisBin = h_ele_ISO_C_abseta_pt_ratio->FindBin( searchEta , 20.001 );
				nomval=h_ele_ISO_C_abseta_pt_ratio->GetBinContent( thisBin );
				error=h_ele_ISO_C_abseta_pt_ratio->GetBinError( thisBin );
			}
			upval=nomval+error;
			downval=nomval-error;
		}
		else{
			nomval=1;
			error=0;
			upval=nomval+error;
			downval=nomval-error;
		}
	}

	else if ( type == "Iso_D" ){

		if(searchPt>20){
			thisBin = h_ele_ISO_D_abseta_pt_ratio->FindBin( searchEta , searchPt );
			nomval=h_ele_ISO_D_abseta_pt_ratio->GetBinContent( thisBin );
			error=h_ele_ISO_D_abseta_pt_ratio->GetBinError( thisBin );
			if(nomval==0) {
				thisBin = h_ele_ISO_D_abseta_pt_ratio->FindBin( searchEta , 20.001 );
				nomval=h_ele_ISO_D_abseta_pt_ratio->GetBinContent( thisBin );
				error=h_ele_ISO_D_abseta_pt_ratio->GetBinError( thisBin );
			}
			upval=nomval+error;
			downval=nomval-error;
		}
		else{
			nomval=1;
			error=0;
			upval=nomval+error;
			downval=nomval-error;
		}
	}

	else if ( type == "Iso_E" ){

		if(searchPt>20){
			thisBin = h_ele_ISO_E_abseta_pt_ratio->FindBin( searchEta , searchPt );
			nomval=h_ele_ISO_E_abseta_pt_ratio->GetBinContent( thisBin );
			error=h_ele_ISO_E_abseta_pt_ratio->GetBinError( thisBin );
			if(nomval==0) {
				thisBin = h_ele_ISO_E_abseta_pt_ratio->FindBin( searchEta , 20.001 );
				nomval=h_ele_ISO_E_abseta_pt_ratio->GetBinContent( thisBin );
				error=h_ele_ISO_E_abseta_pt_ratio->GetBinError( thisBin );
			}
			upval=nomval+error;
			downval=nomval-error;
		}
		else{
			nomval=1;
			error=0;
			upval=nomval+error;
			downval=nomval-error;
		}
	}

	else if ( type == "Iso_F" ){

		if(searchPt>20){
			thisBin = h_ele_ISO_F_abseta_pt_ratio->FindBin( searchEta , searchPt );
			nomval=h_ele_ISO_F_abseta_pt_ratio->GetBinContent( thisBin );
			error=h_ele_ISO_F_abseta_pt_ratio->GetBinError( thisBin );
			if(nomval==0) {
				thisBin = h_ele_ISO_F_abseta_pt_ratio->FindBin( searchEta , 20.001 );
				nomval=h_ele_ISO_F_abseta_pt_ratio->GetBinContent( thisBin );
				error=h_ele_ISO_F_abseta_pt_ratio->GetBinError( thisBin );
			}
			upval=nomval+error;
			downval=nomval-error;
		}
		else{
			nomval=1;
			error=0;
			upval=nomval+error;
			downval=nomval-error;
		}
	}

  else {

    std::cout << "Unknown Type. Supported Types are: ID, Trigger, Iso" << std::endl;
    nomval = -1;
    upval = -1;
    downval= -1;

  }

  if ( syst==-1 ){ return downval; }
  else if ( syst==1 ){ return upval; }
  else { return nomval; }

}

float LeptonSFHelper::GetMuonSF(  float muonPt , float muonEta , int syst , std::string type  ){
  if ( muonPt == 0.0 ){ return 1.0; }

  int thisBin=0;

  float searchEta=fabs( muonEta );
  float searchPt=TMath::Min( muonPt , muonMaxPt );

  float nomval = 0;
  float error = 0;
  float upval = 0;
  float downval= 0;

	if ( type == "ID_BCDEF" ){

		thisBin = h_mu_ID_BCDEF_abseta_pt_ratio->FindBin( searchPt, searchEta );
		nomval=h_mu_ID_BCDEF_abseta_pt_ratio->GetBinContent( thisBin );
		error=h_mu_ID_BCDEF_abseta_pt_ratio->GetBinError( thisBin );
		if(nomval==0) {
			thisBin = h_mu_ID_BCDEF_abseta_pt_ratio->FindBin( 20.001, searchEta );
			nomval=h_mu_ID_BCDEF_abseta_pt_ratio->GetBinContent( thisBin );
			error=h_mu_ID_BCDEF_abseta_pt_ratio->GetBinError( thisBin );
		}
		upval=( nomval+error );
		downval=( nomval-error );
	}

	else if ( type == "ID_BC" ){

		thisBin = h_mu_ID_BC_abseta_pt_ratio->FindBin( searchPt, searchEta );
		nomval=h_mu_ID_BC_abseta_pt_ratio->GetBinContent( thisBin );
		error=h_mu_ID_BC_abseta_pt_ratio->GetBinError( thisBin );
		if(nomval==0) {
			thisBin = h_mu_ID_BC_abseta_pt_ratio->FindBin( 20.001, searchEta );
			nomval=h_mu_ID_BC_abseta_pt_ratio->GetBinContent( thisBin );
			error=h_mu_ID_BC_abseta_pt_ratio->GetBinError( thisBin );
		}
		upval=( nomval+error );
		downval=( nomval-error );
	}

	else if ( type == "ID_DE" ){

		thisBin = h_mu_ID_DE_abseta_pt_ratio->FindBin( searchPt, searchEta );
		nomval=h_mu_ID_DE_abseta_pt_ratio->GetBinContent( thisBin );
		error=h_mu_ID_DE_abseta_pt_ratio->GetBinError( thisBin );
		if(nomval==0) {
			thisBin = h_mu_ID_DE_abseta_pt_ratio->FindBin( 20.001, searchEta );
			nomval=h_mu_ID_DE_abseta_pt_ratio->GetBinContent( thisBin );
			error=h_mu_ID_DE_abseta_pt_ratio->GetBinError( thisBin );
		}
		upval=( nomval+error );
		downval=( nomval-error );
	}

	else if ( type == "ID_F" ){

		thisBin = h_mu_ID_F_abseta_pt_ratio->FindBin( searchPt, searchEta );
		nomval=h_mu_ID_F_abseta_pt_ratio->GetBinContent( thisBin );
		error=h_mu_ID_F_abseta_pt_ratio->GetBinError( thisBin );
		if(nomval==0) {
			thisBin = h_mu_ID_F_abseta_pt_ratio->FindBin( 20.001, searchEta );
			nomval=h_mu_ID_F_abseta_pt_ratio->GetBinContent( thisBin );
			error=h_mu_ID_F_abseta_pt_ratio->GetBinError( thisBin );
		}
		upval=( nomval+error );
		downval=( nomval-error );
	}

  /*
  else if ( type == "Trigger_BF" ){

    //float mult4p2 = 0.2834;
    //float mult4p3 = 0.7166;
    //float mult4p2 = 0.0482;
    //float mult4p3 = 0.9518;
	
	searchPt=TMath::Min( muonPt , muonMaxPt_High );

    thisBin = h_mu_TRIGGER_BF_abseta_pt_ratio->FindBin( searchPt, searchEta );
    nomval=h_mu_TRIGGER_BF_abseta_pt_ratio->GetBinContent(thisBin);
    error=h_mu_TRIGGER_BF_abseta_pt_ratio->GetBinError(thisBin);
    upval=nomval+error;
    downval=nomval-error;
    
    //float nomval4p3=h_mu_TRIGGER_abseta_pt_ratio4p3->GetBinContent(thisBin);
    //float error4p3=h_mu_TRIGGER_abseta_pt_ratio4p3->GetBinError(thisBin);
    //float upval4p3=nomval4p3+error4p3;
    //float downval4p3=nomval4p3-error4p3;
    //thisBin = h_mu_TRIGGER_abseta_pt_ratio4p2->FindBin(searchEta,searchPt);
    //float nomval4p2=h_mu_TRIGGER_abseta_pt_ratio4p2->GetBinContent(thisBin);
    //float error4p2=h_mu_TRIGGER_abseta_pt_ratio4p2->GetBinError(thisBin);
    //float upval4p2=nomval4p2+error4p2;
    //float downval4p2=nomval4p2-error4p2;
    //nomval = mult4p2*nomval4p2 + mult4p3*nomval4p3;
    //upval = mult4p2*upval4p2 + mult4p3*upval4p3;
    //downval = mult4p2*downval4p2 + mult4p3*downval4p3;
    //upval=upval*(1.0+0.005);
    //downval=downval*(1.0-0.005);
    
    if(nomval==0) {
    	thisBin = h_mu_TRIGGER_BF_abseta_pt_ratio->FindBin( 25.001, searchEta );
    	nomval=h_mu_TRIGGER_BF_abseta_pt_ratio->GetBinContent( thisBin );
    }

  }

  else if ( type == "Trigger_GH" ){

      //float mult4p2 = 0.2834;
      //float mult4p3 = 0.7166;
      //float mult4p2 = 0.0482;
      //float mult4p3 = 0.9518;

      searchPt=TMath::Min( muonPt , muonMaxPt_High );

      thisBin = h_mu_TRIGGER_GH_abseta_pt_ratio->FindBin( searchPt, searchEta );
      nomval=h_mu_TRIGGER_GH_abseta_pt_ratio->GetBinContent(thisBin);
      error=h_mu_TRIGGER_GH_abseta_pt_ratio->GetBinError(thisBin);
      upval=nomval+error;
      downval=nomval-error;

      //float nomval4p3=h_mu_TRIGGER_abseta_pt_ratio4p3->GetBinContent(thisBin);
      //float error4p3=h_mu_TRIGGER_abseta_pt_ratio4p3->GetBinError(thisBin);
      //float upval4p3=nomval4p3+error4p3;
      //float downval4p3=nomval4p3-error4p3;
      //thisBin = h_mu_TRIGGER_abseta_pt_ratio4p2->FindBin(searchEta,searchPt);
      //float nomval4p2=h_mu_TRIGGER_abseta_pt_ratio4p2->GetBinContent(thisBin);
      //float error4p2=h_mu_TRIGGER_abseta_pt_ratio4p2->GetBinError(thisBin);
      //float upval4p2=nomval4p2+error4p2;
      //float downval4p2=nomval4p2-error4p2;
      //nomval = mult4p2*nomval4p2 + mult4p3*nomval4p3;
      //upval = mult4p2*upval4p2 + mult4p3*upval4p3;
      //downval = mult4p2*downval4p2 + mult4p3*downval4p3;
      //upval=upval*(1.0+0.005);
      //downval=downval*(1.0-0.005);

      if(nomval==0) {
          thisBin = h_mu_TRIGGER_GH_abseta_pt_ratio->FindBin( 25.001, searchEta );
          nomval=h_mu_TRIGGER_GH_abseta_pt_ratio->GetBinContent( thisBin );
      }
      
  }
  */

	else if ( type == "Iso_BCDEF" ){

		thisBin = h_mu_ISO_BCDEF_abseta_pt_ratio->FindBin( searchPt, searchEta );
		nomval=h_mu_ISO_BCDEF_abseta_pt_ratio->GetBinContent( thisBin );
		error=h_mu_ISO_BCDEF_abseta_pt_ratio->GetBinError( thisBin );
		if(nomval==0) {
			thisBin = h_mu_ISO_BCDEF_abseta_pt_ratio->FindBin( 20.001, searchEta );
			nomval=h_mu_ISO_BCDEF_abseta_pt_ratio->GetBinContent( thisBin );
			error=h_mu_ISO_BCDEF_abseta_pt_ratio->GetBinError( thisBin );
		}
		upval=( nomval+error );
		downval=( nomval-error );
	}

	else if ( type == "Iso_BC" ){

		thisBin = h_mu_ISO_BC_abseta_pt_ratio->FindBin( searchPt, searchEta );
		nomval=h_mu_ISO_BC_abseta_pt_ratio->GetBinContent( thisBin );
		error=h_mu_ISO_BC_abseta_pt_ratio->GetBinError( thisBin );
		if(nomval==0) {
			thisBin = h_mu_ISO_BC_abseta_pt_ratio->FindBin( 20.001, searchEta );
			nomval=h_mu_ISO_BC_abseta_pt_ratio->GetBinContent( thisBin );
			error=h_mu_ISO_BC_abseta_pt_ratio->GetBinError( thisBin );
		}
		upval=( nomval+error );
		downval=( nomval-error );
	}

	else if ( type == "Iso_DE" ){

		thisBin = h_mu_ISO_DE_abseta_pt_ratio->FindBin( searchPt, searchEta );
		nomval=h_mu_ISO_DE_abseta_pt_ratio->GetBinContent( thisBin );
		error=h_mu_ISO_DE_abseta_pt_ratio->GetBinError( thisBin );
		if(nomval==0) {
			thisBin = h_mu_ISO_DE_abseta_pt_ratio->FindBin( 20.001, searchEta );
			nomval=h_mu_ISO_DE_abseta_pt_ratio->GetBinContent( thisBin );
			error=h_mu_ISO_DE_abseta_pt_ratio->GetBinError( thisBin );
		}
		upval=( nomval+error );
		downval=( nomval-error );
	}

	else if ( type == "Iso_F" ){

		thisBin = h_mu_ISO_F_abseta_pt_ratio->FindBin( searchPt, searchEta );
		nomval=h_mu_ISO_F_abseta_pt_ratio->GetBinContent( thisBin );
		error=h_mu_ISO_F_abseta_pt_ratio->GetBinError( thisBin );
		if(nomval==0) {
			thisBin = h_mu_ISO_F_abseta_pt_ratio->FindBin( 20.001, searchEta );
			nomval=h_mu_ISO_F_abseta_pt_ratio->GetBinContent( thisBin );
			error=h_mu_ISO_F_abseta_pt_ratio->GetBinError( thisBin );
		}
		upval=( nomval+error );
		downval=( nomval-error );
	}

	/*
	else if ( type == "Tracking_BCDEF" ){

		double x, y;
		double l,r;
		int index = -1;
		for(int i=0; i<h_mu_Tracking_BCDEF_abseta_ratio->GetN(); i++){
			h_mu_Tracking_BCDEF_abseta_ratio->GetPoint(i,x,y);
			l = x - h_mu_Tracking_BCDEF_abseta_ratio->GetErrorXlow(i);
			r = x + h_mu_Tracking_BCDEF_abseta_ratio->GetErrorXhigh(i);
			if ( searchEta >= l && searchEta < r ){
				index = i;
				break;
			}
		}

		if(index != -1){
			h_mu_Tracking_BCDEF_abseta_ratio->GetPoint(index,x,y);
			nomval = y;
			upval = y + h_mu_Tracking_BCDEF_abseta_ratio->GetErrorYhigh(index);
			downval = y - h_mu_Tracking_BCDEF_abseta_ratio->GetErrorYlow(index);
		}
		else {
			nomval = 1;
			upval = 1;
			downval = 1;
		}
	}

	else if ( type == "Tracking_BC" ){

		double x, y;
		double l,r;
		int index = -1;
		for(int i=0; i<h_mu_Tracking_BC_abseta_ratio->GetN(); i++){
			h_mu_Tracking_BC_abseta_ratio->GetPoint(i,x,y);
			l = x - h_mu_Tracking_BC_abseta_ratio->GetErrorXlow(i);
			r = x + h_mu_Tracking_BC_abseta_ratio->GetErrorXhigh(i);
			if ( searchEta >= l && searchEta < r ){
				index = i;
				break;
			}
		}

		if(index != -1){
			h_mu_Tracking_BC_abseta_ratio->GetPoint(index,x,y);
			nomval = y;
			upval = y + h_mu_Tracking_BC_abseta_ratio->GetErrorYhigh(index);
			downval = y - h_mu_Tracking_BC_abseta_ratio->GetErrorYlow(index);
		}
		else {
			nomval = 1;
			upval = 1;
			downval = 1;
		}
	}

	else if ( type == "Tracking_DE" ){

		double x, y;
		double l,r;
		int index = -1;
		for(int i=0; i<h_mu_Tracking_DE_abseta_ratio->GetN(); i++){
			h_mu_Tracking_DE_abseta_ratio->GetPoint(i,x,y);
			l = x - h_mu_Tracking_DE_abseta_ratio->GetErrorXlow(i);
			r = x + h_mu_Tracking_DE_abseta_ratio->GetErrorXhigh(i);
			if ( searchEta >= l && searchEta < r ){
				index = i;
				break;
			}
		}

		if(index != -1){
			h_mu_Tracking_DE_abseta_ratio->GetPoint(index,x,y);
			nomval = y;
			upval = y + h_mu_Tracking_DE_abseta_ratio->GetErrorYhigh(index);
			downval = y - h_mu_Tracking_DE_abseta_ratio->GetErrorYlow(index);
		}
		else {
			nomval = 1;
			upval = 1;
			downval = 1;
		}
	}

	else if ( type == "Tracking_F" ){

		double x, y;
		double l,r;
		int index = -1;
		for(int i=0; i<h_mu_Tracking_F_abseta_ratio->GetN(); i++){
			h_mu_Tracking_F_abseta_ratio->GetPoint(i,x,y);
			l = x - h_mu_Tracking_F_abseta_ratio->GetErrorXlow(i);
			r = x + h_mu_Tracking_F_abseta_ratio->GetErrorXhigh(i);
			if ( searchEta >= l && searchEta < r ){
				index = i;
				break;
			}
		}

		if(index != -1){
			h_mu_Tracking_F_abseta_ratio->GetPoint(index,x,y);
			nomval = y;
			upval = y + h_mu_Tracking_F_abseta_ratio->GetErrorYhigh(index);
			downval = y - h_mu_Tracking_F_abseta_ratio->GetErrorYlow(index);
		}
		else {
			nomval = 1;
			upval = 1;
			downval = 1;
		}
	}
	*/
  
  else {

    std::cout << "Unknown Type. Supported Types are: ID, Trigger, Iso" << std::endl;
    nomval = -1;
    upval = -1;
    downval= -1;

  }


  if ( syst==-1 ){ return downval; }
  else if ( syst==1 ){ return upval; }
  else { return nomval; }


}
float LeptonSFHelper::GetElectronElectronSF(  float electronEta1 , float electronEta2 , int syst , std::string type  ) {

  float nomval = 0;
  /*
  int thisBin=0;

  float searchEta1=fabs(electronEta1);
  float searchEta2=fabs(electronEta2);


  if ( type == "Trigger" ){

    thisBin = h_ele_ele_TRIGGER_abseta_abseta->FindBin( searchEta1 , searchEta2 );
    nomval = h_ele_ele_TRIGGER_abseta_abseta->GetBinContent( thisBin );

  }
  */
  return nomval;
}
float LeptonSFHelper::GetMuonMuonSF(  float muonEta1 , float muonEta2 , int syst , std::string type  ) {

  float nomval = 0;
  /*
  int thisBin=0;

  float searchEta1=fabs(muonEta1);
  float searchEta2=fabs(muonEta2);


  if ( type == "Trigger" ){

    //thisBin = h_mu_mu_TRIGGER_abseta_abseta->FindBin( searchEta1 , searchEta2 );
    //nomval = h_mu_mu_TRIGGER_abseta_abseta->GetBinContent( thisBin );

  }
  */
  return nomval;
}
float LeptonSFHelper::GetElectronMuonSF(  float electronEta , float muonEta , int syst , std::string type  ) {

  float nomval = 0;
  /*
  int thisBin=0;

  float searchEta1=fabs(electronEta);
  float searchEta2=fabs(muonEta);

  float nomval = 0;
  if ( type == "Trigger" ){

    //thisBin = h_ele_mu_TRIGGER_abseta_abseta->FindBin( searchEta1 , searchEta2 );
    //nomval= h_ele_mu_TRIGGER_abseta_abseta->GetBinContent( thisBin );

  }
  */
  return nomval;
}
//PRIVATE

void LeptonSFHelper::SetElectronHistos( ){

  std::string IDinputFile_BCDEF = std::string(getenv("CMSSW_BASE")) + "/src/analyzers/ttH_bb/data/leptonSF/2017/" + "egammaEffi.txt_EGM2D_runBCDEF_passingTight94X.root";
  std::string IDinputFile_B = std::string(getenv("CMSSW_BASE")) + "/src/analyzers/ttH_bb/data/leptonSF/2017/" + "egammaEffi.txt_EGM2D_runB_passingTight94X.root";
  std::string IDinputFile_C = std::string(getenv("CMSSW_BASE")) + "/src/analyzers/ttH_bb/data/leptonSF/2017/" + "egammaEffi.txt_EGM2D_runC_passingTight94X.root";
  std::string IDinputFile_D = std::string(getenv("CMSSW_BASE")) + "/src/analyzers/ttH_bb/data/leptonSF/2017/" + "egammaEffi.txt_EGM2D_runD_passingTight94X.root";
  std::string IDinputFile_E = std::string(getenv("CMSSW_BASE")) + "/src/analyzers/ttH_bb/data/leptonSF/2017/" + "egammaEffi.txt_EGM2D_runE_passingTight94X.root";
  std::string IDinputFile_F = std::string(getenv("CMSSW_BASE")) + "/src/analyzers/ttH_bb/data/leptonSF/2017/" + "egammaEffi.txt_EGM2D_runF_passingTight94X.root";
  std::string ISOinputFile_BCDEF = std::string(getenv("CMSSW_BASE")) + "/src/analyzers/ttH_bb/data/leptonSF/2017/" + "egammaEffi.txt_EGM2D_runBCDEF_passingRECO.root";
  std::string ISOinputFile_BCDEF_lowEt = std::string(getenv("CMSSW_BASE")) + "/src/analyzers/ttH_bb/data/leptonSF/2017/" + "egammaEffi.txt_EGM2D_runBCDEF_passingRECO_lowEt.root";
  std::string ISOinputFile_B = std::string(getenv("CMSSW_BASE")) + "/src/analyzers/ttH_bb/data/leptonSF/2017/" + "egammaEffi.txt_EGM2D_runB_passingRECO.root";
  std::string ISOinputFile_C = std::string(getenv("CMSSW_BASE")) + "/src/analyzers/ttH_bb/data/leptonSF/2017/" + "egammaEffi.txt_EGM2D_runC_passingRECO.root";
  std::string ISOinputFile_D = std::string(getenv("CMSSW_BASE")) + "/src/analyzers/ttH_bb/data/leptonSF/2017/" + "egammaEffi.txt_EGM2D_runD_passingRECO.root";
  std::string ISOinputFile_E = std::string(getenv("CMSSW_BASE")) + "/src/analyzers/ttH_bb/data/leptonSF/2017/" + "egammaEffi.txt_EGM2D_runE_passingRECO.root";
  std::string ISOinputFile_F = std::string(getenv("CMSSW_BASE")) + "/src/analyzers/ttH_bb/data/leptonSF/2017/" + "egammaEffi.txt_EGM2D_runF_passingRECO.root";
  //std::string TRIGGERinputFile = std::string(getenv("CMSSW_BASE")) + "/src/analyzers/ttH_bb/data/leptonSF/2017/TriggerSF_EG_Run2016All_v1.root";

  TFile *f_IDSF_BCDEF = new TFile(std::string(IDinputFile_BCDEF).c_str(),"READ");
  TFile *f_IDSF_B = new TFile(std::string(IDinputFile_B).c_str(),"READ");
  TFile *f_IDSF_C = new TFile(std::string(IDinputFile_C).c_str(),"READ");
  TFile *f_IDSF_D = new TFile(std::string(IDinputFile_D).c_str(),"READ");
  TFile *f_IDSF_E = new TFile(std::string(IDinputFile_E).c_str(),"READ");
  TFile *f_IDSF_F = new TFile(std::string(IDinputFile_F).c_str(),"READ");
  TFile *f_ISOSF_BCDEF = new TFile(std::string(ISOinputFile_BCDEF).c_str(),"READ");
  TFile *f_ISOSF_BCDEF_lowEt = new TFile(std::string(ISOinputFile_BCDEF_lowEt).c_str(),"READ");
  TFile *f_ISOSF_B = new TFile(std::string(ISOinputFile_B).c_str(),"READ");
  TFile *f_ISOSF_C = new TFile(std::string(ISOinputFile_C).c_str(),"READ");
  TFile *f_ISOSF_D = new TFile(std::string(ISOinputFile_D).c_str(),"READ");
  TFile *f_ISOSF_E = new TFile(std::string(ISOinputFile_E).c_str(),"READ");
  TFile *f_ISOSF_F = new TFile(std::string(ISOinputFile_F).c_str(),"READ");
  //TFile *f_TRIGGERSF = new TFile(std::string(TRIGGERinputFile).c_str(),"READ");

  h_ele_ID_BCDEF_abseta_pt_ratio = (TH2F*)f_IDSF_BCDEF->Get("EGamma_SF2D");
  h_ele_ID_B_abseta_pt_ratio = (TH2F*)f_IDSF_B->Get("EGamma_SF2D");
  h_ele_ID_C_abseta_pt_ratio = (TH2F*)f_IDSF_C->Get("EGamma_SF2D");
  h_ele_ID_D_abseta_pt_ratio = (TH2F*)f_IDSF_D->Get("EGamma_SF2D");
  h_ele_ID_E_abseta_pt_ratio = (TH2F*)f_IDSF_E->Get("EGamma_SF2D");
  h_ele_ID_F_abseta_pt_ratio = (TH2F*)f_IDSF_F->Get("EGamma_SF2D");
  h_ele_ISO_BCDEF_abseta_pt_ratio = (TH2F*)f_ISOSF_BCDEF->Get("EGamma_SF2D");
  h_ele_ISO_BCDEF_lowEt_abseta_pt_ratio = (TH2F*)f_ISOSF_BCDEF_lowEt->Get("EGamma_SF2D");
  h_ele_ISO_B_abseta_pt_ratio = (TH2F*)f_ISOSF_B->Get("EGamma_SF2D");
  h_ele_ISO_C_abseta_pt_ratio = (TH2F*)f_ISOSF_C->Get("EGamma_SF2D");
  h_ele_ISO_D_abseta_pt_ratio = (TH2F*)f_ISOSF_D->Get("EGamma_SF2D");
  h_ele_ISO_E_abseta_pt_ratio = (TH2F*)f_ISOSF_E->Get("EGamma_SF2D");
  h_ele_ISO_F_abseta_pt_ratio = (TH2F*)f_ISOSF_F->Get("EGamma_SF2D");
  //h_ele_TRIGGER_abseta_pt_ratio = (TH2F*)f_TRIGGERSF->Get("Ele27_WPTight_Gsf");

}

void LeptonSFHelper::SetMuonHistos( ){

  std::string IDinputFile_BCDEF = std::string(getenv("CMSSW_BASE")) + "/src/analyzers/ttH_bb/data/leptonSF/2017/" + "RunBCDEF_SF_ID.root";
  std::string IDinputFile_BC = std::string(getenv("CMSSW_BASE")) + "/src/analyzers/ttH_bb/data/leptonSF/2017/" + "RunBC_SF_ID.root";
  std::string IDinputFile_DE = std::string(getenv("CMSSW_BASE")) + "/src/analyzers/ttH_bb/data/leptonSF/2017/" + "RunDE_SF_ID.root";
  std::string IDinputFile_F = std::string(getenv("CMSSW_BASE")) + "/src/analyzers/ttH_bb/data/leptonSF/2017/" + "RunF_SF_ID.root";
  std::string ISOinputFile_BCDEF = std::string(getenv("CMSSW_BASE")) + "/src/analyzers/ttH_bb/data/leptonSF/2017/" + "RunBCDEF_SF_ISO.root";
  std::string ISOinputFile_BC = std::string(getenv("CMSSW_BASE")) + "/src/analyzers/ttH_bb/data/leptonSF/2017/" + "RunBC_SF_ISO.root";
  std::string ISOinputFile_DE = std::string(getenv("CMSSW_BASE")) + "/src/analyzers/ttH_bb/data/leptonSF/2017/" + "RunDE_SF_ISO.root";
  std::string ISOinputFile_F = std::string(getenv("CMSSW_BASE")) + "/src/analyzers/ttH_bb/data/leptonSF/2017/" + "RunF_SF_ISO.root";
  //std::string TRIGGERinputFile_BF =  std::string(getenv("CMSSW_BASE")) + "/src/analyzers/ttH_bb/data/leptonSF/2017/" + "Trigger_EfficienciesAndSF_MU_RunBtoF.root";
  //std::string TRIGGERinputFile_GH =  std::string(getenv("CMSSW_BASE")) + "/src/analyzers/ttH_bb/data/leptonSF/2017/" + "Trigger_EfficienciesAndSF_MU_Period4.root";
  //std::string TrackinginputFile_BCDEF = std::string(getenv("CMSSW_BASE")) + "/src/analyzers/ttH_bb/data/leptonSF/2017/" + "RunBCDEF_SF_Tracking.root";
  //std::string TrackinginputFile_BC = std::string(getenv("CMSSW_BASE")) + "/src/analyzers/ttH_bb/data/leptonSF/2017/" + "RunBC_SF_Tracking.root";
  //std::string TrackinginputFile_DE = std::string(getenv("CMSSW_BASE")) + "/src/analyzers/ttH_bb/data/leptonSF/2017/" + "RunDE_SF_Tracking.root";
  //std::string TrackinginputFile_F = std::string(getenv("CMSSW_BASE")) + "/src/analyzers/ttH_bb/data/leptonSF/2017/" + "RunF_SF_Tracking.root";

  TFile *f_IDSF_BCDEF = new TFile(std::string(IDinputFile_BCDEF).c_str(),"READ");
  TFile *f_IDSF_BC = new TFile(std::string(IDinputFile_BC).c_str(),"READ");
  TFile *f_IDSF_DE = new TFile(std::string(IDinputFile_DE).c_str(),"READ");
  TFile *f_IDSF_F = new TFile(std::string(IDinputFile_F).c_str(),"READ");
  TFile *f_ISOSF_BCDEF = new TFile(std::string(ISOinputFile_BCDEF).c_str(),"READ");
  TFile *f_ISOSF_BC = new TFile(std::string(ISOinputFile_BC).c_str(),"READ");
  TFile *f_ISOSF_DE = new TFile(std::string(ISOinputFile_DE).c_str(),"READ");
  TFile *f_ISOSF_F = new TFile(std::string(ISOinputFile_F).c_str(),"READ");
  //TFile *f_TRIGGERSF_BF = new TFile(std::string(TRIGGERinputFile_BF).c_str(),"READ");
  //TFile *f_TRIGGERSF_GH = new TFile(std::string(TRIGGERinputFile_GH).c_str(),"READ");
  //TFile *f_TrackingSF_BCDEF = new TFile(std::string(TrackinginputFile_BCDEF).c_str(),"READ");
  //TFile *f_TrackingSF_BC = new TFile(std::string(TrackinginputFile_BC).c_str(),"READ");
  //TFile *f_TrackingSF_DE = new TFile(std::string(TrackinginputFile_DE).c_str(),"READ");
  //TFile *f_TrackingSF_F = new TFile(std::string(TrackinginputFile_F).c_str(),"READ");


  h_mu_ID_BCDEF_abseta_pt_ratio = (TH2F*)f_IDSF_BCDEF->Get("NUM_TightID_DEN_genTracks_pt_abseta");
  h_mu_ID_BC_abseta_pt_ratio = (TH2F*)f_IDSF_BC->Get("NUM_TightID_DEN_genTracks");
  h_mu_ID_DE_abseta_pt_ratio = (TH2F*)f_IDSF_DE->Get("NUM_TightID_DEN_genTracks");
  h_mu_ID_F_abseta_pt_ratio = (TH2F*)f_IDSF_F->Get("NUM_TightID_DEN_genTracks");
  h_mu_ISO_BCDEF_abseta_pt_ratio = (TH2F*)f_ISOSF_BCDEF->Get("NUM_TightRelIso_DEN_TightIDandIPCut_pt_abseta");
  h_mu_ISO_BC_abseta_pt_ratio = (TH2F*)f_ISOSF_BC->Get("NUM_TightRelIso_DEN_TightIDandIPCut");
  h_mu_ISO_DE_abseta_pt_ratio = (TH2F*)f_ISOSF_DE->Get("NUM_TightRelIso_DEN_TightIDandIPCut");
  h_mu_ISO_F_abseta_pt_ratio = (TH2F*)f_ISOSF_F->Get("NUM_TightRelIso_DEN_TightIDandIPCut");
  //h_mu_TRIGGER_BF_abseta_pt_ratio = (TH2F*)f_TRIGGERSF_BF->Get("IsoMu24_OR_IsoTkMu24_PtEtaBins/pt_abseta_ratio");
  //h_mu_TRIGGER_GH_abseta_pt_ratio = (TH2F*)f_TRIGGERSF_GH->Get("IsoMu24_OR_IsoTkMu24_PtEtaBins/pt_abseta_ratio");
  //h_mu_Tracking_BCDEF_abseta_ratio = (TGraphAsymmErrors*)f_TrackingSF_BCDEF->Get("ratio_eff_aeta_dr030e030_corr");
  //h_mu_Tracking_BC_abseta_ratio = (TGraphAsymmErrors*)f_TrackingSF_BC->Get("ratio_eff_aeta_dr030e030_corr");
  //h_mu_Tracking_DE_abseta_ratio = (TGraphAsymmErrors*)f_TrackingSF_DE->Get("ratio_eff_aeta_dr030e030_corr");
  //h_mu_Tracking_F_abseta_ratio = (TGraphAsymmErrors*)f_TrackingSF_F->Get("ratio_eff_aeta_dr030e030_corr");

}

void LeptonSFHelper::SetElectronElectronHistos( ){
  //std::string TRIGGERinputFile = std::string(getenv("CMSSW_BASE")) + "/src/analyzers/ttH_bb/data/leptonSF/2017/" + "triggerSummary_ee_ReReco2016_ttH.root";

  //TFile *f_TRIGGERSF = new TFile(std::string(TRIGGERinputFile).c_str(),"READ");

  //h_ele_ele_TRIGGER_abseta_abseta = (TH2F*)f_TRIGGERSF->Get("scalefactor_eta2d_with_syst");
}

void LeptonSFHelper::SetMuonMuonHistos( ){
  //std::string TRIGGERinputFile = std::string(getenv("CMSSW_BASE")) + "/src/analyzers/ttH_bb/data/leptonSF/2017/" + "triggerSummary_mumu_ReReco2016_ttH.root";

  //TFile *f_TRIGGERSF = new TFile(std::string(TRIGGERinputFile).c_str(),"READ");

  //h_mu_mu_TRIGGER_abseta_abseta = (TH2F*)f_TRIGGERSF->Get("scalefactor_eta2d_with_syst");
}

void LeptonSFHelper::SetElectronMuonHistos( ){
  //std::string TRIGGERinputFile = std::string(getenv("CMSSW_BASE")) + "/src/analyzers/ttH_bb/data/leptonSF/2017/" + "triggerSummary_emu_ReReco2016_ttH.root";

  //TFile *f_TRIGGERSF = new TFile(std::string(TRIGGERinputFile).c_str(),"READ");

  //h_ele_mu_TRIGGER_abseta_abseta = (TH2F*)f_TRIGGERSF->Get("scalefactor_eta2d_with_syst");
}
