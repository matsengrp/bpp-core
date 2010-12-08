//
// File: ConstantDistribution.cpp
// Created by: jdutheil <Julien.Dutheil@univ-montp2.fr>
// Created on: Fri Oct 24 08:48:03 2003
//

/*
Copyright or © or Copr. CNRS, (November 17, 2004)

This software is a computer program whose purpose is to provide classes
for numerical calculus.

This software is governed by the CeCILL  license under French law and
abiding by the rules of distribution of free software.  You can  use, 
modify and/ or redistribute the software under the terms of the CeCILL
license as circulated by CEA, CNRS and INRIA at the following URL
"http://www.cecill.info". 

As a counterpart to the access to the source code and  rights to copy,
modify and redistribute granted by the license, users are provided only
with a limited warranty  and the software's author,  the holder of the
economic rights,  and the successive licensors  have only  limited
liability. 

In this respect, the user's attention is drawn to the risks associated
with loading,  using,  modifying and/or developing or reproducing the
software by the user in light of its specific status of free software,
that may mean  that it is complicated to manipulate,  and  that  also
therefore means  that it is reserved for developers  and  experienced
professionals having in-depth computer knowledge. Users are therefore
encouraged to load and test the software's suitability as regards their
requirements in conditions enabling the security of their systems and/or 
data to be ensured and,  more generally, to use and operate it in the 
same conditions as regards security. 

The fact that you are presently reading this means that you have had
knowledge of the CeCILL license and that you accept its terms.
*/

#include "ConstantDistribution.h"

using namespace bpp;

/******************************************************************************/

ConstantDistribution::ConstantDistribution(double value, bool fixed) : AbstractDiscreteDistribution(1,"Constant."),
                                                                       value_(value)
{
  if (! fixed)
    addParameter_(Parameter("Constant.value",value));
  distribution_[value_] = 1; //One single class of rate 1 with probability 1.
}

/******************************************************************************/

void ConstantDistribution::fireParameterChanged(const ParameterList& parameters) 
{
  AbstractDiscreteDistribution::fireParameterChanged(parameters);
  
  if (hasParameter("value")){
    value_=getParameterValue("value");
    distribution_.clear();
    distribution_[getParameterValue("value")] = 1; //One single class of rate 1 with probability 1.
  }
}

/******************************************************************************/

Domain ConstantDistribution::getDomain() const
{
  return Domain(value_,value_,1);
}

/******************************************************************************/

std::string ConstantDistribution::getName() const
{
  return("ConstantDistribution");
}

/******************************************************************************/

void ConstantDistribution::restrictToConstraint(const Constraint& c)
{
  if (getNumberOfParameters()==0)
    return;
  
  const Interval* pi=dynamic_cast<const Interval*>(&c);
  if (!pi)
    throw Exception("ConstantDistribution::restrictToConstraint: Non-interval exception");

  if (! pi->isCorrect(getParameterValue("value")))
    throw ConstraintException("Impossible to restrict to Constraint", &getParameter_("value"), getParameterValue("value_"));

  AbstractDiscreteDistribution::restrictToConstraint(c);
  
  getParameter_("value").setConstraint(&intMinMax_);
}
