#pragma once

#include "scone/core/system_tools.h"
#include "scone/model/Model.h"
#include "scone/optimization/SimulationObjective.h"
#include "scone/optimization/Objective.h"
#include "scone/model/State.h"
#include "scone/core/types.h"
#include "scone/optimization/ModelObjective.h"
#include "ModelVis.h"

namespace scone
{
	class Scenario
	{
	public:
		Scenario( vis::scene& s, const path& filename );
		~Scenario();

		void UpdateVis( TimeInSeconds t );
		void EvaluateTo( TimeInSeconds t );
		void FinalizeEvaluation( bool output_results );

		const Storage<>& GetData() { return storage_; }
		Model& GetSimModel() { return *model_; }
		ModelObjective& GetObjective() { return *model_objective_; }

		bool IsEvaluating() const { return is_evaluating; }
		TimeInSeconds GetTime() const { return model_->GetTime(); }
		TimeInSeconds GetMaxTime() const { return IsEvaluating() ? model_objective_->GetDuration() : storage_.Back().GetTime(); }

		void ApplyViewSettings( const ModelVis::ViewSettings& f );
		const path& GetFileName() { return filename_; }

	private:
		// visualizer
		u_ptr<ModelVis> vis_;

		// model / scenario data
		Storage<> storage_;
		ModelObjectiveUP model_objective_;
		ModelUP model_;
		path filename_;
		bool is_evaluating;

		// model state
		std::vector< size_t > state_data_index;
		State model_state;
		void InitStateDataIndices();
	};
}