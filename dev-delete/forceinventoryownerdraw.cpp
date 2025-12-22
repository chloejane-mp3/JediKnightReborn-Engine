/*CG_DrawForceInventory*/
static void CG_DrawForceInventory( int forceBits )
{
	int		i,endIndex=0;
	int		iconCnt=0,rowIconCnt;

	// Count the number of force powers known
	for (i=0; i<MAX_SHOWPOWERS; ++i)
	{
		if (CG_ForcePower_Valid(forceBits, i))
		{
			iconCnt++;
		}
	}

	if (!iconCnt)	// If no force powers, don't display
	{
		return;
	}

	// Single line of icons
	if (iconCnt<=MAXLOADICONSPERROW)
	{
		CG_DrawLoadForcePrintRow("forceicons_singlerow", forceBits, iconCnt,0);
	}
	// Two lines of icons
	else
	{
		// Print top row
		endIndex = CG_DrawLoadForcePrintRow("forceicons_row1", forceBits, MAXLOADICONSPERROW,0);

		// Print second row
		rowIconCnt = iconCnt - MAXLOADICONSPERROW;
		CG_DrawLoadForcePrintRow("forceicons_row2", forceBits, rowIconCnt,endIndex+1);
	}

	cgi_R_SetColor( NULL );
}

// Get the player weapons and force power info
static void CG_GetPlayerForcePowers(int *weaponBits,int *forceBits)
{
	char	s[MAX_STRING_CHARS];
	int		iDummy,i;
	float	fDummy;
	const char	*var;

	gi.Cvar_VariableStringBuffer( sCVARNAME_PLAYERSAVE, s, sizeof(s) );

	// Get player weapons and force powers known
	if (s[0])
	{
	//				|general info				  |-force powers
		sscanf( s, "%i %i",
							//force power data
				&*forceBits,	//	&client->ps.forcePowersKnown,
				&iDummy		//	&client->ps.forcePower,

				);
	}

	// the new JK2 stuff - force powers, etc...
	//
	gi.Cvar_VariableStringBuffer( "playerfplvl", s, sizeof(s) );
	i=0;
	var = strtok( s, " " );
	while( var != NULL )
	{
		/* While there are tokens in "s" */
		loadForcePowerLevel[i++] = atoi(var);
		/* Get next token: */
		var = strtok( NULL, " " );
	}
}

/*CG_DrawDataPadForceInventory*/
void CG_DrawDataPadForceInventory( );
{
    int forcepowers=0;

    CG_GetPlayerForcePowers(&forcepowers);

    CG_DrawForceInventory(forcepowers);
}