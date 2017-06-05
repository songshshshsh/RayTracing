#ifndef PHOTONMAP_H
#define PHOTONMAP_H

#include "Photon.h"
#include "base.h"
#include <vector>


class PhotonMap
{
	public:
		int getPhotonNumber(Photon*);
		void addPhoton(Photon& photon)
		{
			photons.push_back(photon);
		}
	private:
		std::vector<Photon> photons;
};

#endif