﻿drop table ZData  ;
drop table  AWSMinute;
create table ZData(
	id int not null AUTO_INCREMENT,
        ObserveTime timestamp unique,
        ObserveMonth date,
				InsertTime timestamp,
				UpdateTime timestamp,
				stationNum varchar(6),
        time varchar(14),
        latitude varchar(10),
        longitude varchar(10),
        height varchar(6),
        PPHeight varchar(6),
        awsMode varchar(1),
        QCCode varchar(3),
        CCX varchar(3),
        P varchar(6),
        SP varchar(6),
        VP3 varchar(6),
        VP24 varchar(6),
        MaxP varchar(6),
        MaxPT varchar(6),
        MinP varchar(6),
        MinPT varchar(6),
        T varchar(6),
        MaxT  varchar(6),
        MaxTT varchar(6),
        MinT varchar(6),
        MinTT varchar(6),
        VT24 varchar(6),
        MaxT24 varchar(6),
        MinT24 varchar(6),
        TD varchar(6),
        RH varchar(6),
        MinRH varchar(6),
        MinRHT varchar(6),
        WP varchar(6),
        HRain varchar(6),
        HRain3 varchar(6),
        HRain6 varchar(6),
        HRain12 varchar(6),
        HRain24 varchar(6),
        RainMT varchar(6),
        RainM varchar(6),
        E varchar(6),
        WD2 varchar(6),
        WS2 varchar(6),
        WD10 varchar(6),
        WS10 varchar(6),
        MaxWD varchar(6),
        MaxWS varchar(6),
        MaxWST varchar(6),
        WD varchar(6),
        WS varchar(6),
        ExWD varchar(6),
        ExWS varchar(6),
        ExWST varchar(6),
        ExWS6 varchar(6),
        ExWD6 varchar(6),
        ExWS12 varchar(6),
        ExWD12 varchar(6),
        ET varchar(6),
        MaxET varchar(6),
        MaxETT varchar(6),
        MinET varchar(6),
        MinETT varchar(6),
        MinET12 varchar(6),
        ET5 varchar(6),
        ET10 varchar(6),
        ET15 varchar(6),
        ET20 varchar(6),
        ET40 varchar(6),
        ET80 varchar(6),
        ET160 varchar(6),
        ET320 varchar(6),
        GT varchar(6),
        MaxGT varchar(6),
        MaxGTT varchar(6),
        MinGT varchar(6),
        MinGTT varchar(6),
        V1 varchar(6),
        V10 varchar(6),
        MinV varchar(6),
        MinVT varchar(6),
        V varchar(6),
        CA varchar(6),
        LCA varchar(6),
        RCA varchar(6),
        CH varchar(6),
        CF varchar(24),
        CFC varchar(3),
        WW varchar(6),
        WT varchar(6),
        W1 varchar(6),
        W2 varchar(6),
        EC varchar(6),     
        SnowD varchar(6),
        SnowP varchar(6),
        FE1U varchar(6),
        FE1D varchar(6),
        FE2U varchar(6),
        FE2D varchar(6),
        TRT varchar(6),
        TRD varchar(6),
        GA varchar(6),
        HA varchar(6),
        HMRain varchar(120),
        MWW varchar(100),
        Q1PP varchar(8),
        Q1TH varchar(13),
        Q1RE varchar(8),
        Q1WI varchar(16),
        Q1DT varchar(19),
        Q1VV varchar(4),
        Q1CW varchar(12),
        Q1SP varchar(10),
        Q1MR varchar(60),      
        Q2PP varchar(8),
        Q2TH varchar(13),
        Q2RE varchar(8),
        Q2WI varchar(16),
        Q2DT varchar(19),
        Q2VV varchar(4),
        Q2CW varchar(12),
        Q2SP varchar(10),
        Q2MR varchar(60),       
        Q3PP varchar(8),
        Q3TH varchar(13),
        Q3RE varchar(8),
        Q3WI varchar(16),
        Q3DT varchar(19),
        Q3VV varchar(4),
        Q3CW varchar(12),
        Q3SP varchar(10),
        Q3MR varchar(60),
				primary key(id)
);
create table AWSMinute(
	id int not null AUTO_INCREMENT,
        ObserveTime timestamp unique,
        ObserveMonth date,
	InsertTime timestamp,
	UpdateTime timestamp,
	WindDir2 int,
	Windspeed2 int ,
	WindDir10 int,
	Windspeed10 int,
	WindDir int,
	Windspeed int,
	WindDir2c int,
	Windspeed10c int,
	minutexWindspeeedc int,
	MRainrat int,
	HRainrat int,
	MRainrat1 int,
	HRainrat1 int,
	MRainweight int,
	HRainweight int,
	tempis int,
	rsWindspeed int,
	temprs int,
	Wettemp int,
	HumicapRH int,
	Rh int,
	VPressure int,
	Dewpointtemp int,
	Pressure int,
	Grasstemp int,
	Groundtemppt int,
	Groundtempinfrared int,
	g5temp int,
	g10temp int,
	g15temp int,
	g20temp int,
	g40temp int,
	g80temp int,
	g160temp int,
	g320temp int,
	OntimeEvacap int,
	EvaCapacity int,
	Vis_1min int,
	Vis_10min int,
	Cloudheight int,
	Cloudage int,
	Lowcloudage int,	
	Snowdeep int,
	Freezingrain int,
	Wireice int,
	Frozensoliddeep int,
	Lightingfreq int,
	Weatherphcode varchar(12),
	DataQuality varchar(48),
	primary key (id)
)
