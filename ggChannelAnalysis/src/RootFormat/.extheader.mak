RootFormat.d: ../../include/MiniElectronBranches.h ../../include/MiniElectron.h ../../include/MiniEventBranches.h ../../include/MiniJetBranches.h ../../include/MiniJet.h ../../include/MiniMuonBranches.h ../../include/MiniMuon.h ../../include/ParticleReader.h 
../../include/MiniElectronBranches.h: MiniElectronBranches.h
	@rm -f ../../include/MiniElectronBranches.h
	@ln -fs ../src/RootFormat/MiniElectronBranches.h ../../include/MiniElectronBranches.h
../../include/MiniElectron.h: MiniElectron.h
	@rm -f ../../include/MiniElectron.h
	@ln -fs ../src/RootFormat/MiniElectron.h ../../include/MiniElectron.h
../../include/MiniEventBranches.h: MiniEventBranches.h
	@rm -f ../../include/MiniEventBranches.h
	@ln -fs ../src/RootFormat/MiniEventBranches.h ../../include/MiniEventBranches.h
../../include/MiniJetBranches.h: MiniJetBranches.h
	@rm -f ../../include/MiniJetBranches.h
	@ln -fs ../src/RootFormat/MiniJetBranches.h ../../include/MiniJetBranches.h
../../include/MiniJet.h: MiniJet.h
	@rm -f ../../include/MiniJet.h
	@ln -fs ../src/RootFormat/MiniJet.h ../../include/MiniJet.h
../../include/MiniMuonBranches.h: MiniMuonBranches.h
	@rm -f ../../include/MiniMuonBranches.h
	@ln -fs ../src/RootFormat/MiniMuonBranches.h ../../include/MiniMuonBranches.h
../../include/MiniMuon.h: MiniMuon.h
	@rm -f ../../include/MiniMuon.h
	@ln -fs ../src/RootFormat/MiniMuon.h ../../include/MiniMuon.h
../../include/ParticleReader.h: ParticleReader.h
	@rm -f ../../include/ParticleReader.h
	@ln -fs ../src/RootFormat/ParticleReader.h ../../include/ParticleReader.h
