#ifndef PHOTONMAP_H
#define PHOTONMAP_H

#include "Photon.h"
#include "base.h"
#include <vector>


class PhotonMap
{
	public:
		int getPhotonNumber(Photon*);
		double getPhotonFlux(Photon*){return 0;}
		void addPhoton(Photon& photon)
		{
			// printf("added\n");
			photons.push_back(photon);
			// if (photons.size() % 100000 == 0)
			// 	printf("%lu\n",photons.size());
		}
	private:
		std::vector<Photon> photons;
};

#endif