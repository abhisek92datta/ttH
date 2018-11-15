#ifndef CU_ttH_EDA_Handles_CC
#define CU_ttH_EDA_Handles_CC

#include "CU_ttH_EDA_Handles.h"

/// Set up handles with getByToken from edm::Event
void Set_up_handles(const Event &iEvent, const EventSetup &iSetup,
                    const CU_ttH_EDA_event_vars &local, edm_Handles &handle,
                    edm_Tokens &token)
{
    iEvent.getByToken(token.triggerResults, handle.triggerResults);
    iEvent.getByToken(token.filterResults, handle.filterResults);
    iEvent.getByToken(token.triggerObjects, handle.triggerObjects);

    iEvent.getByToken(token.vertices, handle.vertices);
    iEvent.getByToken(token.sec_vertices, handle.sec_vertices);
    iEvent.getByToken(token.PU_info, handle.PU_info);
    iEvent.getByToken(token.srcRho, handle.srcRho);

    iEvent.getByToken(token.electrons, handle.electrons);
    iEvent.getByToken(token.muons, handle.muons);
    iEvent.getByToken(token.jets, handle.jets);
    iEvent.getByToken(token.METs, handle.METs);
    iEvent.getByToken(token.genjets, handle.genjets);
    iEvent.getByToken(token.genparticles, handle.genparticles);

    iEvent.getByToken(token.PF_candidates, handle.PF_candidates);

    iEvent.getByToken(token.BS, handle.BS);

    iEvent.getByToken(token.eleTightIdMapToken_, handle.tight_id_decisions);
    // iEvent.getByToken(token.mvaValuesMapToken_, handle.mvaValues);
    // iEvent.getByToken(token.mvaCategoriesMapToken_, handle.mvaCategories);
    iEvent.getByToken(token.electrons_for_mva_token, handle.electrons_for_mva);
    iEvent.getByToken(token.muon_h_token, handle.muon_h);

    iEvent.getByToken(token.puInfoToken, handle.PupInfo);

    if (!local.isdata) {
        // for PDF weight
        iEvent.getByToken(token.event_gen_info, handle.event_gen_info);

        // for ttHf categorization
        iEvent.getByToken(token.genTtbarIdToken_, handle.genTtbarId);
		//if(!local.is_madg)
			//iEvent.getByToken(token.ttHFGenFilterToken_, handle.ttHFGenFilter);

        // for Q2 weight
        if (!local.is_OLS)
            iEvent.getByToken(token.lheptoken, handle.EvtHandle);
    }

    //iSetup.get<TransientTrackRecord>().get("TransientTrackBuilder", handle.ttrkbuilder);
}

#endif
