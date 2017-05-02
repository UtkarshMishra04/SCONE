#pragma once

#include "scone/core/types.h"
#include "scone/core/HasSignature.h"
#include "scone/core/HasData.h"
#include "scone/model/State.h"

namespace scone
{
	class SCONE_API Controller : public HasSignature, public HasData
	{
	public:
		Controller( const PropNode& props, ParamSet& par, Model& model, const Locality& target_area );
		virtual ~Controller();

		enum UpdateResult { SuccessfulUpdate, NoUpdate, RequestTermination };

		/// Called each attempted integration step
		// TODO: use Result< UpdateResult > or bool
		virtual UpdateResult UpdateControls( Model& model, double timestamp ) { return NoUpdate; }

		/// Called after each successful integration step
		// TODO: use Result< UpdateResult > or bool
		virtual UpdateResult UpdateAnalysis( const Model& model, double timestamp ) { return NoUpdate; }

		// default implementation doesn't store anything
		virtual void StoreData( Storage< Real >::Frame& frame ) override {}

	private:
		bool m_TerminationRequest;
	};
}