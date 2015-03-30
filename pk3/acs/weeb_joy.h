// [jpalomo] Execute specials and the ghost step with joysticks
// It still works perfectly fine with buttons instead of sticks

int stick_forward; // positive is forward, negative is backward
int stick_side; // positive is right, negative is left
// Both of the above have a range of [-12800, 12800]


int previous_buttons;
int current_buttons;

int MoveAngle;

Function Int PressedKey (Int key)
{
	previous_buttons = GetPlayerInput (-1, ModInput_OldButtons);
	current_buttons = GetPlayerInput (-1, ModInput_Buttons);
	
	if ((current_buttons & key) && !(previous_buttons & key))
	{
		Return key;
	}
	Return 0;
}

// Specials
// I had to put each of these in their own script since it wouldn't keep track of all 4 directions

Script WEEB_JOY_FORW Enter
{
	Int ForwardCounter = 0;
	Int TapCounterForward = 0;
	While (True)
	{
		stick_forward = GetPlayerInput (-1, ModInput_ForwardMove); // This needs to be constantly updated
		
		if (GetCvar("dst_nospecials") == 0)
		{
			
			// Forward  
			if (stick_forward >= 3200) // About 1/4 forward while running or half-way while walking
			{
				ForwardCounter = 8;
				TapCounterForward ++;
				Until (stick_forward < 3200 || TapCounterForward >= 2) // Do this while we wait for the stick to return to neutral
				{
					ForwardCounter --;
					If (ForwardCounter == 0) // Did we wait too long
					{
						TapCounterForward = 0;
						break;
					}
					Delay (1);
				}
				// We need to go through the above twice before executing the stuff below
				If (CheckInventory("SuperMeterCounter") >= 20 && CheckInventory("DoubleTapCooldown") == 0 && ForwardCounter > 0 && TapCounterForward == 2)
				{
					GiveInventory("DoubleTapForward",1);
					GiveInventory("DoubleTapCooldown",20);
					// Reset all of our counters
					TapCounterForward = 0;
					ForwardCounter = 0;
					break;
				}
			}
			
			ForwardCounter --;
			If (ForwardCounter == 0)
			{
				TapCounterForward = 0;
			}
			Delay (1);
		}
		Delay (1);
	}
	Delay (1);
	Restart;
}

Script WEEB_JOY_LEFT Enter
{
	Int BackCounter = 0;
	Int TapCounterBack = 0;
	While (True)
	{
		stick_forward = GetPlayerInput (-1, ModInput_ForwardMove);

		if (GetCvar("dst_nospecials") == 0)
		{
			// Back
			if (stick_forward <= -3200)
			{
				BackCounter = 8;
				TapCounterBack ++;
				Until (stick_forward > -3200 || TapCounterBack >= 2)
				{
					BackCounter --;
					If (BackCounter == 0)
					{
						TapCounterBack = 0;
						break;
					}
					Delay (1);
				}
			
				if (CheckInventory("SuperMeterCounter") >= 20 && CheckInventory("DoubleTapCooldown") == 0 && BackCounter > 0 && TapCounterBack == 2)
				{ 
					GiveInventory("DoubleTapBack",1); 
					GiveInventory("DoubleTapCooldown",20);
					TapCounterBack = 0;
					BackCounter = 0;
					break;
				}
			}
			BackCounter --;
			If (BackCounter == 0)
			{
				TapCounterBack = 0;
			}
			Delay (1);
		}
		Delay (1);
	}
	Delay (1);
	Restart;
}

Script WEEB_JOY_RITE Enter
{
	Int LeftCounter = 0;
	Int TapCounterLeft = 0;
	While (True)
	{
		stick_side = GetPlayerInput (-1, ModInput_SideMove);

		if (GetCvar("dst_nospecials") == 0)
		{
			// Left
			if (stick_side <= -3200)
			{
				LeftCounter = 8;
				TapCounterLeft ++;
				Until (stick_side > -3200 || TapCounterLeft >= 2)
				{
					LeftCounter --;
					If (LeftCounter == 0)
					{
						TapCounterLeft = 0;
						break;
					}
					Delay (1);
				}
			
				if (CheckInventory("SuperMeterCounter") >= 20 && CheckInventory("DoubleTapCooldown") == 0 && LeftCounter > 0 && TapCounterLeft == 2)
				{ 
					GiveInventory("DoubleTapLeft",1); 
					GiveInventory("DoubleTapCooldown",20);
					TapCounterLeft = 0;
					LeftCounter = 0;
					break;
				}
			}
			
			LeftCounter --;
			If (LeftCounter == 0)
			{
				TapCounterLeft = 0;
			}
			Delay (1);
		}
		Delay (1);
	}
	Delay (1);
	Restart;
}

Script WEEB_JOY_BACK Enter
{
	Int RightCounter = 0;
	Int TapCounterRight = 0;
	While (True)
	{
		stick_side = GetPlayerInput (-1, ModInput_SideMove);

		if (GetCvar("dst_nospecials") == 0)
		{
			// Right
			if (stick_side >= 3200)
			{
				RightCounter = 8;
				TapCounterRight ++;
				Until (stick_side < 3200 || TapCounterRight >= 2)
				{
					RightCounter --;
					If (RightCounter == 0)
					{
						TapCounterRight = 0;
						break;
					}
					Delay (1);
				}
			
				if (CheckInventory("SuperMeterCounter") >= 20 && CheckInventory("DoubleTapCooldown") == 0 && RightCounter > 0 && TapCounterRight == 2)
				{ 
					GiveInventory("DoubleTapRight",1); 
					GiveInventory("DoubleTapCooldown",20);
					TapCounterRight = 0;
					RightCounter = 0;
					break;
				}
			}
			RightCounter --;
			If (RightCounter == 0)
			{
				TapCounterRight = 0;
			}
			Delay (1);
		}
		Delay (1);
	}
	Delay (1);
	Restart;
}

// Ghost Step
// This one still uses the Speed button to trigger it, so you still need to bind it

Script WEEB_JOY_LOOP Enter
{
	While (True)
	{
		stick_forward = GetPlayerInput (-1, ModInput_ForwardMove);
		stick_side = GetPlayerInput (-1, ModInput_SideMove);
		previous_buttons = GetPlayerInput (-1, ModInput_OldButtons);
		current_buttons = GetPlayerInput (-1, ModInput_Buttons);
		
		MoveAngle = GetActorAngle(0) >> 8;
		
		if (CheckInventory("GhostStepCooldown") == 0 && CheckInventory("GhostStepDone") == 0)
        {
			if ((PressedKey(BT_SPEED)) && (stick_forward >= 3200)) {
              if (CheckInventory("OnTheGround") == 1) { ThrustThing(MoveAngle+0,35,1,0); ThrustThingZ(0,85,1,1); } else { ThrustThing(MoveAngle+0,25,0,0); ThrustThingZ(0,20,0,0); }
              ActivatorSound("ghost/step",127);
              GiveInventory("GhostStepDone",1);
              GiveInventory("GhostStepCooldown",35);
              ACS_ExecuteAlways(267,0,6,0,0); }
			if ((PressedKey(BT_SPEED)) && (stick_side <= -3200)) {
              if (CheckInventory("OnTheGround") == 1) { ThrustThing(MoveAngle+64,35,1,0); ThrustThingZ(0,85,1,1); } else { ThrustThing(MoveAngle+64,25,0,0); ThrustThingZ(0,20,0,0); }
              ActivatorSound("ghost/step",127);
              GiveInventory("GhostStepDone",1);
              GiveInventory("GhostStepCooldown",35); 
              ACS_ExecuteAlways(267,0,6,0,0); }
			if ((PressedKey(BT_SPEED)) && (stick_forward <= -3200)) {
              if (CheckInventory("OnTheGround") == 1) { ThrustThing(MoveAngle+128,35,1,0); ThrustThingZ(0,85,1,1); } else { ThrustThing(MoveAngle+128,25,0,0); ThrustThingZ(0,20,0,0); }
              ActivatorSound("ghost/step",127);
              GiveInventory("GhostStepDone",1);
              GiveInventory("GhostStepCooldown",35); 
              ACS_ExecuteAlways(267,0,6,0,0); }
			if ((PressedKey(BT_SPEED)) && (stick_side >= 3200)) {
              if (CheckInventory("OnTheGround") == 1) { ThrustThing(MoveAngle+192,35,1,0); ThrustThingZ(0,85,1,1); } else { ThrustThing(MoveAngle+192,25,0,0); ThrustThingZ(0,20,0,0); }
              ActivatorSound("ghost/step",127);
              GiveInventory("GhostStepDone",1);
              GiveInventory("GhostStepCooldown",35); 
              ACS_ExecuteAlways(267,0,6,0,0); }
        }
		
		Delay (1);
	}
	
	Delay (1);
	Restart;
}