#ifndef PHOTONMAP_H
#define PHOTONMAP_H

#include "Photon.h"
#include <vector>

class PhotonMap
{
	public:
		int getPhotonNumber(Photon*);
	private:
		std::vector<Photon> photons;
};

#endif