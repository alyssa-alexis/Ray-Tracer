// Light methods (3 total)

#include "lightbase.hpp"

CMRT::LightBase::LightBase()
{
}


CMRT::LightBase::~LightBase()
{
}


bool CMRT::LightBase::ComputeIllumination(	const qbVector<double> &intPoint,
											const qbVector<double> &localNormal,
											const std::vector<std::shared_ptr<CMRT::ObjectBase>> &objectList,
											const std::shared_ptr<CMRT::ObjectBase> &currentObject,
											qbVector<double> &color,
											double &intensity)
{
	return false;
}