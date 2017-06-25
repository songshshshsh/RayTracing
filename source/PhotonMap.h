#ifndef PHOTONMAP_H
#define PHOTONMAP_H

#include "Photon.h"
#include "base.h"
#include "kdtree.h"
#include <vector>


class PhotonMap
{
	public:
		int getPhotonNumber(Photon*);
		Color getPhotonFlux(Photon&);
		void addPhoton(Photon& photon)
		{
			// printf("added\n");
			photons.push_back(photon);
			// if (photons.size() % 100000 == 0)
			// 	printf("%lu\n",photons.size());
		}
		void Balance();
		std::vector<Photon> photons;
	private:
		kdt::KDTree<Photon>* kdtree;
		double BRDF(Photon&);
};

#endif