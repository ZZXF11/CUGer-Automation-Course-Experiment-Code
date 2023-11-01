/* Quartus II 64-Bit Version 13.1.0 Build 162 10/23/2013 SJ Full Version */
JedecChain;
	FileRevision(JESD32A);
	DefaultMfr(6E);

	P ActionCode(Ign)
		Device PartName(5CSEMA5F31) MfrSpec(OpMask(0));
	P ActionCode(Cfg)
		Device PartName(5CSEMA5F31) Path("E:/code/DE1Soc/05_ckey_led/output_files/") File("ckey_led.sof") MfrSpec(OpMask(1));

ChainEnd;

AlteraBegin;
	ChainType(JTAG);
AlteraEnd;
