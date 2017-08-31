#include "ImitationObjective.h"

#include "scone/core/Exception.h"
#include "scone/model/Model.h"

#include "scone/core/version.h"
#include "scone/core/string_tools.h"
#include "scone/core/system_tools.h"
#include "scone/core/Factories.h"
#include "../core/StorageIo.h"
#include "scone/model/Muscle.h"

namespace scone
{
	ImitationObjective::ImitationObjective( const PropNode& pn ) :
	Objective( pn ),
	m_ModelPropsCopy( pn.get_child( "Model" ) )
	{
		INIT_PROP_REQUIRED( pn, file );

		// create model to flag unused model props and create par_info_
		auto model = CreateModel( pn.get_child( "Model" ), info_ );
		m_Signature = model->GetSignature();
		ReadStorageSto( m_Storage, ( scone::GetFolder(SCONE_SCENARIO_FOLDER ) / file ).str() );

		// make sure data and model are compatible
		auto state = model->GetState();
		SCONE_THROW_IF( state.GetSize() > m_Storage.GetChannelCount(), "File and model are incompatible for ImitationObjective" );
		for ( Index i = 0; i < state.GetSize(); ++i )
			SCONE_THROW_IF( state.GetName( i ) != m_Storage.GetLabels()[ i ], "File and model are incompatible for ImitationObjective" );

		// find excitation channels
		m_ExcitationChannels.reserve( model->GetMuscles().size() );
		for ( auto& mus : model->GetMuscles() )
		{
			m_ExcitationChannels.push_back( m_Storage.GetChannelIndex( mus->GetName() + ".excitation" ) );
			SCONE_THROW_IF( m_ExcitationChannels.back() == NoIndex, "Could not find excitation for " + mus->GetName() );
		}
	}

	ImitationObjective::~ImitationObjective()
	{}

	scone::fitness_t ImitationObjective::evaluate( const ParamInstance& point ) const
	{
		// WARNING: this function must be thread-safe and should only access local or const variables
		auto model = CreateModel( m_ModelPropsCopy, ParamInstance( point ) );
		double result = 0.0;

		for ( Index i = 0; i < m_Storage.GetFrameCount(); ++i )
		{
			auto f = m_Storage.GetFrame( i );
			model->SetStateValues( f.GetValues(), f.GetTime() );
			model->UpdateControlValues();

			// compare results
			for ( Index idx = 0; idx < m_ExcitationChannels.size(); ++idx )
				result += abs( model->GetMuscles()[ idx ]->GetExcitation() - f[ m_ExcitationChannels[ idx ] ] );
		}
		return result / m_Storage.GetFrameCount() / m_ExcitationChannels.size();
	}

	String ImitationObjective::GetClassSignature() const
	{
		return m_Signature;
	}
}
