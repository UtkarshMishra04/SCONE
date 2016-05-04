#pragma once

#include "cs.h"
#include "Reflex.h"
#include "scone/sim/SensorDelayAdapter.h"
#include "scone/core/Range.h"

namespace scone
{
	namespace cs
	{
		class SCONE_API MuscleReflex : public Reflex
		{
		public:
			MuscleReflex( const PropNode& props, opt::ParamSet& par, sim::Model& model, const sim::Area& area );
			virtual ~MuscleReflex();

			virtual void ComputeControls( double timestamp ) override;

			// Reflex parameters
			Real length_gain;
			Real length_ofs;
			Real force_gain;
			Real velocity_gain;
			Real u_constant;

		private:
			sim::SensorDelayAdapter* m_pForceSensor;
			sim::SensorDelayAdapter* m_pLengthSensor;
			sim::SensorDelayAdapter* m_pVelocitySensor;
		};
	}
}