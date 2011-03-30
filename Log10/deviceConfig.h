#if defined(USE_EC_CLOCK)
_FOSCSEL( FNOSC_PRI &		// external clock + PLL enabled in code
		IESO_ON )				// include file is WRONG
_FOSC(	FCKSM_CSECME &			// clocks and monitor disabled
		OSCIOFNC_ON &			// no Fcy output on OSC2
		POSCMD_EC &
		IOL1WAY_OFF )			// reconfig allowed
#else
//_FOSCSEL( FNOSC_FRC &			// external clock + PLL enabled in code
//		IESO_OFF )				// include file is WRONG
_FOSCSEL( FNOSC_FRCPLL &			// external clock + PLL enabled in code
		IESO_OFF )				// include file is WRONG
_FOSC(	FCKSM_CSECMD &			// clocks and monitor disabled
		OSCIOFNC_ON &			// no Fcy output on OSC2
		POSCMD_EC &
		IOL1WAY_OFF )			// reconfig allowed
#endif

_FBS( BWRP_WRPROTECT_OFF )		// no boot segments or write protect
_FSS ( SWRP_WRPROTECT_OFF )		// no secure sections
_FGS( GSS_OFF &					// no code protect
		GCP_OFF &
		GWRP_OFF )
_FWDT(	FWDTEN_OFF &			// wdt's disabled
		WINDIS_OFF )
_FPOR(	FPWRT_PWR32 & ALTI2C_ON  ) // fast powerup, will need to change for ext osc
_FICD(	JTAGEN_OFF &			// jtag off and use 2nd set for ICSP
		ICS_PGD1 )
_FUID0( 0xffff )
_FUID1( 0xffff )
_FUID2( 0xffff )
_FUID3( 0xffff )
