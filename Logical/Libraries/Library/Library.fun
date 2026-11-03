
{REDUND_ERROR} FUNCTION_BLOCK DriveStateMashine (*TODO: Add your comment here*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		state : {REDUND_UNREPLICABLE} UINT;
		enable : {REDUND_UNREPLICABLE} BOOL;
	END_VAR
	VAR_OUTPUT
		command : {REDUND_UNREPLICABLE} UINT;
		speedSet : {REDUND_UNREPLICABLE} INT;
		speed : INT;
	END_VAR
	VAR
		step : {REDUND_UNREPLICABLE} UINT;
	END_VAR
END_FUNCTION_BLOCK

FUNCTION_BLOCK LedStateMashine
	VAR_INPUT
		state : UINT;
	END_VAR
	VAR_OUTPUT
		led1 : BOOL;
		led2 : BOOL;
		led3 : BOOL;
		timer : INT;
		led4 : BOOL;
	END_VAR
	VAR
		blinkOn : USINT;
	END_VAR
END_FUNCTION_BLOCK

FUNCTION_BLOCK DoorStateMashine
	VAR_INPUT
		state : UINT;
		s0 : BOOL;
		s1 : BOOL;
		s2 : BOOL;
		s3 : BOOL;
		direction : BOOL;
	END_VAR
	VAR_OUTPUT
		speed : INT;
	END_VAR
	VAR
		doorState : UINT;
	END_VAR
END_FUNCTION_BLOCK
