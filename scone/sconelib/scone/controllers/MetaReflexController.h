#pragma once

#include "scone/model/Controller.h"
#include "scone/core/types.h"

namespace scone
{
	class SCONE_API MetaReflexController : public Controller
	{
	public:
		MetaReflexController( const PropNode& props, ParamSet& par, Model& model, const Locality& area );
		virtual ~MetaReflexController();

		virtual UpdateResult UpdateControls( Model& model, double timestamp ) override;

		const std::vector< MetaReflexDofUP >& GetReflexDofs() const { return m_ReflexDofs; }
		const std::vector< MetaReflexVirtualMuscleUP >& GetVirtualMuscles() const { return m_VirtualMuscles; }

	private:
		MetaReflexController( const MetaReflexController& other );
		MetaReflexController& operator=( const MetaReflexController& other );

		virtual String GetClassSignature() const override;

		virtual void StoreData( Storage< Real >::Frame& frame ) override;

		std::vector< MetaReflexDofUP > m_ReflexDofs;
		std::vector< MetaReflexVirtualMuscleUP > m_VirtualMuscles;
		std::vector< MetaReflexMuscleUP > m_ReflexMuscles;
	};
}