struct ProgressbarProxy
(
	targetprogressbar = undefined
	,
	totalprogressstep = 0
	,
	currentprogressstep = 0
	,
	allocedpercentage = 0
	,
	value_progressedstep = 0
	,
	value_normal_percent = 0
	,
	fn setprogressbar arg_bar =
	(
		targetprogressbar = arg_bar;
		value_normal_percent = arg_bar.value;
	)
	,
	fn settotalstep arg_step =
	(
		totalprogressstep = arg_step;
	)
	,
	fn setallocpercent arg_percent = 
	(
		allocedpercentage = arg_percent;
	)
	,
	fn increasestep = 
	(
		currentprogressstep = ((allocedpercentage as float)/(totalprogressstep as float));
		value_progressedstep += currentprogressstep;
		if value_progressedstep <= allocedpercentage then
		(
			targetprogressbar.value = value_normal_percent + value_progressedstep;
		)
	)
)