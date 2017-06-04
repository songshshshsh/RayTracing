#include "PhotonMap.h"
#include "base.h"

const static double radius = 10.0;

int PhotonMap::getPhotonNumber(Photon* photon)
{
	int tot = 0;
	for (int i = 0;i < photons.size();++i)
		if (dist(photon->position,photons[i].position) <= radius)
			tot += 1;
	return tot;
}