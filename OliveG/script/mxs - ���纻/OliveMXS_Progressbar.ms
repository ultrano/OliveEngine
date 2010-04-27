struct ProgressbarProxy
(
	targetprogressbar
	,
	totalprogressstep
	,
	currentprogressstep
	,
	allocedpercentage
	,
	value_progressedstep = 0
	,
	fn increasestep = 
	(
		currentprogressstep = (allocedpercentage/totalprogressstep);
		value_progressedstep += currentprogressstep;
		if value_progressedstep <= allocedpercentage then
			ref_targetprogressbar.value += (value_progressedstep as integer);
	)
)