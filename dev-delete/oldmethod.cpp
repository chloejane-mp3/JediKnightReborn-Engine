/*
===================
CG_DrawDataPadForceInventory
===================
*/
void CG_DrawDataPadForceInventory()
{
	int i;
	int sideLeftIconCnt, sideRightIconCnt;
	int iconCnt;
	char text[1024] = { 0 };
	char text2[1024] = { 0 };

	// count the number of powers known
	int count = 0;
	for (i = 0; i < MAX_DPSHOWPOWERS; i++)
	{
		if (ForcePowerDataPad_Valid(i))
		{
			count++;
		}
	}

	if (count < 1) // If no force powers, don't display
	{
		return;
	}

	// Time to switch new icon colors
	cg.iconSelectTime = cg.forcepowerSelectTime;

	constexpr int sideMax = 1; // Max number of icons on the side

	// Calculate how many icons will appear to either side of the center one
	const int holdCount = count - 1; // -1 for the center icon
	if (holdCount == 0) // No icons to either side
	{
		sideLeftIconCnt = 0;
		sideRightIconCnt = 0;
	}
	else if (count > 2 * sideMax) // Go to the max on each side
	{
		sideLeftIconCnt = sideMax;
		sideRightIconCnt = sideMax;
	}
	else // Less than max, so do the calc
	{
		sideLeftIconCnt = holdCount / 2;
		sideRightIconCnt = holdCount - sideLeftIconCnt;
	}

	constexpr int smallIconSize = 22;
	constexpr int bigIconSize = 45;
	constexpr int bigPad = 64;
	constexpr int pad = 32;

	constexpr int centerXPos = 320;
	constexpr int graphicYPos = 310;

	i = cg.DataPadforcepowerSelect - 1;
	if (i < 0)
	{
		i = MAX_DPSHOWPOWERS - 1;
	}

	// Print icons to the left of the center
	cgi_R_SetColor(colorTable[CT_WHITE]);

	// Work backwards from current icon
	int holdX = centerXPos - (bigIconSize / 2 + bigPad + smallIconSize);
	for (iconCnt = 1; iconCnt < sideLeftIconCnt + 1; i--)
	{
		if (i < 0)
		{
			i = MAX_DPSHOWPOWERS - 1;
		}

		if (!ForcePowerDataPad_Valid(i)) // Does he have this power?
		{
			continue;
		}

		++iconCnt; // Good icon

		if (force_icons[showDataPadPowers[i]])
		{
			CG_DrawPic(holdX, graphicYPos, smallIconSize, smallIconSize, force_icons[showDataPadPowers[i]]);
		}

		// A new force power
		if (cg_updatedDataPadForcePower1.integer - 1 == showDataPadPowers[i] ||
			cg_updatedDataPadForcePower2.integer - 1 == showDataPadPowers[i] ||
			cg_updatedDataPadForcePower3.integer - 1 == showDataPadPowers[i])
		{
			CG_DrawPic(holdX, graphicYPos, smallIconSize, smallIconSize, cgs.media.DPForcePowerOverlay);
		}

		if (force_icons[showDataPadPowers[i]])
		{
			holdX -= smallIconSize + pad;
		}
	}

	// Current Center Icon
	if (force_icons[showDataPadPowers[cg.DataPadforcepowerSelect]])
	{
		cgi_R_SetColor(colorTable[CT_WHITE]);
		CG_DrawPic(centerXPos - bigIconSize / 2, graphicYPos - (bigIconSize - smallIconSize) / 2, bigIconSize,
			bigIconSize, force_icons[showDataPadPowers[cg.DataPadforcepowerSelect]]);

		// New force power
		if (cg_updatedDataPadForcePower1.integer - 1 == showDataPadPowers[cg.DataPadforcepowerSelect] ||
			cg_updatedDataPadForcePower2.integer - 1 == showDataPadPowers[cg.DataPadforcepowerSelect] ||
			cg_updatedDataPadForcePower3.integer - 1 == showDataPadPowers[cg.DataPadforcepowerSelect])
		{
			CG_DrawPic(centerXPos - bigIconSize / 2, graphicYPos - (bigIconSize - smallIconSize) / 2,
				bigIconSize,
				bigIconSize, cgs.media.DPForcePowerOverlay);
		}
	}

	i = cg.DataPadforcepowerSelect + 1;
	if (i >= MAX_DPSHOWPOWERS)
	{
		i = 0;
	}

	cgi_R_SetColor(colorTable[CT_WHITE]);

	// Work forwards from current icon
	holdX = centerXPos + bigIconSize / 2 + bigPad;
	for (iconCnt = 1; iconCnt < sideRightIconCnt + 1; i++)
	{
		if (i >= MAX_DPSHOWPOWERS)
		{
			i = 0;
		}

		if (!ForcePowerDataPad_Valid(i)) // Does he have this power?
		{
			continue;
		}

		++iconCnt; // Good icon

		if (force_icons[showDataPadPowers[i]])
		{
			CG_DrawPic(holdX, graphicYPos, smallIconSize, smallIconSize, force_icons[showDataPadPowers[i]]);
		}

		// A new force power
		if (cg_updatedDataPadForcePower1.integer - 1 == showDataPadPowers[i] ||
			cg_updatedDataPadForcePower2.integer - 1 == showDataPadPowers[i] ||
			cg_updatedDataPadForcePower3.integer - 1 == showDataPadPowers[i])
		{
			CG_DrawPic(holdX, graphicYPos, smallIconSize, smallIconSize, cgs.media.DPForcePowerOverlay);
		}

		if (force_icons[showDataPadPowers[i]])
		{
			holdX += smallIconSize + pad;
		}
	}

	if (!cgi_SP_GetStringTextString(va("SP_INGAME_%s", forcepowerDesc[cg.DataPadforcepowerSelect]), text,
		sizeof text))
	{
		cgi_SP_GetStringTextString(va("SPMOD_INGAME_%s", forcepowerDesc[cg.DataPadforcepowerSelect]), text,
			sizeof text);
	}

	if (player->client->ps.forcePowerLevel[showDataPadPowers[cg.DataPadforcepowerSelect]] == 1)
	{
		if (!cgi_SP_GetStringTextString(va("SP_INGAME_%s", forcepowerLvl1Desc[cg.DataPadforcepowerSelect]), text2,
			sizeof text2))
		{
			cgi_SP_GetStringTextString(va("SPMOD_INGAME_%s", forcepowerLvl1Desc[cg.DataPadforcepowerSelect]), text2,
				sizeof text2);
		}
	}
	else if (player->client->ps.forcePowerLevel[showDataPadPowers[cg.DataPadforcepowerSelect]] == 2)
	{
		if (!cgi_SP_GetStringTextString(va("SP_INGAME_%s", forcepowerLvl2Desc[cg.DataPadforcepowerSelect]), text2,
			sizeof text2))
		{
			cgi_SP_GetStringTextString(va("SPMOD_INGAME_%s", forcepowerLvl2Desc[cg.DataPadforcepowerSelect]), text2,
				sizeof text2);
		}
	}
	else
	{
		if (!cgi_SP_GetStringTextString(va("SP_INGAME_%s", forcepowerLvl3Desc[cg.DataPadforcepowerSelect]), text2,
			sizeof text2))
		{
			cgi_SP_GetStringTextString(va("SPMOD_INGAME_%s", forcepowerLvl3Desc[cg.DataPadforcepowerSelect]), text2,
				sizeof text2);
		}
	}

	if (text[0])
	{
		constexpr short textboxXPos = 40;
		constexpr short textboxYPos = 60;
		constexpr int textboxWidth = 560;
		constexpr int textboxHeight = 300;
		constexpr float textScale = 1.0f;

		CG_DisplayBoxedText(textboxXPos, textboxYPos, textboxWidth, textboxHeight, va("%s%s", text, text2),
			4,
			textScale,
			colorTable[CT_ICON_BLUE]
		);
	}
}