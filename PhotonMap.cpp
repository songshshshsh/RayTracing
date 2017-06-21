#include "PhotonMap.h"
#include "Object.h"

const static double radius = 10.0;

int PhotonMap::getPhotonNumber(Photon* photon)
{
	// printf("%lu\n", photons.size());
	int tot = 0;
	for (int i = 0;i < photons.size();++i)
		if (dist(photon->position,photons[i].position) <= radius)
			tot += 1;
	return tot;
}

void PhotonMap::Balance()
{
	kdtree = new kdt::KDTree<Photon>(photons);
}

double PhotonMap::getPhotonFlux(Photon& photon)
{
	int k = 10;
	std::vector<int> indices = kdtree->knnSearch(photon, k);
	// printf("2333\n");
	double max_r = 0;
	for (int i = 0;i < indices.size();++i)
		if (dist(photons[indices[i]].position,photon.position) > max_r)
			max_r = dist(photons[indices[i]].position,photon.position);
	// printf("23333\n");
	// printf("%f\n", max_r);
	double flux = 0;
	for (int i = 0;i < indices.size();++i)
		flux += BRDF(photons[indices[i]])/(asin(1) * max_r * max_r);
	return flux;
}

double PhotonMap::BRDF(Photon& photon)
{
	double temp = photon.direction.dot(photon.object->getVerticalVector(photon.position))/photon.direction.Veclen();
	if (temp > 0)
	{
		return temp;
	}
	return 0;
}